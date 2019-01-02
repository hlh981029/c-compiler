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
    temp$0 sdword ?

.code
label0:
    mov eax, 1
    mov temp$0, eax
label1:
$return_array_item PROC,
    a$1:sdword,
    b$2:sdword,
    temp: ptr sdword

    LOCAL temp$4:sdword
    LOCAL temp$3:sdword
label2:
    mov eax, 1
    cmp eax, 0
    jz label2
label3:
    mov eax, 4
    imul eax, b$2
    mov temp$4, eax
label4:
    mov esi, temp$4
    mov eax, a$1[esi]
    mov temp$3, eax
label5:
    mov eax, temp$3
    mov esi, temp
    mov [esi], eax
    jmp return_array_item_end
label6:
return_array_item_end:
    ret
$return_array_item ENDP
label7:
$main PROC
    LOCAL temp$5:sdword
    LOCAL temp$6:sdword
    LOCAL temp$7:sdword
    LOCAL temp$8:sdword
    LOCAL arr$9[3]:sdword
    LOCAL temp$10:sdword
    LOCAL temp$11:sdword
label8:
    mov eax, 3
    mov temp$5, eax
label9:
    mov eax, 1
    mov temp$6, eax
label10:
    mov eax, 2
    mov temp$7, eax
label11:
    mov eax, 3
    mov temp$8, eax
label12:
    mov eax, temp$6
    mov esi, 0
    mov arr$9[esi], eax
label13:
    mov eax, temp$7
    mov esi, 4
    mov arr$9[esi], eax
label14:
    mov eax, temp$8
    mov esi, 8
    mov arr$9[esi], eax
label15:
    mov eax, 1
    cmp eax, 0
    jz label15
label16:
    mov eax, 1
    cmp eax, 0
    jz label16
label17:
    mov eax, 1
    cmp eax, 0
    jz label17
label18:
label19:
    mov eax, 1
    mov temp$10, eax
label20:
label21:
    INVOKE $return_array_item, arr$9, temp$10, ADDR temp$11
label22:
label23:
    INVOKE $print, temp$11
label24:
main_end:
    ret
$main ENDP
END $main
