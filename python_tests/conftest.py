
import secrets
import subprocess

import pytest

# certificate stuff
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import hashes, serialization
import datetime

# File management
from pathlib import Path

def run_tso_command(command: str):
    """Runs a supplied TSO command"""
    subprocess.run(
        f'tsocmd "{command}"', 
        text=False, 
        shell=True, 
        check=True, 
        capture_output=True,
        )

def run_shell_command(command: str):
    """Runs a supplied shell command"""
    subprocess.run(
        command, 
        text=False, 
        shell=True, 
        check=True, 
        capture_output=True,
        )

@pytest.fixture
def delete_user():
    userid=f"SEAR{secrets.token_hex(2)}".upper()
    yield userid
    try:  # noqa: SIM105
        run_tso_command(f"deluser {userid}")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_user(delete_user):
    """Create a new RACF user for a test"""
    run_tso_command(f"ADDUSER {delete_user} DATA('USER GENERATED DURING SEAR TESTING, NOT IMPORTANT')")  # noqa: E501
    yield delete_user

@pytest.fixture
def delete_group():
    groupid=f"SEAR{secrets.token_hex(2)}".upper()
    yield groupid
    try:  # noqa: SIM105
        run_tso_command(f"DELGROUP {groupid}")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_group(delete_group):
    """Create a RACF group for a test"""
    run_tso_command(f"ADDGROUP {delete_group} DATA('GROUP GENERATED DURING SEAR TESTING, NOT IMPORTANT')")  # noqa: E501
    yield delete_group

@pytest.fixture
def delete_dataset():
    profile_name=f"SEARTEST.TEST{secrets.token_hex(2)}.**".upper()
    yield profile_name
    try:  # noqa: SIM105
        run_tso_command(f"DELDSD ({profile_name})")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_dataset(delete_dataset):
    """Create a new RACF dataset profile for a test"""
    run_tso_command(f"ADDSD ('{delete_dataset}') DATA('DATASET PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT') OWNER(SYS1)")  # noqa: E501
    run_tso_command("SETROPTS GENERIC(DATASET) REFRESH")
    yield delete_dataset

@pytest.fixture
def delete_resource():
    profile_name=f"SEARTEST.JUNK{secrets.token_hex(2)}.**".upper()
    class_name = "FACILITY"
    yield profile_name, class_name
    try:  # noqa: SIM105
        run_tso_command(f"RDELETE {class_name} ({profile_name})")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_resource(delete_resource):
    """Create a new resource profile for a test"""
    profile_name, class_name = delete_resource
    run_tso_command(f"RDEFINE {class_name} {profile_name} DATA('RESOURCE PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT') OWNER(SYS1) FGENERIC")  # noqa: E501
    run_tso_command(f"SETROPTS GENERIC({class_name}) REFRESH")
    run_tso_command(f"SETROPTS RACLIST({class_name}) REFRESH")
    yield profile_name, class_name

@pytest.fixture
def delete_resource_in_search_class():
    profile_name=f"SEARTEST.DISCRETE{secrets.token_hex(2)}.**".upper()
    class_name = "SEARTEST"
    yield profile_name, class_name
    try:  # noqa: SIM105
        run_tso_command(f"RDELETE {class_name} ({profile_name})")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_resource_in_search_class(delete_resource_in_search_class):
    """Create a new resource profile for a test"""
    profile_name, class_name = delete_resource_in_search_class
    run_tso_command(f"RDEFINE {class_name} {profile_name} DATA('RESOURCE PROFILE GENERATED DURING SEAR TESTING, NOT IMPORTANT') OWNER(SYS1) FGENERIC")  # noqa: E501
    run_tso_command(f"SETROPTS GENERIC({class_name}) REFRESH")
    run_tso_command(f"SETROPTS RACLIST({class_name}) REFRESH")
    yield profile_name, class_name

@pytest.fixture
def delete_keyring():
    ring_name=f"SEARTEST.RING{secrets.token_hex(2)}".upper()
    owner = "SEARTEST"
    yield ring_name, owner
    try:  # noqa: SIM105
        run_tso_command(f"RACDCERT DELRING({ring_name}) ID({owner})")
        run_tso_command("SETROPTS RACLIST(DIGTRING) REFRESH")
    except:  # noqa: E722
        pass

@pytest.fixture
def create_keyring(delete_keyring):
    """Create a new RACF keyring for a test"""
    ring_name, owner = delete_keyring
    run_tso_command(f"RACDCERT ADDRING({ring_name}) ID({owner})")  # noqa: E501
    run_tso_command("SETROPTS RACLIST(DIGTCERT, DIGTRING) REFRESH")
    yield ring_name, owner

@pytest.fixture
def delete_certificate():
    certificate_name=f"./certificate_{secrets.token_hex(4)}"
    certificate_label=f"SEARTestCert{secrets.token_hex(8)}"
    certificate_file = Path(certificate_name)
    yield certificate_name, certificate_label, certificate_file
    try:  # noqa: SIM105
        certificate_file.unlink()
    except:  # noqa: E722
        pass

@pytest.fixture
def create_certificate_pem(delete_certificate):
    """creates an x509 certificate in PEM format"""
    certificate_filename, certificate_label, certificate_file = delete_certificate
    # Generate our key
    key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
    )

    subject = issuer = x509.Name([
        x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Mainframe Renewal Project"),
        x509.NameAttribute(NameOID.COMMON_NAME, "SEAR"),
    ])

    cert = x509.CertificateBuilder().subject_name(
        subject
    ).issuer_name(
        issuer
    ).public_key(
        key.public_key()
    ).serial_number(
        x509.random_serial_number()
    ).not_valid_before(
        datetime.datetime.now(datetime.timezone.utc)
    ).not_valid_after(
        # Our certificate will be valid for 2 days
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(days=2)
    ).add_extension(
        x509.SubjectAlternativeName([x509.DNSName("localhost")]),
        critical=False,
    # Sign our certificate with our private key
    ).sign(key, hashes.SHA256())

    # Make sure the file that the certificate will be written to has the right encoding
    certificate_file.touch(mode=0o700)
    run_shell_command(f"chtag -tc ISO8859-1 {certificate_filename}")

    certificate_file.write_bytes(cert.public_bytes(serialization.Encoding.PEM))

    yield certificate_filename, certificate_label

@pytest.fixture
def create_certificate_der(delete_certificate):
    """creates an x509 certificate in DER format"""
    certificate_filename, certificate_label, certificate_file = delete_certificate
    # Generate our key
    key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
    )

    subject = issuer = x509.Name([
        x509.NameAttribute(NameOID.ORGANIZATION_NAME, "Mainframe Renewal Project"),
        x509.NameAttribute(NameOID.COMMON_NAME, "SEAR"),
    ])

    cert = x509.CertificateBuilder().subject_name(
        subject
    ).issuer_name(
        issuer
    ).public_key(
        key.public_key()
    ).serial_number(
        x509.random_serial_number()
    ).not_valid_before(
        datetime.datetime.now(datetime.timezone.utc)
    ).not_valid_after(
        # Our certificate will be valid for 2 days
        datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(days=2)
    ).add_extension(
        x509.SubjectAlternativeName([x509.DNSName("localhost")]),
        critical=False,
    # Sign our certificate with our private key
    ).sign(key, hashes.SHA256())

    # Make sure the file that the certificate will be written to has the right encoding
    certificate_file.touch(mode=0o700)
    run_shell_command(f"chtag -tc ISO8859-1 {certificate_filename}")

    certificate_file.write_bytes(cert.public_bytes(serialization.Encoding.DER))

    yield certificate_filename, certificate_label
