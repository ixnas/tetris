SRC_DIR := ./src
OBJ_DIR := ./obj
CC := clang
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lncurses
CFLAGS := -Wall -O3 -std=c89

all: clean prep build

clean:
	rm -r bin obj

prep:
	mkdir -p bin obj

build: $(OBJ_FILES)
	CC $(LDFLAGS) -o bin/tetris $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	CC $(CFLAGS) -c -o $@ $<
