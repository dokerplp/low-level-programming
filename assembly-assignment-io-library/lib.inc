section .text

; Принимает код возврата и завершает текущий процесс
exit:
    push rax
    push rdi
    mov rax, 60 
    xor rdi, rdi
    syscall
    pop rax
    pop rdi
    ret 

; Input data: rdi - string pointer
; Output data: rax - string length
; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    push rcx
    xor rcx, rcx ; 0 -> rcx (counter)

string_length_next:     
    cmp [rdi], byte 0
    je string_length_end 
    inc rcx 
    inc rdi
    jmp string_length_next

string_length_end:
    mov rax, rcx ; str_length -> rax
    pop rcx
    ret

; Input data: rdi - string pointer
; Output data: stdout - string
; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    push rsi
    push rax
    push rdx
    mov rsi, rdi ; pointer -> rsi
    call string_length ; str_length -> rax
    mov rdx, rax ; rax -> rdx
    mov rax, 1 
    mov rdi, 1
    syscall
    pop rsi
    pop rax
    pop rdx
    ret

; Input data: rdi - symbol
; Output data: stdout - symbol   
; Принимает код символа и выводит его в stdout
print_char:
    push rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp 
    mov rdx, 1 
    syscall
    pop rdi
    ret

; Output data: stdout - 0x0A
; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, 0xA
    call print_char
    ret


; Input data: rdi - number
; Output data: stdout - number
; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    xor rcx, rcx ; 0 -> rcx (counter)
    mov rax, rdi
    mov r10, 0x0A
    push 0x00
print_uint_divide:
    xor rdx, rdx ; 0 -> rdx (remainder of division)
    div r10
    add rdx, '0' ; null terminator for print_char
    push rdx
    cmp rax, r10
    jge print_uint_divide
    add rax, '0' ; null terminator for print_char
    cmp rax, '0'
    je print_uint_next
    push rax
print_uint_next:
    pop rdi
    cmp rdi, 0x00 
    je print_uint_ret
    call print_char
    jmp print_uint_next
print_uint_ret:
    ret

; Input data: rdi - number
; Output data: stdout - number
; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    push r10
    mov r10, rdi
    cmp rdi, 0
    jge print_int_positive
    mov rdi, '-'
    call print_char
    neg r10
print_int_positive:
    mov rdi, r10    
    call print_uint
    pop r10
    ret   

; Input data: rdi - string1, rsi - string2
; Output data: rax - 1 or 0
; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    push rdx
string_equals_symbol:
    mov al, byte[rdi]
    mov dl, byte[rsi]
    cmp al, dl
    jne string_equals_not_equals
    cmp al, 0
    je string_equals_equals
    inc rdi
    inc rsi
    jmp string_equals_symbol
string_equals_equals:
    mov rax, 1
    pop rdx
    ret
string_equals_not_equals:
    mov rax, 0
    pop rdx    
    ret

; Input data: stdin - symbol
; Output data: rax - symbol
; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    push 0
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 1
    syscall
    pop rax
    ret 

; Input data: rdi - start of buffer, rsi - buffer length
; Output data: buffer addr -> rax, str len -> rdx || 0 -> rax
; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор


read_word:
    xor rbx, rbx
    xor r10, r10
    xor r12, r12

    push rbx
    push r10
    push r12
    
    mov r10, rdi
    mov r12, rsi

read_word_space:
    call read_char
    cmp al, 0x20
    je read_word_space
    cmp al, 0x09
    je read_word_space
    cmp al, 0x0A
    je read_word_space
    cmp al, 0
    je read_word_success

read_word_reading:
    dec r12
    cmp r12, 0
    je read_word_error
    mov byte[r10 + rbx], al
    inc rbx

    call read_char
    cmp al, 0x20
    je read_word_success
    cmp al, 0x09
    je read_word_success
    cmp al, 0x0A
    je read_word_success
    cmp al, 0
    je read_word_success

    jmp read_word_reading

read_word_success:
    mov byte [r10+rbx], 0
    mov rax, r10
    mov rdx, rbx
    jmp read_word_ret

read_word_error:
    xor rax, rax
read_word_ret:
    pop r12
    pop r10
    pop rbx
    ret 


; Input data: rdi - string pointer
; Outout data: number -> rax, num len -> rdx
; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    push rcx
    push r10

    xor rcx, rcx ; 0 -> rcx (length)
    xor rax, rax ; 0 -> rax (result)
    xor rdx, rdx 
    mov r10, 10

parse_uint_next:
    cmp byte[rdi+rcx], '0'
    jl parse_uint_ret
    cmp byte[rdi+rcx], '9'
    jg parse_uint_ret
    mul r10
    mov dl,  byte[rdi+rcx]
    sub dl, '0'
    add rax, rdx
    inc rcx
    jmp parse_uint_next

parse_uint_ret:
    mov rdx, rcx
    pop rcx
    pop r10
    ret






; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    cmp byte[rdi], '-'
    je parse_int_neg
    call parse_uint
    ret

parse_int_neg:
    inc rdi
    call parse_uint
    neg rax
    inc rdx
    ret 

; Input data: rdi - string pointer, rsi - buffer pointer, rdx - buffer length
; Output data: string length -> rax || 0 -> rax
; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:

    cmp rdx, 0
    je string_copy_error
    xor r10, r10
    mov r10b, byte[rdi]
    mov byte[rsi], r10b
    inc rdi
    inc rsi
    dec rdx
    cmp r10, 0
    jne string_copy
    ret

string_copy_error:

    xor rax, rax
    ret
