import os
import sys
import re
import json

def to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def to_lower_camel_case(snake_str):
    # We capitalize the first letter of each component except the first one
    # with the 'capitalize' method and join them together.
    camel_string = to_camel_case(snake_str)
    return snake_str[0].lower() + camel_string[1:]

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



def convert_key_map_hpp_to_json_schema(input_filepath, output_filepath):
    alter_only_admin_types = ["Racf Options", "Permission", "Group Connection"]
    if input_filepath.split('.')[1] != "hpp" or output_filepath.split('.')[1] != "json":
        print("whoops, wrong file!")
    admin_type = output_filepath.split('.')[0].split('/')[-1].replace("_"," ").title()
    allowed_operations = ["add", "alter", "extract"]
    if admin_type in alter_only_admin_types:
        allowed_operations = ["alter", "extract"]

    admin_type.replace("Racf","RACF")

    json_admin_type_name =  f"{get_json_name(admin_type.lower())}_admin"
    with open(f"dev_tools/old_json/{json_admin_type_name}.json") as fp:
            admin_json = json.load(fp)

    f = open(input_filepath, "r")
    header_file_data = f.read()
    f.close()

    segement_trait_information = header_file_data.split('segment_key_mapping_t')[0]

    segment_mapping = f"{admin_type.replace(" ","_").upper()}_([A-Z]*)(?<!SEGMENT)_(?:SEGMENT|KEY)_MAP"

    segments = re.findall(segment_mapping, segement_trait_information)

    if "add" in allowed_operations:
        json_schema = { "addOnlyTraits": {}, "alterOnlyTraits": {}, "commonTraits": {}, "extractOnlyTraits": {}, "patternProperties": {}}
    else:
        json_schema = { "commonTraits": {}, "extractOnlyTraits": {}, "patternProperties": {}}
    
    for segment in segments:
        #print(segment)
        trait_mapping = f"\"({segment.lower()}:[a-z_]*)\"," + \
        ".*\"([a-z]*)\",\n.*TRAIT_TYPE_([A-Z]*),.*\\{(true|false), (true|false), (true|false), (true|false)\\}"
        traits = re.findall(trait_mapping, segement_trait_information)
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
            
            trait_name = trait[0] if "*" not in trait[0] else trait[0].replace("*","[a-zA-Z0-9@#$]+$")
            trait_dict = {trait_name: { "racfKey": trait[1]}}
            if trait[2].lower() == "pseudo_boolean":
                trait_dict[trait_name]["pseudoBoolean"] = True
            op_allowed_str = ''.join(operators_allowed)
            if "boolean" in trait[2].lower():
                if op_allowed_str == '`"delete"`':
                    trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeDelOnlyBoolean"
                elif op_allowed_str == '`"set"`':
                    trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeSetOnlyBoolean"
                else:
                    trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeBoolean"
            elif "repeat" in trait[2].lower():
                trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeList"
            elif "string" in trait[2].lower():
                if '`"add"`' in op_allowed_str or '`"remove"`' in op_allowed_str:
                    if '`"set"`' not in op_allowed_str:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeAddRemoveList"
                    elif '`"delete"`' not in op_allowed_str:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeNoDeleteList"
                    elif '`"remove"`' not in op_allowed_str:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeNoRemoveList"
                    elif '`"add"`' not in op_allowed_str:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeNoAddList"
                    else:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeList"
                else:
                    if op_allowed_str == '`"set"`':
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeSetOnlyString"
                    else:
                        trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeString"
            elif "uint" in trait[2].lower():
                if op_allowed_str == '`"set"`':
                    trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeSetOnlyUint"
                else:
                    trait_dict[trait_name]["$ref"] = "#/$defs/traitTypeUint"
            else:
                trait_dict[trait_name]["$ref"] = "N/A"
            
            if supported_operations == ['`"extract"`']:
                json_schema["extractOnlyTraits"].update(trait_dict)
                #print('extract only')
            elif "*" in trait[0]:
                trait_dict[trait_name]["operatorCode"] = trait[2].lower()+''.join(operators_allowed)
                json_schema["patternProperties"].update(trait_dict)
                #print('addedPattern')
            else:
                trait_dict[trait_name]["operatorCode"] = trait[2].lower()+''.join(operators_allowed)
                if "add" in allowed_operations:
                    if '`"add"`' in supported_operations and '`"alter"`' not in supported_operations:
                        json_schema["addOnlyTraits"].update(trait_dict)
                        #print('add')
                    elif '`"alter"`' in supported_operations and '`"add"`' not in supported_operations:
                        json_schema["alterOnlyTraits"].update(trait_dict)
                        #print('addedPattern')
                    else:
                        json_schema["commonTraits"].update(trait_dict)
                else:
                    json_schema["commonTraits"].update(trait_dict)

    return json_schema

def convert_directory(directory_path):
    ignore_list = ["key_map.cpp", "key_map.hpp", "key_map_structs.hpp"]
    master_json = {}
    for file_name in os.listdir(directory_path):
        if file_name in ignore_list:
            continue
        admin_type = file_name.split("key_map_")[1].split('.')[0]
        output_name = admin_type+".json"
        print(f"Converting {file_name} to {output_name} for documentation purposes...")
        master_json[admin_type] = convert_key_map_hpp_to_json_schema(directory_path+"/"+file_name, "dev_tools/schema/"+output_name)

    f = open("dev_tools/schema/trait_types_defs.json", "r")
    json_schema = json.load(f)
    f.close()

    operation_combos = []
    for admin_type in master_json.keys():
        camel_admin_type = to_lower_camel_case(admin_type)
        if "addOnlyTraits" in master_json[admin_type] and master_json[admin_type]["addOnlyTraits"] != {}:
            for trait in master_json[admin_type]["addOnlyTraits"]:
                operation_combos.append(master_json[admin_type]["addOnlyTraits"][trait]["operatorCode"])
                del master_json[admin_type]["addOnlyTraits"][trait]["operatorCode"]
            add_properties = { 
                f"{camel_admin_type}AddOnlyTraits": { 
                    "properties": master_json[admin_type]["addOnlyTraits"],
                    "patternProperties": master_json[admin_type]["patternProperties"],
                    "additionalProperties": False
                }
            }
            json_schema["$defs"].update(add_properties)
        if "alterOnlyTraits" in master_json[admin_type] and master_json[admin_type]["alterOnlyTraits"] != {}:
            for trait in master_json[admin_type]["alterOnlyTraits"]:
                #print(trait, master_json[admin_type]["alterProperties"][trait])
                operation_combos.append(master_json[admin_type]["alterOnlyTraits"][trait]["operatorCode"])
                del master_json[admin_type]["alterOnlyTraits"][trait]["operatorCode"]
            alter_properties = { 
                f"{camel_admin_type}AlterOnlyTraits": { 
                    "properties": master_json[admin_type]["alterOnlyTraits"],
                    "patternProperties": master_json[admin_type]["patternProperties"],
                    "additionalProperties": False
                }
            }
            json_schema["$defs"].update(alter_properties)
        for trait in master_json[admin_type]["commonTraits"]:
            #print(trait, master_json[admin_type]["alterProperties"][trait])
            operation_combos.append(master_json[admin_type]["commonTraits"][trait]["operatorCode"])
            del master_json[admin_type]["commonTraits"][trait]["operatorCode"]
        alter_properties = { 
            f"{camel_admin_type}CommonTraits": { 
                "properties": master_json[admin_type]["commonTraits"],
                "patternProperties": master_json[admin_type]["patternProperties"],
                "additionalProperties": False
            }
        }
        json_schema["$defs"].update(alter_properties)
        if "extractOnlyTraits" in master_json[admin_type] and master_json[admin_type]["extractOnlyTraits"] != {}:
            extract_only_properties = {
                    f"{camel_admin_type}ExtractOnlyTraits": { 
                    "properties": master_json[admin_type]["extractOnlyTraits"]
                }
            }
    #unique_combos = list(sorted(set(operation_combos)))
    #print(unique_combos)

    master_json_path = "dev_tools/schema/traits_schema_defs.json"
    f = open(master_json_path, "w")
    json.dump(json_schema,indent=2,fp=f)
    f.write("\n")
    f.close()
    

def convert_file(file_path):
    file_name = file_path.split('/')[1]
    output_name = file_name.split("key_map_")[1].split('.')[0]+".md"
    convert_key_map_hpp_to_json_schema(file_path, "md/"+output_name)

def merge_schema(input_1, input_2, output):
    full_schema = {}

    f = open(input_1, "r")
    json_schema_1 = json.load(f)
    f.close()

    f = open(input_2, "r")
    json_schema_2 = json.load(f)
    f.close()

    full_schema = json_schema_1
    for key in json_schema_2:
        if key in full_schema and isinstance(full_schema[key],dict):
            full_schema[key].update(json_schema_2[key])
    
    f = open(output, "w")
    json.dump(full_schema,indent=2,fp=f)
    f.write("\n")
    f.close()


directory_path = "racfu/key_map"
convert_directory(directory_path)

merge_schema("schemas/parameters.json","dev_tools/schema/traits_schema_defs.json","schemas/racfu_schema.json")

#file_path = sys.argv[1]
#convert_file(file_path)
