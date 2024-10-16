CC = g++
CFLAGS = -I../include
SRC = ../include/network.cpp server.cpp
BUILD_DIR = ../build
TARGET = $(BUILD_DIR)/server

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
