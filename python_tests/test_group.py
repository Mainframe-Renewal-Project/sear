
from helper import successful_return_codes

# Import SEAR
from sear import sear


def test_add_group(delete_group):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "profile_type": "group", 
            "group": delete_group,
            "traits": {
                "base:installation_data": "GROUP GENERATED DURING SEAR TESTING, NOT IMPORTANT",
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_group_no_traits(delete_group):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "profile_type": "group", 
            "group": delete_group,
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_extract_group(create_group):
    """This test is supposed to succeed"""
    extract_result = sear(
            {
            "operation": "extract",
            "profile_type": "group",
            "group": create_group,
            },
        )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_extract_group_missing_group():
    """This test is supposed to fail"""
    extract_result = sear(
            {
            "operation": "extract",
            "profile_type": "group",
            },
        )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes

def test_group_not_found():
    """This test is supposed to fail"""
    not_found_result = sear(
            {
            "operation": "extract",
            "profile_type": "group", 
            "data_set": "BADGRP",
            },
        )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != successful_return_codes

def test_alter_group(create_group):
    """This test is supposed to succeed"""
    alter_result = sear(
            {
            "operation": "alter", 
            "profile_type": "group", 
            "group": create_group,
            "traits": {
                "omvs:auto_gid": True,
            },
            },
        )
    assert "errors" not in str(alter_result.result)
    assert alter_result.result["return_codes"] == successful_return_codes

def test_delete_group(create_group):
    """This test is supposed to succeed"""
    delete_result = sear(
            {
            "operation": "delete",
            "profile_type": "group",
            "group": create_group,
            },
        )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes

def test_delete_group_missing_group(create_group):
    """This test is supposed to fail"""
    delete_result = sear(
            {
            "operation": "delete",
            "profile_type": "group",
            },
        )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes
