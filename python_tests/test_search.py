
from helper import successful_return_codes, successful_return_codes_search

# Import SEAR
from sear import sear


def test_search_admin_type_missing():
    """This test is supposed to fail"""
    search_result = sear(
            {
            "operation": "search", 
            },
        )
    assert "errors" in str(search_result.result)
    assert search_result.result["return_codes"] != successful_return_codes

def test_search_resource_profiles_class_missing():
    """This test is supposed to fail"""
    search_result = sear(
            {
            "operation": "search", 
            "admin_type": "resource", 
            },
        )
    assert "errors" in str(search_result.result)
    assert search_result.result["return_codes"] != successful_return_codes

def test_search_resource_profiles_nonexistent_class():
    """This test is supposed to fail"""
    search_result = sear(
            {
            "operation": "search", 
            "admin_type": "resource",
            "class": "WRONG", 
            },
        )
    assert "errors" in str(search_result.result)
    assert search_result.result["return_codes"] != successful_return_codes

def test_search_resource_profiles_all():
    """This test is supposed to succeed"""
    search_result = sear(
            {
            "operation": "search", 
            "admin_type": "resource",
            "class": "seartest", 
            },
        )
    assert "errors" not in str(search_result.result)
    assert search_result.result["return_codes"] == successful_return_codes_search

def test_search_resource_profiles_filter():
    """This test is supposed to succeed"""
    search_result = sear(
            {
            "operation": "search", 
            "admin_type": "resource",
            "class": "seartest", 
            "resource_filter": "filter",
            },
        )
    assert "errors" not in str(search_result.result)
    assert search_result.result["return_codes"] == successful_return_codes

def test_search_resource_profiles_discrete(create_resource_in_search_class):
    """This test is supposed to succeed"""
    profile_name, class_name = create_resource_in_search_class
    search_result = sear(
            {
            "operation": "search", 
            "admin_type": "resource",
            "class": class_name, 
            "resource_filter": f"{profile_name}",
            },
        )
    assert "errors" not in str(search_result.result)
    assert profile_name in search_result.result["profiles"]
    assert search_result.result["return_codes"] == successful_return_codes