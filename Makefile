SRC_DIR := src/

INPUT_FILE := $(SRC_DIR)main.c
CFLAGS := -g
TARGET := run_emu

debug: $(SRC_DIR)main.c
	cc $(CFLAGS) $(INPUT_FILE) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm $(TARGET)

