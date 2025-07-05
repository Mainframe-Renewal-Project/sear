
from helper import dataset_not_found_return_codes, successful_return_codes

# Import SEAR
from sear import sear


def test_add_dataset(delete_dataset):
    """This test is supposed to succeed"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "dataset", 
            "dataset": delete_dataset,
            "traits": {
                "base:installation_data": "DATASET PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_dataset_incorrect_profile_name():
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "dataset", 
            "dataset": "^^.**",
            "traits": {
                "base:installation_data": "DATASET PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_dataset_missing_dataset():
    """This test is supposed to fail"""
    add_result = sear(
            {
            "operation": "add", 
            "admin_type": "dataset", 
            "traits": {
                "base:installation_data": "DATASET PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT",  # noqa: E501
            },
            },
        )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_extract_dataset(create_dataset):
    """This test is supposed to succeed"""
    extract_result = sear(
            {
            "operation": "extract",
            "admin_type": "dataset", 
            "dataset": create_dataset,
            },
        )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_dataset_extract_not_found():
    """This test is supposed to fail"""
    not_found_result = sear(
            {
            "operation": "extract",
            "admin_type": "dataset", 
            "dataset": "DOES.NOT.EXIST",
            },
        )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] == dataset_not_found_return_codes

def test_dataset_extract_dataset_missing():
    """This test is supposed to fail"""
    not_found_result = sear(
            {
            "operation": "extract",
            "admin_type": "dataset", 
            },
        )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] == dataset_not_found_return_codes

def test_dataset_extract_invalid_json():
    """This test is supposed to fail"""
    not_found_result = sear(
            {
            "operation": "extract",
            "admin_type": "dataset", 
            "data_set": "DOES.NOT.EXIST",
            },
        )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != successful_return_codes

def test_delete_dataset(create_dataset):
    """This test is supposed to succeed"""
    delete_result = sear(
            {
            "operation": "delete",
            "admin_type": "dataset", 
            "dataset": create_dataset,
            },
        )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes

def test_delete_dataset_invalid_json(create_dataset):
    """This test is supposed to fail"""
    delete_result = sear(
            {
            "operation": "delete",
            "admin_type": "dataset", 
            "data_set": create_dataset,
            },
        )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes

def test_delete_dataset_missing_dataset():
    """This test is supposed to fail"""
    delete_result = sear(
            {
            "operation": "delete",
            "admin_type": "dataset", 
            },
        )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes