# Security policy

To report a security vulnerability, use the [Report a vulnerability](https://github.com/Mainframe-Renewal-Project/sear/security/advisories/new) feature in GitHub.

## Security initiatives and quality assurance

### Linting

We have linters like Ruff and cppcheck set up to fix some of the code quality issues before code is pushed to production. It won't catch all issues but it does catch a lot and also ensures we have formatted our code in a readable manner.

### Test pipeline

To ensure we don't release bad builds we have integrated functional tests into our release pipeline. It tests real builds of SEAR's language interfaces against real code, on a real mainframe system. If a test fails it prevents the release of the language interfaces. These tests don't catch all of the potential problems, but it does prevent a lot of bad builds from being published to PyPi and GitHub.

### Code review

Pull requests and code reviews are required on our repositories to reduce risk of bad code being pushed to production.

### Build pipeline security

We have split up the test and build user for the pipeline, to make sure each step of the pipeline only has access to what it needs. We also make heavy use of GitHub secrets, SSH, and OpenID Connect, to ensure pipeline security.
