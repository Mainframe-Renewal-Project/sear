UNAME := $(shell uname)

ARTIFACTS		= ${PWD}/artifacts
DIST			= ${PWD}/dist

# Directory Paths
SRC				= ${PWD}/sear
IRRSMO00_SRC	= ${PWD}/sear/irrsmo00
IRRSEQ00_SRC	= ${PWD}/sear/irrseq00
IRRSDL00_SRC	= ${PWD}/sear/irrsdl00
KEY_MAP			= ${PWD}/sear/key_map
VALIDATION		= ${PWD}/sear/validation
EXTERNALS		= ${PWD}/externals
JSON			= $(EXTERNALS)/json
JSON_SCHEMA		= $(EXTERNALS)/json-schema-validator
ICONV			= $(EXTERNALS)/iconv
TESTS			= ${PWD}/tests
ZOSLIB			= $(TESTS)/zoslib

CSTANDARD		= c99
CXXSTANDARD		= c++14

COMMON_INC		= \
				-I $(SRC) \
				-I $(IRRSMO00_SRC) \
				-I $(IRRSEQ00_SRC) \
				-I $(IRRSDL00_SRC) \
				-I $(KEY_MAP) \
				-I $(VALIDATION) \
				-I $(JSON) \
				-I $(JSON_SCHEMA)
				-I $(ICONV) \

# JSON Schemas
SEAR_SCHEMA	= $(shell cat ${PWD}/schema.json | jq -c)

ifeq ($(UNAME), Linux)
	CLANG_FORMAT	= clang-format-19
else
	CLANG_FORMAT	= clang-format
endif

# z/OS
ifeq ($(UNAME), OS/390)
	AS			= as
	CC			= ibm-clang64
	CXX			= ibm-clang++64

	SRCZOSLIB	=

	ASFLAGS		= -mGOFF -I$(IRRSEQ00_SRC)
	CFLAGS		= \
				-std=$(CXXSTANDARD) -m64 -fzos-le-char-mode=ascii \
				-D_POSIX_C_SOURCE=200112L \
				-I ${ZOPEN_ROOTFS}/usr/local/include \
				$(COMMON_INC)
	TFLAGS		= \
				-DUNIT_TEST -DUNITY_OUTPUT_COLOR \
				-I ${PWD} \
				-I $(TESTS)/mock
	LDFLAGS		= \
				-m64 -Wl,-b,edit=no \
				-Wl,${ZOPEN_ROOTFS}/usr/local/lib/libcrypto.a \
				-Wl,${ZOPEN_ROOTFS}/usr/local/lib/libssl.a \
				-Wl,${ZOPEN_ROOTFS}/usr/local/lib/libzoslib.a
# Mac
else ifeq ($(UNAME), Darwin)
	CC			= clang
	CXX			= clang++

	SRCZOSLIB	= $(ZOSLIB)/*.c

	CFLAGS		= \
				-std=$(CXXSTANDARD) -D__ptr32= \
				-D_POSIX_C_SOURCE=200112L \
				-I /opt/homebrew/include \
				$(COMMON_INC)
	TFLAGS		= \
				-DUNIT_TEST -DUNITY_OUTPUT_COLOR -gdwarf \
				-I ${PWD} \
				-I $(TESTS)/mock \
				-I $(ZOSLIB)
	LDFLAGS		= \
			-Wl,/opt/homebrew/lib/libssl.a \
			-Wl,/opt/homebrew/lib/libcrypto.a
# Linux
else
	CC			= clang
	CXX			= clang++

	SRCZOSLIB	= $(ZOSLIB)/*.c

	CFLAGS		= \
				-std=$(CXXSTANDARD) -D__ptr32= \
				-D_POSIX_C_SOURCE=200112L \
				$(COMMON_INC)
	TFLAGS		= \
				-DUNIT_TEST -DUNITY_OUTPUT_COLOR -gdwarf \
				-I ${PWD} \
				-I $(TESTS)/mock \
				-I $(ZOSLIB)
	LDFLAGS		= \
				-Wl,/usr/lib/x86_64-linux-gnu/libssl.so \
				-Wl,/usr/lib/x86_64-linux-gnu/libcrypto.so
endif

FUZZFLGS	= \
			-fsanitize=fuzzer \
			-fsanitize=undefined \
			-fsanitize=address

RM				= rm -rf

all: sear

mkdirs:
	mkdir $(ARTIFACTS)
	mkdir $(DIST)

schema:
	@echo "#ifndef __SEAR_SCHEMA_H_\n"\
	"#define __SEAR_SCHEMA_H_\n\n"\
	"#define SEAR_SCHEMA" 'R"($(SEAR_SCHEMA))"_json'\
	"\n\n#endif" > $(SRC)/sear_schema.hpp

sear: clean mkdirs schema
	$(AS) $(ASFLAGS) -o $(ARTIFACTS)/irrseq00.o $(IRRSEQ00_SRC)/irrseq00.s
	cd $(ARTIFACTS) \
		&& $(CXX) -g -c $(CFLAGS) \
			$(SRC)/*.cpp \
			$(IRRSMO00_SRC)/*.cpp \
			$(IRRSEQ00_SRC)/*.cpp \
			$(IRRSDL00_SRC)/*.cpp \
			$(KEY_MAP)/*.cpp \
			$(VALIDATION)/*.cpp \
			$(JSON_SCHEMA)/*.cpp
	cd $(DIST) && $(CXX) $(LDFLAGS) $(ARTIFACTS)/*.o -o sear.so

test: clean mkdirs schema
	cd $(ARTIFACTS) \
		&& $(CXX) -g -c $(CFLAGS) $(TFLAGS) \
			$(TESTS)/unity/unity.c \
			$(TESTS)/mock/*.cpp \
			$(SRCZOSLIB) \
			$(SRC)/*.cpp \
			$(IRRSMO00_SRC)/*.cpp \
			$(IRRSEQ00_SRC)/*.cpp \
			$(IRRSDL00_SRC)/*.cpp \
			$(KEY_MAP)/*.cpp \
			$(VALIDATION)/*.cpp \
			$(JSON_SCHEMA)/*.cpp \
			$(TESTS)/*.cpp \
			$(TESTS)/irrsmo00/*.cpp \
			$(TESTS)/irrseq00/*.cpp \
			$(TESTS)/irrsdl00/*.cpp \
			$(TESTS)/validation/*.cpp \
		&& $(CXX) $(LDFLAGS) *.o -o $(DIST)/test_runner
	$(DIST)/test_runner

fuzz: clean mkdirs schema
	cd $(ARTIFACTS) \
		&& $(CXX) -g -c $(CFLAGS) $(TFLAGS) $(FUZZFLGS) \
			$(TESTS)/fuzz.cpp \
			$(TESTS)/mock/*.cpp \
			$(SRCZOSLIB) \
			$(SRC)/*.cpp \
			$(IRRSMO00_SRC)/*.cpp \
			$(IRRSEQ00_SRC)/*.cpp \
			$(IRRSDL00_SRC)/*.cpp \
			$(KEY_MAP)/*.cpp \
			$(VALIDATION)/*.cpp \
			$(JSON_SCHEMA)/*.cpp \
		&& $(CXX) $(LDFLAGS) $(FUZZFLGS) *.o -o $(DIST)/fuzz
	ASAN_OPTIONS=alloc_dealloc_mismatch=1 \
	$(DIST)/fuzz -runs=65536 -artifact_prefix=$(ARTIFACTS)/

fvt: 
	python3 $(TESTS)/fvt/fvt.py

dbg:
	cd $(ARTIFACTS) && $(CC) -m64 -std=$(CSTANDARD) -fzos-le-char-mode=ascii \
		-o $(DIST)/debug \
		${PWD}/debug/debug.c

check: schema
	cppcheck \
		--suppress='missingIncludeSystem' \
		--suppress='useStlAlgorithm' \
		--inline-suppr \
		--language=c++ \
		--std=$(CXXSTANDARD) \
		--enable=all \
		--force \
		--check-level=exhaustive \
		--inconclusive \
		--error-exitcode=1 \
		-U __TOS_390__ -D __ptr32= \
		-D _POSIX_C_SOURCE=200112L \
		-I $(SRC) \
		-I $(IRRSMO00_SRC) \
		-I $(IRRSEQ00_SRC) \
		-I $(IRRSDL00_SRC) \
		-I $(KEY_MAP) \
		-I $(VALIDATION) \
		-I $(ZOSLIB) \
		-I $(TESTS)/irrsdl00 \
		$(SRC)/

lint:
	$(CLANG_FORMAT) --Werror --dry-run -i ./**/*.cpp ./**/*.c ./**/*.hpp ./**/*.h

clean:
	$(RM) $(ARTIFACTS) $(DIST) $(SRC)/sear_schema.hpp
