import os
import sys
import re
import json

def get_json_name(admin_type):
    if admin_type == "group connection":
        return "gc"
    if admin_type == "permission":
        return "perm"
    if admin_type == "racf options":
        return "s"
    if admin_type == "resource":
        return "p"
    return admin_type[0]

def add_supported_operations(racf_segment, racf_key, allowed_operations, admin_json, is_racf_options = False, is_permission = False):
    #print(f"Segment: {racf_segment}, Trait: {racf_key}")
    #print(f"segment keys: {admin_json[racf_segment].keys()}")
    trait = admin_json[racf_segment][racf_key]
    #print(f"trait keys: {trait.keys()}")
    #print(allowed_operations, ('alter' in allowed_operations))
    supported_operations = []
    for key in trait.keys():
        if not isinstance(trait[key], dict) or "extract" not in trait[key].keys():
            continue
        #print(f"{trait[key].keys()}")
        if ('add' in allowed_operations) and (trait[key]["add"] == True):
            supported_operations.append('`"add"`')
        if  trait[key]["alt"] == True or (is_racf_options or is_permission):
            supported_operations.append('`"alter"`')
        if trait[key]["extract"] == True or is_racf_options:
            supported_operations.append('`"extract"`')
    #print(supported_operations)
    if supported_operations != []:
        supported_operations = list(set(supported_operations))
        supported_operations.sort()
    #print(supported_operations)
    return supported_operations



def convert_key_map_hpp_to_doc(input_filepath, output_filepath):
    alter_only_admin_types = ["Racf Options", "Permission", "Group Connection"]
    if input_filepath.split('.')[1] != "hpp" or output_filepath.split('.')[1] != "md":
        print("whoops, wrong file!")
    admin_type = output_filepath.split('.')[0].split('/')[1].replace("_"," ").title()
    operation_types = "add and alter operations,"
    allowed_operations = ["add", "alter", "extract"]
    if admin_type in alter_only_admin_types:
        operation_types = "alter operations"
        allowed_operations = ["alter", "extract"]
    
    doc_link = "https://www.ibm.com/docs/en/zos/latest?topic=services-reference-documentation-tables"

    admin_type.replace("Racf","RACF")
    
    doc_file_data = f"---\nlayout: default\nparent: Traits\n---\n\n# {admin_type} Traits\n\n" + \
    f"The following tables describes the {admin_type.lower()} segments and traits that are" + \
    f" supported for {operation_types} and returned by extract operations.\n" + \
    "{: .fs-6 .fw-300 }\n\n&nbsp;\n\n{: .note }\n" + \
    f"> _More information about **RACF Keys** can be found [here]({doc_link})._" + \
    "\n\n&nbsp;\n\n{: .note }\n" + \
    "> _See [Data Types](../data_types) for more information about **Data Types**._" + \
    "\n\n&nbsp;\n\n{: .note }\n" + \
    "> _See [Operators](../operators) for more information about **Operator** usage._\n"

    json_admin_type_name =  f"{get_json_name(admin_type.lower())}_admin"
    with open(f"{json_admin_type_name}.json") as fp:
            admin_json = json.load(fp)

    f = open(input_filepath, "r")
    header_file_data = f.read()
    f.close()

    segment_trait_information = header_file_data.split('segment_key_mapping_t')[0]

    segment_mapping = f"{admin_type.replace(" ","_").upper()}_([A-Z]*)(?<!SEGMENT)_(?:SEGMENT|KEY)_MAP"

    segments = re.findall(segment_mapping, segment_trait_information)
    
    for segment in segments:
        if segment.upper() == "CSDATA":
            continue
        #print(segment)
        doc_file_data = doc_file_data + f"\n## `{segment.lower()}`\n\n" + \
        "| **Trait** | **RACF Key** | **Data Types** | **Operators Allowed** | **Supported Operations** |\n"
        trait_mapping = f"\"({segment.lower()}:[a-z_]*)\"," + \
        ".*\"([a-z]*)\",\n.*TRAIT_TYPE_([A-Z]*),.*\\{(true|false), (true|false), (true|false), (true|false)\\}"
        traits = re.findall(trait_mapping, segment_trait_information)
        for trait in traits:
            #print(trait)
            operators_allowed = []
            if trait[3] == "true":
                operators_allowed.append('`"set"`')
            if trait[4] == "true":
                operators_allowed.append('`"add"`')
            if trait[5] == "true":
                operators_allowed.append('`"remove"`')
            if trait[6] == "true":
                operators_allowed.append('`"delete"`')
            if operators_allowed == []:
                operators_allowed = ["N/A"]
                supported_operations = ['`"extract"`']
            else:
                supported_operations = add_supported_operations( segment.lower(), trait[1].lower(), allowed_operations, admin_json, is_racf_options = (admin_type.lower() == "racf options"), is_permission = (admin_type.lower() == "permission") )
            doc_file_data = doc_file_data + \
            f"| `\"{trait[0]}\"` | `{trait[1]}` | `{trait[2].lower()}` | {"<br>".join(operators_allowed)} | {"<br>".join(supported_operations)} |\n"
    
    f = open(output_filepath, "w")
    f.write(doc_file_data)
    f.close()
    return 0

def convert_directory(directory_path):
    ignore_list = ["key_map.cpp", "key_map.hpp", "key_map_structs.hpp"]
    for file_name in os.listdir(directory_path):
        if file_name in ignore_list:
            continue
        output_name = file_name.split("key_map_")[1].split('.')[0]+".md"
        print(f"Converting {file_name} to {output_name} for documentation purposes...")
        convert_key_map_hpp_to_doc(directory_path+"/"+file_name, "md/"+output_name)

def convert_file(file_path):
    file_name = file_path.split('/')[1]
    output_name = file_name.split("key_map_")[1].split('.')[0]+".md"
    convert_key_map_hpp_to_doc(file_path, "md/"+output_name)

directory_path = sys.argv[1]
convert_directory(directory_path)

#file_path = sys.argv[1]
#convert_file(file_path)
