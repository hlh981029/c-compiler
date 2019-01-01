.386
.model flat, stdcall
include msvcrt.inc
include kernel32.inc
includelib msvcrt.lib
includelib kernel32.lib

$hlh proto,
    aa$3:sdword
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

.code
label0:
$lyh PROC
    LOCAL a$0:sdword,
        temp$1:sdword,
        temp$2:sdword,
        $end_of_local:dword
label1:
    mov eax, 1
    cmp eax, 0
    jz label1
label2:
    mov eax, 1
    mov temp$1, eax
label3:
    mov eax, temp$1
    mov a$0, eax
label4:
    mov eax, temp$1
    mov temp$2, eax
label5:
lyh_end:
    ret
$lyh ENDP
label6:
$hlh PROC,
    aa$3:sdword
    LOCAL temp$4:sdword,
        temp$5:sdword,
        temp$6:sdword,
        temp$7:sdword,
        a$8[3]:sdword,
        temp$10:sdword,
        temp$9:sdword,
        $end_of_local:dword
label7:
    mov eax, 3
    mov temp$4, eax
label8:
    mov eax, 1
    mov temp$5, eax
label9:
    mov eax, 2
    mov temp$6, eax
label10:
    mov eax, 3
    mov temp$7, eax
label11:
    mov eax, temp$5
    mov esi, 0
    mov a$8[esi], eax
label12:
    mov eax, temp$6
    mov esi, 4
    mov a$8[esi], eax
label13:
    mov eax, temp$7
    mov esi, 8
    mov a$8[esi], eax
label14:
    mov eax, 1
    cmp eax, 0
    jz label14
label15:
    mov eax, 1
    cmp eax, 0
    jz label15
label16:
    mov eax, 4
    imul eax, aa$3
    mov temp$10, eax
label17:
    mov esi, temp$10
    mov eax, a$8[esi]
    mov temp$9, eax
label18:
label19:
    INVOKE $print, temp$9
label20:
hlh_end:
    ret
$hlh ENDP
label21:
$main PROC
    LOCAL temp$11:sdword,
        temp$12:sdword,
        temp$13:sdword,
        temp$14:sdword,
        a$15[3]:sdword,
        temp$16:sdword,
        temp$18:sdword,
        temp$17:sdword,
        $end_of_local:dword
label22:
    mov eax, 3
    mov temp$11, eax
label23:
    mov eax, 1
    mov temp$12, eax
label24:
    mov eax, 2
    mov temp$13, eax
label25:
    mov eax, 3
    mov temp$14, eax
label26:
    mov eax, temp$12
    mov esi, 0
    mov a$15[esi], eax
label27:
    mov eax, temp$13
    mov esi, 4
    mov a$15[esi], eax
label28:
    mov eax, temp$14
    mov esi, 8
    mov a$15[esi], eax
label29:
    mov eax, 1
    cmp eax, 0
    jz label29
label30:
    mov eax, 1
    mov temp$16, eax
label31:
    mov eax, 4
    imul eax, temp$16
    mov temp$18, eax
label32:
    mov esi, temp$18
    mov eax, a$15[esi]
    mov temp$17, eax
label33:
label34:
    INVOKE $print, temp$17
label35:
main_end:
    ret
$main ENDP
END $main
