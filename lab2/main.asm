%include "words.inc"

%define DICT_START last_address
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
    reading_error_msg: db "Error: Reading problem", 0
	not_found_msg: db "Error: Non-Existent key", 0

section .text

_start:

	mov rsi, KEY_MAX_SIZE
	sub rsp, KEY_MAX_SIZE
	mov rdi, rsp
	call read_word			; Read key into rax

	test rax, rax			; Check if word is null or error?
	je .reading_error_exit

	mov rdi, rax
	mov rsi, DICT_START
	call find_word			; Check dictionary for key

	test rax, rax
	je .not_found_exit      ; Check if no such key

	add rax, 8              ; Set accumulator as a key pointer
	mov r10, rax            ; Save rax in r10
	mov rdi, rax            ; Provide string address for string_length
	call string_length      ; calc key length

	inc r10                 ; Skipping key string
	add r10, rax			; To access value string

	mov rdi, r10            ; Printing value string
	mov r8, STDOUT
	call print_string

	jmp .exit

.reading_error_exit:
	mov rdi, reading_error_msg
	call string_length
	mov rsi, rax

    jmp .error_exit

.not_found_exit:
	mov rdi, not_found_msg
	call string_length
	mov rsi, rax

	jmp .error_exit

.error_exit:
	mov r8, STDERR
	call print_string
	jmp .exit

.exit:
    call print_newline
    mov rax, 60
    mov rdi, rax
    syscall
    ret