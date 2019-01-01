.386
.model flat, stdcall
include msvcrt.inc
include kernel32.inc
includelib msvcrt.lib
includelib kernel32.lib

.const
$output_format_int byte "%d", 0DH, 0AH, 0
$input_format_int byte "%d", 0
.code
$print proc,
    val: dword
    invoke crt_printf, addr $output_format_int, val
    ret
$print endp
$input proc,
    val : ptr dword
    invoke crt_scanf, addr $input_format_int,  val
    ret
$input endp
$$getch proc
    invoke crt__getch
    ret
$$getch endp

.data
    a$0 sdword ?
    b$1 sdword ?
    temp$2 sdword ?
    temp$3 sdword ?
    temp$4 sdword ?
    temp$5 sdword ?
    temp$6 sdword ?
    temp$7 sdword ?

.code
label0:
    mov eax, 1
    cmp eax, 0
    jz label0
label1:
    mov eax, 1
    mov temp$2, eax
label2:
    mov eax, temp$2
    mov a$0, eax
label3:
    mov eax, temp$2
    mov temp$3, eax
label4:
    mov eax, 1
    cmp eax, 0
    jz label4
label5:
    mov eax, 0
    mov temp$4, eax
label6:
    mov eax, temp$4
    mov b$1, eax
label7:
    mov eax, temp$4
    mov temp$5, eax
label8:
    mov eax, 1
    cmp eax, 0
    jz label8
label9:
    mov eax, 1
    cmp eax, 0
    jz label9
label10:
    mov eax, a$0
    cmp eax, 0
    jnz label14
label11:
    mov eax, b$1
    cmp eax, 0
    jnz label14
label12:
    mov eax, 0
    mov temp$6, eax
label13:
    jmp label15
label14:
    mov eax, 1
    mov temp$6, eax
label15:
    mov eax, temp$6
    cmp eax, 0
    jnz label18
label16:
    jmp label22
label17:
    jmp label22
label18:
    mov eax, 1
    cmp eax, 0
    jz label18
label0:
    mov eax, a$0
    mov temp$7, eax
label0:
    mov eax, a$0
    dec eax
    mov a$0, eax
label21:
    jmp label8
END $main
