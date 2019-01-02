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
    b$4 label byte
    b$a1$5 sdword ?
    b$a2$6 sdword ?
    b$a3$7 sdword ?

.code
label0:
$main PROC
    LOCAL temp$8:sdword
    LOCAL temp$9:sdword
    LOCAL temp$10:sdword
    LOCAL temp$11:sdword
    LOCAL temp$12:sdword
label1:
    mov eax, 1
    mov temp$8, eax
label2:
