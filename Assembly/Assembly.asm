.386
.model flat, stdcall
include msvcrt.inc
include kernel32.inc
includelib msvcrt.lib
includelib kernel32.lib

$print_twice proto,
    twice_num$3:sdword
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
$print_plus_1 PROC,
    puls_num$0:sdword
    LOCAL temp$1:sdword
    LOCAL temp$2:sdword
label1:
    mov eax, 1
    cmp eax, 0
    jz label1
label2:
    mov eax, 1
    cmp eax, 0
    jz label2
label3:
    mov eax, 1
    mov temp$1, eax
label4:
    mov eax, puls_num$0
    add eax, temp$1
    mov temp$2, eax
label5:
label6:
    INVOKE $print, temp$2
label7:
print_plus_1_end:
    ret
$print_plus_1 ENDP
label8:
$print_twice PROC,
    twice_num$3:sdword
    LOCAL temp$4:sdword
    LOCAL temp$5:sdword
label9:
    mov eax, 1
    cmp eax, 0
    jz label9
label10:
    mov eax, 1
    cmp eax, 0
    jz label10
label11:
    mov eax, 2
    mov temp$4, eax
label12:
    mov eax, twice_num$3
    imul eax, temp$4
    mov temp$5, eax
label13:
label14:
    INVOKE $print, temp$5
label15:
print_twice_end:
    ret
$print_twice ENDP
label16:
$main PROC
    LOCAL temp$6:sdword
    LOCAL a$7:sdword
    LOCAL temp$8:sdword
    LOCAL temp$9:sdword
    LOCAL temp$10:sdword
    LOCAL temp$11:sdword
    LOCAL arr$12[3]:sdword
    LOCAL temp$13:sdword
    LOCAL b$14:sdword
    LOCAL i$15:sdword
    LOCAL temp$16:sdword
    LOCAL temp$18:sdword
    LOCAL temp$17:sdword
    LOCAL temp$19:sdword
    LOCAL temp$20:sdword
    LOCAL temp$21:sdword
    LOCAL temp$22:sdword
    LOCAL temp$23:sdword
    LOCAL temp$24:sdword
    LOCAL temp$25:sdword
label17:
    mov eax, 10
    mov temp$6, eax
label18:
    mov eax, temp$6
    mov a$7, eax
label19:
    mov eax, 3
    mov temp$8, eax
label20:
    mov eax, 1
    mov temp$9, eax
label21:
    mov eax, 2
    mov temp$10, eax
label22:
    mov eax, 3
    mov temp$11, eax
label23:
    mov eax, temp$9
    mov esi, 0
    mov arr$12[esi], eax
label24:
    mov eax, temp$10
    mov esi, 4
    mov arr$12[esi], eax
label25:
    mov eax, temp$11
    mov esi, 8
    mov arr$12[esi], eax
label26:
    mov eax, 1
    mov temp$13, eax
label27:
    mov eax, temp$13
    mov b$14, eax
label28:
    mov eax, 1
    cmp eax, 0
    jz label28
label29:
    mov eax, 2
    mov temp$16, eax
label30:
    mov eax, 4
    imul eax, temp$16
    mov temp$18, eax
label31:
    mov esi, temp$18
    mov eax, arr$12[esi]
    mov temp$17, eax
label32:
    mov eax, 3
    mov temp$19, eax
label33:
    mov eax, temp$17
    imul eax, temp$19
    mov temp$20, eax
label34:
label35:
    INVOKE $print, temp$20
label36:
    mov eax, 1
    cmp eax, 0
    jz label36
label37:
    mov eax, b$14
    mov temp$21, eax
label38:
    mov eax, b$14
    inc eax
    mov b$14, eax
label39:
    mov eax, 1
    cmp eax, 0
    jz label39
label40:
    mov eax, 1
    cmp eax, 0
    jz label40
label41:
label42:
    INVOKE $print, b$14
label43:
    mov eax, 1
    cmp eax, 0
    jz label43
label44:
    mov eax, 1
    cmp eax, 0
    jz label44
label45:
    INVOKE $input, ADDR temp$22
label46:
    mov eax, temp$22
    mov b$14, eax
label47:
    mov eax, temp$22
    mov temp$23, eax
label48:
    mov eax, 1
    cmp eax, 0
    jz label48
label49:
    mov eax, 1
    cmp eax, 0
    jz label49
label50:
label51:
    INVOKE $print, b$14
label52:
    mov eax, 1
    cmp eax, 0
    jz label52
label53:
    mov eax, 1
    cmp eax, 0
    jz label53
label54:
    mov eax, 1
    mov temp$24, eax
label55:
    mov eax, a$7
    add eax, temp$24
    mov temp$25, eax
label56:
label57:
    INVOKE $print_plus_1, temp$25
label58:
main_end:
    ret
$main ENDP
END $main
