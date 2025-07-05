
from helper import keyring_not_found_return_codes, successful_return_codes, successful_return_codes_cert

# Import SEAR
from sear import sear


def test_extract_keyring_not_found():
    """This test is supposed to fail"""
    not_found_result = sear(
        {
        "operation": "extract", 
        "admin_type": "keyring", 
        "keyring": "SEARNOTFOUND",
        "owner": "IBMUSER",
        },
    )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] == keyring_not_found_return_codes

def test_extract_keyring_missing_admin_type():
    """This test is supposed to fail"""
    not_found_result = sear(
        {
        "operation": "extract", 
        "keyring": "SEARNOTFOUND",
        "owner": "IBMUSER",
        },
    )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != keyring_not_found_return_codes

def test_extract_keyring_missing_operation():
    """This test is supposed to fail"""
    not_found_result = sear(
        {
        "admin_type": "keyring", 
        "keyring": "SEARNOTFOUND",
        "owner": "IBMUSER",
        },
    )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != keyring_not_found_return_codes

def test_extract_keyring_missing_owner():
    """This test is supposed to fail"""
    not_found_result = sear(
        {
        "operation": "extract", 
        "admin_type": "keyring", 
        "keyring": "SEARNOTFOUND",
        },
    )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != keyring_not_found_return_codes

def test_extract_keyring_missing_keyring():
    """This test is supposed to fail"""
    not_found_result = sear(
        {
        "operation": "extract", 
        "admin_type": "keyring", 
        "owner": "IBMUSER",
        },
    )
    assert "errors" in str(not_found_result.result)
    assert not_found_result.result["return_codes"] != keyring_not_found_return_codes

def test_extract_keyring(create_keyring):
    """This test is supposed to succeed"""
    keyring, owner = create_keyring

    extract_result = sear(
        {
        "operation": "extract", 
        "admin_type": "keyring", 
        "keyring": keyring,
        "owner": owner,
        },
    )
    assert "errors" not in str(extract_result.result)
    assert extract_result.result["return_codes"] == successful_return_codes

def test_add_keyring(delete_keyring):
    """This test is supposed to succeed"""
    keyring, owner = delete_keyring

    add_result = sear(
        {
        "operation": "add", 
        "admin_type": "keyring", 
        "keyring": keyring,
        "owner": owner,
        },
    )
    assert "errors" not in str(add_result.result)
    assert add_result.result["return_codes"] == successful_return_codes

def test_add_keyring_missing_owner(delete_keyring):
    """This test is supposed to fail"""
    keyring, owner = delete_keyring

    add_result = sear(
        {
        "operation": "add", 
        "admin_type": "keyring", 
        "keyring": keyring,
        },
    )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_add_keyring_missing_keyring(delete_keyring):
    """This test is supposed to fail"""
    keyring, owner = delete_keyring

    add_result = sear(
        {
        "operation": "add", 
        "admin_type": "keyring", 
        "owner": owner,
        },
    )
    assert "errors" in str(add_result.result)
    assert add_result.result["return_codes"] != successful_return_codes

def test_delete_keyring(create_keyring):
    """This test is supposed to succeed"""
    keyring, owner = create_keyring

    delete_result = sear(
        {
        "operation": "delete", 
        "admin_type": "keyring", 
        "keyring": keyring,
        "owner": owner,
        },
    )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes

def test_delete_keyring_missing_owner(create_keyring):
    """This test is supposed to fail"""
    keyring, owner = create_keyring

    delete_result = sear(
        {
        "operation": "delete", 
        "admin_type": "keyring", 
        "keyring": keyring,
        },
    )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes

def test_delete_keyring_missing_keyring(create_keyring):
    """This test is supposed to fail"""
    keyring, owner = create_keyring

    delete_result = sear(
        {
        "operation": "delete", 
        "admin_type": "keyring", 
        "owner": owner,
        },
    )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes

def test_add_pem_certificate_to_keyring(create_keyring, create_certificate_pem):
    """This test is supposed to succeed"""
    keyring, owner = create_keyring
    cert_file = create_certificate_pem

    delete_result = sear(
        {
        "operation": "add",
        "admin_type": "certificate",
        "owner": owner,
        "keyring": keyring,
        "keyring_owner": owner,
        "label": "NewTrustedCert",
        "certificate_file": cert_file,
        "usage": "personal",
        "status": "NOTRUST"
        }
    )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes_cert

def test_add_der_certificate_to_keyring(create_keyring, create_certificate_der):
    """This test is supposed to succeed"""
    keyring, owner = create_keyring
    cert_file = create_certificate_der

    delete_result = sear(
        {
        "operation": "add",
        "admin_type": "certificate",
        "owner": owner,
        "keyring": keyring,
        "keyring_owner": owner,
        "label": "NewTrustedCert",
        "certificate_file": cert_file,
        "usage": "personal",
        "status": "NOTRUST"
        }
    )
    assert "errors" not in str(delete_result.result)
    assert delete_result.result["return_codes"] == successful_return_codes_cert

def test_add_certificate_to_keyring_missing_certificate(create_keyring):
    """This test is supposed to fail"""
    keyring, owner = create_keyring

    delete_result = sear(
        {
        "operation": "add",
        "admin_type": "certificate",
        "owner": owner,
        "keyring": keyring,
        "keyring_owner": owner,
        "label": "NewTrustedCert",
        "usage": "personal",
        "status": "TRUST"
        }
    )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes

def test_add_certificate_to_keyring_missing_keyring(create_keyring, create_certificate):
    """This test is supposed to fail"""
    keyring, owner = create_keyring
    cert_file = create_certificate

    delete_result = sear(
        {
        "operation": "add",
        "admin_type": "certificate",
        "owner": owner,
        "keyring_owner": owner,
        "label": "NewTrustedCert",
        "certificate_file": cert_file,
        "usage": "personal",
        "status": "TRUST"
        }
    )
    assert "errors" in str(delete_result.result)
    assert delete_result.result["return_codes"] != successful_return_codes
