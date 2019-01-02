.386
.model flat, stdcall
include msvcrt.inc
include kernel32.inc
includelib msvcrt.lib
includelib kernel32.lib

$main proto
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
    quanju$0 sdword ?

.code
label0:
$fun1 PROC
label1:
label2:
label3:
label4:
    INVOKE $print, quanju$0
label5:
fun1_end:
    ret
$fun1 ENDP
label6:
$main PROC
    LOCAL temp$1:sdword
    LOCAL temp$2:sdword
    LOCAL temp$3:sdword
    LOCAL temp$4:sdword
label7:
label8:
    mov eax, 5
    mov temp$1, eax
label9:
    mov eax, temp$1
    mov quanju$0, eax
label10:
label11:
label12:
    INVOKE $fun1
label13:
label14:
    mov eax, 6
    mov temp$3, eax
label15:
    mov eax, temp$3
    mov quanju$0, eax
label16:
label17:
label18:
    INVOKE $fun1
label19:
main_end:
    ret
$main ENDP
END $main
