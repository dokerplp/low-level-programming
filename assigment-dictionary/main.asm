extern string_length
extern print_string
extern print_newline
extern string_equals
extern read_word
extern exit

extern find_word

global _start

section .data
wrong_key: db "Key read error", 0
not_found: db "This string wasn't found in list", 0

buffer: times 256 db 0

section .text
%include "colon.inc"
%include "words.inc"

print_err:
    push rsi
    push rax
    push rdx
    mov rsi, rdi
    call string_length
    mov rdx, rax
    mov rax, 1
    mov rdi, 2
    syscall
    pop rsi
    pop rax
    pop rdx
    ret

_start:
    mov rsi, 255
    mov rdi, buffer
    call read_word
    test rax, rax
    je wrong_key_error
    mov rdi, buffer
    mov rsi, list
    call find_word
    test rax, rax
    je not_found_error
    jmp success
wrong_key_error:
    mov rdi, wrong_key
    call print_err
    call print_newline
    mov rdi, 1
    call exit
not_found_error:
    mov rdi, not_found
    call print_err
    call print_newline
    mov rdi, 2
    call exit
success:
    add rax, 8
    mov rdi, rax
    call string_length
    add rdi, rax
    dec rdi
    dec rdi
    dec rdi
    call print_string
    call print_newline
    mov rdi, 0
    call exit
