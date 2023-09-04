TARGETNAME = $(shell basename -a $(wildcard ./src/*.c))
TESTNAME = $(basename $(TARGETNAME) .c)

CC = gcc 
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC
CPPFLAGS = -I ./include
LDFLAGS = -lds -L bin/debug/. -Wl,-rpath=bin/debug/.
DEBUG = -g
REL = -DNDEBUG -O3


SRC_DIR = src
BIN_DIR = bin
DBG_DIR = bin/debug
REL_DIR = bin/release

SOURCES =  $(wildcard $(SRC_DIR)/*.c)
DEBUG_OBJ = $(subst $(SRC_DIR),$(BIN_DIR),$(SOURCES:.c=.o))
REL_OBJ = $(subst $(SRC_DIR),$(BIN_DIR),$(SOURCES:.c=.O))

LIB = libds.so

GD := $(CC) $(CFLAGS) $(DEBUG) $(CPPFLAGS)
GC := $(CC) $(CFLAGS) $(REL) $(CPPFLAGS)


.PHONY: debug release test clean all

all: release debug clean

test : debug  
	$(foreach d, $(TESTNAME), $(GD) ./test/$d_test.c -o ./bin/$d_debug.out \
							    $(LDFLAGS);)

debug: $(DEBUG_OBJ)
	$(GD) -shared -o $(DBG_DIR)/$(LIB) $?


release: $(REL_OBJ)
	$(GC) -shared -o $(REL_DIR)/$(LIB) $?


clean: 
	rm -f $(DEBUG_OBJ) $(REL_OBJ) ./bin/*.out


$(BIN_DIR)/%.O: $(SRC_DIR)/%.c
	$(GC) -c -o $@ $<


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(GD) -c -o $@ $<

