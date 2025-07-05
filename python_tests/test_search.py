
from helper import successful_return_codes

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