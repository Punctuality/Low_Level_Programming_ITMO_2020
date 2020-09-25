global find_word
extern string_equals

section .text

; args: rdi = key string pointer, rsi = list first elem -> returns: rax = address (found) or rax = 0 (not found)
find_word:

    mov r8, rdi

    .loop:
        mov r9, rsi

        test rsi, rsi                   ; Check if dictionary is empty (rsi = 0)
        je .exit_not_found

        mov rdi, r8
        add rsi, 8
        call string_equals				; Compare strings

        mov rsi, r9

        test rax, rax 					; If equals then exit
        jnz .exit_found

        mov rsi, [rsi]                  ; If not then next pair
        jmp .loop

    .exit_found:
        mov rax, rsi
        ret

    .exit_not_found:
        mov rax, 0
        ret