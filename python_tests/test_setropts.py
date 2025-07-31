
from helper import successful_return_codes

# Import SEAR
from sear import sear


def test_setropts_extract():
    """This test is supposed to succeed"""
    extract_result = sear(
        {
        "operation": "extract",
        "profile_type": "racf-options",
        },
    )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_setropts_extract_missing_operation():
    """This test is supposed to fail"""
    extract_result = sear(
        {
        "profile_type": "racf-options",
        },
    )
    assert "errors" in str(extract_result.result)
    assert extract_result.result["return_codes"] != successful_return_codes
