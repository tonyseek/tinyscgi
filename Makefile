CMAKE = cmake
TARGET_DIR = build
SOURCE_DIR = $(CURDIR)

ifeq ($(DEBUG), 1)
	CMAKE_VARS := -DCMAKE_BUILD_TYPE=Debug
endif

all: build

prepare:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR); $(CMAKE) $(CMAKE_VARS) $(CURDIR)

build: prepare
	cd $(TARGET_DIR); $(MAKE)

test: build
	cd $(TARGET_DIR); CTEST_OUTPUT_ON_FAILURE=1 $(MAKE) test

clean:
	rm -rf $(TARGET_DIR)

.PHONY: all prepare build test clean
