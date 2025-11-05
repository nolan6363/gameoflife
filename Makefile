CC = gcc
HEADER_DIR = include
CFLAGS = -Wall -O2 -I$(HEADER_DIR)
SRC_DIR = src
BIN_DIR = bin

LIBS = 

all: $(BIN_DIR)/main 

$(BIN_DIR)/main: $(SRC_DIR)/main.c
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

run: $(BIN_DIR)/main
	@./$(BIN_DIR)/main

clean:
	@rm "$(BIN_DIR)/main"
