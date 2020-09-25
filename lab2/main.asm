%include "words.inc"

%define DICT_START l
%define KEY_MAX_SIZE 255
%define STDOUT 1
%define STDERR 2


global _start

extern read_word
extern find_word
extern string_length
extern print_string
extern print_newline
extern exit

section .data
	error_msg: db "Error: Non-Existent key", 0

section .text

_start:

	mov rsi, KEY_MAX_SIZE
	sub rsp, KEY_MAX_SIZE
	mov rdi, rsp
	call read_word			; Read key into rax

	test rax, rax			; Check if word is null?
	je .error

	mov rdi, rax
	mov rsi, DICT_START
	call find_word			; Check dictionary for key

	test rax, rax
	je .error               ; Check if no such key

	add rax, 8
	mov r10, rax
	mov rdi, rax
	call string_length      ;

	add r10, rax			; сдвинем указатель на начало метки
	inc r10					; учитываем \0
	mov rdi, r10

	mov r15, STDOUT				; stdout
	call print_string

.exit:
	call print_newline
	mov rax, 60
	mov rdi, rax
	syscall
	ret

.error:
	mov rdi, error_msg
	call string_length
	mov rsi, rax

	mov r15, STDERR				; stderr
	call print_string
	jmp .exit