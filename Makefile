CMAKE = cmake
TARGET_DIR = build
SOURCE_DIR = $(CURDIR)

all: build

prepare:
	mkdir -p $(TARGET_DIR)
	cd $(TARGET_DIR); $(CMAKE) $(CURDIR)

build: prepare
	cd $(TARGET_DIR); $(MAKE)

test: build
	cd $(TARGET_DIR); CTEST_OUTPUT_ON_FAILURE=1 $(MAKE) test

clean:
	rm -rf $(TARGET_DIR)

.PHONY: all prepare build test clean
