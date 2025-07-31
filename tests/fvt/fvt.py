import getpass
import json
import os

from sear import sear

# This user shouldn't exist
if "SEAR_FVT_USERID" not in os.environ:
  print(
    "The 'SEAR_FVT_USERID' environment variable must be set "
    + "to a z/OS userid that does NOT exist on the system.")
  exit(1)

# This request may fail, but regardless, it demonstrates that 
# we can make a request to IRRSEQ00 and get a result back.
extract_request = {
  "profile_type": "user",
  "operation": "extract",
  "userid": getpass.getuser(),
}

# This request will fail, but it demonstrates that
# we can make a request to IRRSMO00 and get a result back.
delete_request = {
  "profile_type": "user",
  "operation": "delete",
  "userid": os.environ["SEAR_FVT_USERID"],
}

print("Extract Test (IRRSEQ00):")
result = sear(extract_request)
print(json.dumps(result.result, indent=2))

print("Delete Test (IRRSMO00):")
result = sear(delete_request)
print(json.dumps(result.result, indent=2))

print("Debug Test (IRRSMO00):")
result = sear(delete_request, debug=True)
print(json.dumps(result.result, indent=2))