
from helper import successful_return_codes

# Import SEAR
from sear import sear


def test_rsf_extract():
    """This test is supposed to succeed"""
    extract_result = sear(
        {
        "operation": "extract",
        "admin_type": "racf-rrsf",
        },
    )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_rsf_extract_missing_operation():
    """This test is supposed to fail"""
    extract_result = sear(
        {
        "admin_type": "racf-rrsf",
        },
    )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes

def test_rsf_extract_invalid_operation_add():
    """This test is supposed to fail"""
    extract_result = sear(
        {
        "operation": "add",
        "admin_type": "racf-rrsf",
        },
    )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes

def test_rsf_extract_invalid_operation_delete():
    """This test is supposed to fail"""
    extract_result = sear(
        {
        "operation": "delete",
        "admin_type": "racf-rrsf",
        },
    )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes

def test_rsf_extract_invalid_operation_search():
    """This test is supposed to fail"""
    extract_result = sear(
        {
        "operation": "search",
        "admin_type": "racf-rrsf",
        },
    )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes
