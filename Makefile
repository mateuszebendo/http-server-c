CC = gcc
SRC_DIR = src
TEST_DIR = tests
BUILD_BIN = build/bin
BUILD_OBJ = build/obj

SRC_FILES = $(SRC_DIR)/server.c
TEST_FILES = $(TEST_DIR)/test_server.c

OBJ_FILES = $(BUILD_OBJ)/server.o
OBJ_TEST_FILES = $(BUILD_OBJ)/test_server.o

TARGET = $(BUILD_BIN)/test_server

all: $(TARGET)

$(BUILD_OBJ):
	mkdir -p $(BUILD_OBJ)

$(BUILD_BIN):
	mkdir -p $(BUILD_BIN)

$(TARGET): $(OBJ_FILES) $(OBJ_TEST_FILES) | $(BUILD_BIN)
	$(CC) $(OBJ_FILES) $(OBJ_TEST_FILES) -o $@

$(BUILD_OBJ)/server.o: $(SRC_DIR)/server.c | $(BUILD_OBJ)
	$(CC) -c $(SRC_DIR)/server.c -o $@

$(BUILD_OBJ)/test_server.o: $(TEST_DIR)/test_server.c | $(BUILD_OBJ)
	$(CC) -c $(TEST_DIR)/test_server.c -o $@

clean:
	rm -rf $(BUILD_OBJ) $(BUILD_BIN)
