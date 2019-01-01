.386
.model flat, stdcall
include msvcrt.inc
include kernel32.inc
includelib msvcrt.lib
includelib kernel32.lib

$test_1 proto,
    test_1_int_1$0:sdword
$test_2 proto,
    test_2_int_1$3:sdword,
    temp: ptr sdword
$test_3 proto,
    test_3_int_array$6:ptr sdword,
    test_3_int_1$7:sdword
$main proto,
    temp: ptr sdword
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
    global_int_1$0 sdword ?
    global_int_2$0 sdword ?
    global_int_array_1$1 sdword 10 dup(?)

.code

label100:
$test_1 PROC,
    test_1_int_1$0:sdword
    LOCAL test_1_int_2$1:sdword,
        temp$2:sdword,
        $end_of_local:dword
label101:
label102:
    INVOKE $test_2, test_1_int_1$0, ADDR temp$2
label103:
    mov eax, temp$2
    mov test_1_int_2$1, eax
label104:
label105:
    INVOKE $print, test_1_int_2$1
label106:
test_1_end:
    ret
$test_1 ENDP
label200:
$test_2 PROC,
    test_2_int_1$3:sdword,
    temp: ptr sdword

    LOCAL test_2_int_2$4:sdword,
        temp$5:sdword,
        $end_of_local:dword
label201:
    mov eax, test_2_int_1$3
    add eax, 10
    mov temp$5, eax
label202:
    mov eax, temp$5
    mov test_2_int_2$4, eax
label203:
    mov eax, test_2_int_2$4
    mov esi, temp
    mov [esi], eax
    jmp test_2_end
label204:
test_2_end:
    ret
$test_2 ENDP
label300:
$test_3 PROC,
    test_3_int_array$6:ptr sdword,
    test_3_int_1$7:sdword
    LOCAL test_3_int_2$8:sdword,
        temp$9:sdword,
        temp$10:sdword,
        $end_of_local:dword
label301:
    mov eax, test_3_int_1$7
    sub eax, 1
    mov temp$9, eax
label302:
    mov eax, temp$9
    imul eax, 4
    mov temp$9, eax
label303:
    mov esi, temp$9
    mov eax, test_3_int_array$6[esi]
    mov temp$10, eax
label304:
    mov eax, temp$10
    mov test_3_int_2$8, eax
label305:
    mov eax, test_3_int_2$8
    mov esi, 0
    mov test_3_int_array$6[esi], eax
label306:
    jmp test_3_end
label307:
test_3_end:
    ret
$test_3 ENDP
label0:
$main PROC,
    temp: ptr sdword

    LOCAL main_int_1$11:sdword,
        main_int_array_1$12[1]:sdword,
        temp$13:sdword,
        $end_of_local:dword
label1:
    mov eax, 10
    mov esi, 0
    mov main_int_array_1$12[esi], eax
label2:
    mov eax, 20
    mov esi, 4
    mov main_int_array_1$12[esi], eax
label3:
label4:
label5:
    INVOKE $test_3, main_int_array_1$12, 2
label6:
    mov esi, 0
    mov eax, main_int_array_1$12[esi]
    mov temp$13, eax
label7:
label8:
    INVOKE $print, temp$13
label9:
    mov eax, 10
    mov main_int_1$11, eax
label10:
label11:
    INVOKE $test_1, main_int_1$11
label12:
    mov eax, 0
    mov esi, temp
    mov [esi], eax
    jmp main_end
label13:
main_end:
    ret
$main ENDP
END $main
