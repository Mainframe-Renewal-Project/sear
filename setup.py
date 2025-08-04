"""Build Python extension."""

import json
import os
import subprocess
from glob import glob
from pathlib import Path

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext
from wheel.bdist_wheel import bdist_wheel as _bdist_wheel


class bdist_wheel(_bdist_wheel): # noqa: N801
    def finalize_options(self):
        super().finalize_options()

        self.py_limited_api = "cp312"

def assemble(asm_file: str, asm_directory: Path) -> None:
    """Assemble assembler code."""
    obj_file = asm_file.split(".")[0] + ".o"
    cwd = Path.cwd()
    source_file = cwd / asm_directory / asm_file
    obj_file = cwd / "artifacts" / obj_file

    if obj_file.exists():
        return

    print(f"assembling {source_file}")

    if not obj_file.parents[0].is_dir():
        mkdir_command = f"mkdir {obj_file.parents[0]}"
        print(mkdir_command)
        subprocess.run(mkdir_command, shell=True, check=True)

    assemble_command = (
        f"as -mGOFF -I{source_file.parents[0]} -o {obj_file} {source_file}"
    )
    print(assemble_command)
    subprocess.run(assemble_command, shell=True, check=True)


def generate_json_schema_header() -> None:
    """Generate SEAR JSON schema header."""
    schema_absolute_path = Path.cwd() / "schema.json"
    with open(schema_absolute_path) as f:
        schema = json.dumps(json.load(f), separators=(",", ":"))
    schema_header_absolute_path = Path.cwd() / "sear" / "sear_schema.hpp"
    with open(schema_header_absolute_path, "w") as f:
        f.write(
            "\n".join(
                [
                    "#ifndef __SEAR_SCHEMA_H_",
                    "#define __SEAR_SCHEMA_H_",
                    "",
                    f'#define SEAR_SCHEMA R"({schema})"_json',
                    "",
                    "#endif",
                ],
            ),
        )


class BuildExtensionWithAssemblerAndC(build_ext):
    """Build Python extension that includes assembler code."""

    def run(self):
        os.environ["CC"] = "ibm-clang64"
        os.environ["CFLAGS"] = "-std=c99"
        os.environ["CXX"] = "ibm-clang++64"
        os.environ["CXXFLAGS"] = "-std=c++14"
        sear_source_path = Path("sear")
        assemble("irrseq00.s", sear_source_path / "irrseq00")
        super().run()


def main():
    """Python extension build entrypoint."""
    cwd = Path.cwd()
    # Use ZOPEN_ROOTFS to find OpenSSL and ZOSLIB.
    if "ZOPEN_ROOTFS" not in os.environ:
        raise RuntimeError(
            "ZOPEN_ROOTFS is not set, but is required in order to "
            + "find the zopen community distributions of of OpenSSL "
            + "and ZOSLIB since they are build dependencies.\n"
            + "You can find more information about setting up zopen "
            + "community here: "
            + "https://zopen.community/#/Guides/QuickStart?id=installing-zopen-package-manager",
        )
    assembled_object_path = cwd / "artifacts" / "irrseq00.o"
    generate_json_schema_header()
    setup_args = {
        "ext_modules": [
            Extension(
                "sear._C",
                sources=(
                    glob("sear/**/*.cpp")
                    + glob("sear/*.cpp")
                    + glob("externals/json-schema-validator/*.cpp")
                    + ["sear/python/_sear.c"]
                ),
                include_dirs=(
                    glob("sear/**/")
                    + [
                        "sear",
                        "externals/json",
                        "externals/json-schema-validator",
                        os.environ["ZOPEN_ROOTFS"] + "/usr/local/include",
                    ]
                ),
                extra_link_args=[
                    "-m64",
                    "-Wl,-b,edit=no",
                    "-Wl," + os.environ["ZOPEN_ROOTFS"] + "/usr/local/lib/libcrypto.a",
                    "-Wl," + os.environ["ZOPEN_ROOTFS"] + "/usr/local/lib/libssl.a",
                    "-Wl," + os.environ["ZOPEN_ROOTFS"] + "/usr/local/lib/libzoslib.a",
                ],
                extra_objects=[f"{assembled_object_path}"],
            ),
        ],
        "cmdclass": {
            "build_ext": BuildExtensionWithAssemblerAndC,
            "bdist_wheel": bdist_wheel,
            },
    }
    setup(**setup_args)

if __name__ == "__main__":
    main()