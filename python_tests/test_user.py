
from helper import successful_return_codes, user_not_found_return_codes

# Import SEAR
from sear import sear


def test_add_user(delete_user):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": delete_user,
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_user_with_danish_characters(delete_user):
    """This test is supposed to succeed"""
    username = delete_user

    name = "BØLLE MÅNEN ER STÆRK"

    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": username,
            "traits": {
                "base:name": name,  # noqa: E501
            },
            },
        )
    
    extract_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            "userid": username,
            },
        )
    
    assert "errors" not in str(add_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes
    assert extract_result.result["profile"]["base"]["name"] == name

def test_add_user_with_german_characters(delete_user):
    """This test is supposed to succeed"""
    username = delete_user

    name = "ÖSTERREICH IST ÜBER"

    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": username,
            "traits": {
                "base:name": name,  # noqa: E501
            },
            },
        )
    
    extract_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            "userid": username,
            },
        )
    
    assert "errors" not in str(add_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes
    assert extract_result.result["profile"]["base"]["name"] == name

def test_add_user_with_spanish_characters(delete_user):
    """This test is supposed to succeed"""
    username = delete_user

    name = "DIEGO VELÁZQUEZ"

    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": username,
            "traits": {
                "base:name": name,  # noqa: E501
                "base:installation_data": "Diego Rodríguez de Silva y Velázquez (Sevilla, bautizado el 6 de junio de 1599-Madrid, 6 de agosto de 1660), conocido como Diego Velázquez",  # noqa: E501
            },
            },
        )
    
    extract_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            "userid": username,
            },
        )
    
    assert "errors" not in str(add_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes
    assert extract_result.result["profile"]["base"]["name"] == name

def test_add_user_missing_userid():
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_user_userid_too_long():
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": "ThisIsTooLong",
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_user_base_traits(delete_user):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": delete_user,
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
                "base:name": "TEST USER",
                "base:restrict_global_access_checking": True,
                "base:automatic_dataset_protection": True,
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_user_no_traits(delete_user):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": delete_user,
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_user_tso_traits(delete_user):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": delete_user,
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
                "tso:max_region_size": 0,
                "tso:message_class": "A",
                "tso:hold_class": "B",
                "tso:job_class": "B",
                "tso:sysout_class": "B",
                "tso:account_number": "2348234",
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_user_omvs_traits(delete_user):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "user", 
            "userid": delete_user,
            "traits": {
                "base:installation_data": "USER GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
                "omvs:home_directory": f"/u/{delete_user}",
                "omvs:default_shell": "/bin/sh",
                "omvs:max_files_per_process": 20,
                "omvs:max_threads": 4,
                "omvs:auto_uid": True,
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_extract_user(create_user):
    """This test is supposed to succeed"""
    extract_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            "userid": create_user,
            },
        )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_user_extract_not_found():
    """This test is supposed to fail"""
    user_not_found_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            "userid": "JMCCLANE",
            },
        )
    assert "errors" in str(user_not_found_result.result)
    assert user_not_found_result.result["return_codes"] == user_not_found_return_codes

def test_user_extract_missing_userid():
    """This test is supposed to fail"""
    user_not_found_result = sear(
            {
            "operation": "extract",
            "admin_type": "user",
            },
        )
    assert "errors" in str(user_not_found_result.result)
    assert user_not_found_result.result["return_codes"] != successful_return_codes

def test_alter_user(create_user):
    """This test is supposed to succeed"""
    alter_result = sear(
            {
            "operation": "alter", 
            "admin_type": "user", 
            "userid": create_user,
            "traits": {
                "omvs:default_shell": "/bin/zsh",
            },
            },
        )
    assert "errors" not in str(alter_result.result)
    assert alter_result.result["return_codes"] == successful_return_codes

def test_delete_user(create_user):
    """This test is supposed to succeed"""
    delete_result = sear(
            {
            "operation": "delete",
            "admin_type": "user",
            "userid": create_user,
            },
        )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes

def test_delete_user_missing_userid():
    """This test is supposed to fail"""
    delete_result = sear(
            {
            "operation": "delete",
            "admin_type": "user",
            },
        )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes
