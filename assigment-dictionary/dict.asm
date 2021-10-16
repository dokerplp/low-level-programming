global find_word
extern string_equals

section .text

; rsi - list start
; rdi - key start
find_word:
.loop:
  test rsi, rsi
  jz find_word_error
  push rsi
  add rsi, 8
  call string_equals
  pop rsi
  test rax, rax
  jnz find_word_success
  mov rsi, [rsi]
  jmp .loop
find_word_success:
  mov rax, rsi
  ret
find_word_error:
  mov rax, 0
  ret
