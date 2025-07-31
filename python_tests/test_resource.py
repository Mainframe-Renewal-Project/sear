
from helper import successful_return_codes

# Import SEAR
from sear import sear


def test_add_resource_profile(delete_resource):
    """This test is supposed to succeed"""
    profile_name, class_name = delete_resource
    add_result = sear(
            {
            "operation": "add", 
            "profile_type": "resource", 
            "resource": profile_name,
            "class": class_name,
            "traits": {
                "base:installation_data": "RESOURCE PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_resource_profile_no_traits(delete_resource):
    """This test is supposed to succeed"""
    profile_name, class_name = delete_resource
    add_result = sear(
            {
            "operation": "add", 
            "profile_type": "resource", 
            "resource": profile_name,
            "class": class_name,
            },
        )
    assert add_result.result["return_codes"] == successful_return_codes

def test_extract_resource_profile(create_resource):
    """This test is supposed to succeed"""
    profile_name, class_name = create_resource
    extract_result = sear(
            {
            "operation": "extract", 
            "profile_type": "resource", 
            "resource": profile_name,
            "class": class_name,
            },
        )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_extract_resource_profile_missing_class(create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    extract_result = sear(
            {
            "operation": "extract", 
            "profile_type": "resource", 
            "resource": profile_name,
            },
        )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes

def test_resource_profile_not_found():
    """This test is supposed to fail"""
    not_found_result = sear(
            {
            "operation": "extract",
            "profile_type": "resource", 
            "resource": "REALLYBAD.PROFILE.HAH",
            "class": "APPL",
            },
        )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != successful_return_codes

#def test_alter_resource_profile(create_resource):
#    profile_name, class_name = create_resource
#    alter_result = sear(
#            {
#            "operation": "alter", 
#            "profile_type": "resource", 
#            "resource": profile_name,
#            "class": class_name,
#            "traits": {
#                "base:universal_access": "Read",
#            },
#            },
#        )
#    assert "errors" not in str(alter_result.result)
#    assert alter_result.result["return_codes"] == successful_return_codes

def test_delete_resource_profile(create_resource):
    """This test is supposed to succeed"""
    profile_name, class_name = create_resource
    delete_result = sear(
            {
            "operation": "delete", 
            "profile_type": "resource", 
            "resource": profile_name,
            "class": class_name,
            },
        )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes

def test_delete_resource_profile_missing_class(create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    delete_result = sear(
            {
            "operation": "delete", 
            "profile_type": "resource", 
            "resource": profile_name,
            },
        )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes