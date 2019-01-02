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

.code
label0:
$main PROC
    LOCAL temp$0:sdword
label1:
    mov eax, 1
    sub eax, -
    mov 1, eax
label2:
    mov eax, 20
    mov temp$0, eax
label3:
label4:
    INVOKE $print, temp$0
label5:
main_end:
    ret
$main ENDP
END $main
