
from helper import successful_return_codes

# Import SEAR
from sear import sear


def test_add_dataset_permit(create_user, create_dataset):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "alter", 
            "admin_type": "permission", 
            "dataset": create_dataset,
            "userid": create_user,
            "generic": True,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_dataset_permit_missing_admin_type(create_user, create_dataset):
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "alter", 
            "dataset": create_dataset,
            "userid": create_user,
            "generic": True,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_dataset_permit_missing_operation(create_user, create_dataset):
    """This test is supposed to fail"""
    add_result = sear(
            {
            "admin_type": "permission", 
            "dataset": create_dataset,
            "userid": create_user,
            "generic": True,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_dataset_permit_missing_userid(create_dataset):
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "alter", 
            "admin_type": "permission", 
            "dataset": create_dataset,
            "generic": True,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_resource_permit(create_user, create_resource):
    """This test is supposed to succeed"""
    profile_name, class_name = create_resource
    add_result = sear(
            {
            "operation": "alter", 
            "admin_type": "permission", 
            "resource": profile_name,
            "class": class_name,
            "userid": create_user,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_resource_permit_missing_class(create_user, create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    add_result = sear(
            {
            "operation": "alter", 
            "admin_type": "permission", 
            "resource": profile_name,
            "userid": create_user,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes


def test_add_resource_permit_missing_operation(create_user, create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    add_result = sear(
            {
            "admin_type": "permission", 
            "resource": profile_name,
            "class": class_name,
            "userid": create_user,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_resource_permit_missing_admin_type(create_user, create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    add_result = sear(
            {
            "operation": "alter", 
            "resource": profile_name,
            "class": class_name,
            "userid": create_user,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_resource_permit_missing_userid(create_resource):
    """This test is supposed to fail"""
    profile_name, class_name = create_resource
    add_result = sear(
            {
            "operation": "alter", 
            "admin_type": "permission", 
            "resource": profile_name,
            "class": class_name,
            "traits": {
                "base:access": "READ",
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes