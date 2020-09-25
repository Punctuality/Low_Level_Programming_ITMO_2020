NAME := main

SOURCES := $(wildcard *.asm)
ASM := nasm
LD := ld

ASM_FLAGS ?= -g -felf64

all: $(NAME)

$(NAME): $(patsubst %.asm,%.o,$(SOURCES))
	$(LD) $^ -o $@

%.o: %.asm Makefile
	$(ASM) $(ASM_FLAGS) $< -o $@

main.o: words.inc colon.inc

clean:
	$(RM) *.o
