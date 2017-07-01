C_COMPILER=gcc
MKFILE_PATH := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
UNITY_ROOT=$(MKFILE_PATH)/vendor/Unity
TARGET_DIR=$(MKFILE_PATH)/build

TARGET=add_test
TEST_RUNNERS=$(MKFILE_PATH)/test/test_runners
SRC_FILES += $(UNITY_ROOT)/src/unity.c
SRC_FILES += $(MKFILE_PATH)/src/add.c
SRC_FILES += $(MKFILE_PATH)/test/test_add.c
SRC_FILES += $(MKFILE_PATH)/test/test_runners/test_add_runner.c
INC_DIRS=-I$(MKFILE_PATH)/src -I$(UNITY_ROOT)/src

all: default

clean:
	-rm $(TEST_RUNNERS)/*.c
	-rm $(TARGET_DIR)/*_test

default: $(SRC_FILES)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SRC_FILES) -o $(TARGET_DIR)/$(TARGET)
	$(TARGET_DIR)/$(TARGET)	# Execute test

$(TEST_RUNNERS)/test_add_runner.c: test/test_add.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb \
		test/test_add.c	\
			$(TEST_RUNNERS)/test_add_runner.c
