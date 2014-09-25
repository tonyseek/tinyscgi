PREMAKE = premake4
BUILD_DIR = build
TARGET_DIR = target

help:
	@echo 'commands: test build clean'
.PHONY: help

test: build
	@echo
	@echo "--------------------------------------------------"
	@cd tests && ../target/tests
	@echo "--------------------------------------------------"
.PHONY: test

build:
	@$(PREMAKE) gmake
	@$(MAKE) -C $(BUILD_DIR)
.PHONY: build

clean:
	rm -rf '$(BUILD_DIR)'
	rm -rf '$(TARGET_DIR)'
.PHONY: clean
