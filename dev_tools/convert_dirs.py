import ebcdic
import sys

def convert_file(file_name, CCSID_1="ascii", CCSID_2="ascii", output_file_name = "",remove_newline=False,convert_to_bin=True):
    CCSID_1 = determine_ccsid(CCSID_1) if not CCSID_1 == "ascii" else "UTF-8"
    CCSID_2 = determine_ccsid(CCSID_2) if not CCSID_2 == "ascii" else "UTF-8"

    if output_file_name == "":
        output_file_name = f'{file_name.split('.')[0]}_decoded.{file_name.split('.')[1]}'
    
    if convert_to_bin:
        output_file_name = f"{output_file_name.split('.')[0]}.bin"

    f = open(file_name, "rb")
    file_text = f.read().decode(CCSID_1)
    f.close()

    if remove_newline:
        file_text = file_text.replace("\n","")

    f = open(output_file_name, "wb")
    f.write(file_text.encode(CCSID_2))
    f.close()
    return True

def convert_directory(directory_name, CCSID_1="ascii", CCSID_2="ascii", output_directory_name="", remove_newline=False):
    if output_directory_name == "":
        output_directory_name = f'{directory_name}_decoded'
    admin_types = ["group_connection", "racf_options", "dataset", "group", "user", "resource", "permission"]
    for filename in os.listdir(directory_name):
        admin_dir = ""
        for profile_type in admin_types:
            if profile_type in filename:
                if profile_type == "group" and "group_connection" in filename:
                    continue
                admin_dir = f"/{profile_type}"
        convert_file(f'{directory_name}/{filename}',CCSID_1,CCSID_2,f'{output_directory_name}{admin_dir}/{filename}',remove_newline,convert_to_bin=True)

def determine_ccsid(CCSID):
    if isinstance(CCSID,int):
        return f"cp{CCSID:03}"
    if "cp" in CCSID:
        return CCSID
    return "cp"+CCSID

directory = sys.argv[1]

for directory in sys.argv[1:]:
    print(f"Converting {directory}_xml to EBCDIC in {directory}_bin...")
    convert_directory(f"{directory}_xml",CCSID_2=1047,output_directory_name=f"{directory}_bin",remove_newline=True)

print("All done!")
