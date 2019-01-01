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
    hun$0 sdword ?
    ten$1 sdword ?
    ind$2 sdword ?
    n$3 sdword ?
    d$4 sdword ?
    aaa$5 sdword ?
    temp$6 sdword ?
    temp$7 sdword ?
    temp$8 sdword ?
    temp$9 sdword ?
    temp$10 sdword ?
    temp$11 sdword ?
    temp$12 sdword ?
    temp$13 sdword ?
    temp$14 sdword ?
    temp$15 sdword ?
    temp$16 sdword ?
    temp$17 sdword ?
    temp$18 sdword ?
    temp$19 sdword ?
    temp$20 sdword ?
    temp$21 sdword ?
    temp$22 sdword ?
    temp$23 sdword ?
    temp$24 sdword ?
    temp$25 sdword ?
    temp$26 sdword ?
    temp$27 sdword ?
    temp$28 sdword ?
    temp$29 sdword ?
    temp$30 sdword ?
    temp$31 sdword ?
    temp$32 sdword ?
    temp$33 sdword ?

.code
$main:
label0:
    mov eax, 1
    cmp eax, 0
    jz label0
label1:
    mov eax, 100
    mov temp$6, eax
label2:
    mov eax, temp$6
    mov n$3, eax
label3:
    mov eax, temp$6
    mov temp$7, eax
label4:
    mov eax, 1
    cmp eax, 0
    jz label4
label5:
    mov eax, 1000
    mov temp$8, eax
label6:
    mov eax, n$3
    cmp eax, temp$8
    jl label9
label7:
    mov eax, 0
    mov temp$9, eax
label8:
    jmp label10
label9:
    mov eax, 1
    mov temp$9, eax
label10:
    mov eax, temp$9
    cmp eax, 0
    jnz label17
label11:
    jmp label72
label12:
    mov eax, 1
    cmp eax, 0
    jz label12
label13:
    mov eax, n$3
    mov temp$10, eax
label14:
    mov eax, n$3
    inc eax
    mov n$3, eax
label15:
    jmp label4
label16:
    jmp label72
label17:
    mov eax, 1
    cmp eax, 0
    jz label17
label18:
    mov eax, 1
    cmp eax, 0
    jz label18
label19:
    mov eax, 100
    mov temp$11, eax
label20:
    mov eax, n$3
    cdq
    mov ebx, temp$11
    idiv ebx
    mov temp$12, eax
label21:
    mov eax, temp$12
    mov hun$0, eax
label22:
    mov eax, temp$12
    mov temp$13, eax
label23:
    mov eax, 1
    cmp eax, 0
    jz label23
label24:
    mov eax, 1
    cmp eax, 0
    jz label24
label25:
    mov eax, 1
    cmp eax, 0
    jz label25
label26:
    mov eax, 100
    mov temp$14, eax
label27:
    mov eax, hun$0
    imul eax, temp$14
    mov temp$15, eax
label28:
    mov eax, n$3
    sub eax, temp$15
    mov temp$16, eax
label29:
    mov eax, 10
    mov temp$17, eax
label30:
    mov eax, temp$16
    cdq
    mov ebx, temp$17
    idiv ebx
    mov temp$18, eax
label31:
    mov eax, temp$18
    mov ten$1, eax
label32:
    mov eax, temp$18
    mov temp$19, eax
label33:
    mov eax, 1
    cmp eax, 0
    jz label33
label34:
    mov eax, 1
    cmp eax, 0
    jz label34
label35:
    mov eax, 10
    mov temp$20, eax
label36:
    mov eax, n$3
    cdq
    mov ebx, temp$20
    idiv ebx
    mov temp$21, edx
label37:
    mov eax, temp$21
    mov ind$2, eax
label38:
    mov eax, temp$21
    mov temp$22, eax
label39:
    mov eax, 1
    cmp eax, 0
    jz label39
label40:
    mov eax, 1
    cmp eax, 0
    jz label40
label41:
    mov eax, 1
    cmp eax, 0
    jz label41
label42:
    mov eax, hun$0
    imul eax, hun$0
    mov temp$23, eax
label43:
    mov eax, 1
    cmp eax, 0
    jz label43
label44:
    mov eax, temp$23
    imul eax, hun$0
    mov temp$24, eax
label45:
    mov eax, 1
    cmp eax, 0
    jz label45
label46:
    mov eax, 1
    cmp eax, 0
    jz label46
label47:
    mov eax, ten$1
    imul eax, ten$1
    mov temp$25, eax
label48:
    mov eax, 1
    cmp eax, 0
    jz label48
label49:
    mov eax, temp$25
    imul eax, ten$1
    mov temp$26, eax
label50:
    mov eax, temp$24
    add eax, temp$26
    mov temp$27, eax
label51:
    mov eax, 1
    cmp eax, 0
    jz label51
label52:
    mov eax, 1
    cmp eax, 0
    jz label52
label53:
    mov eax, ind$2
    imul eax, ind$2
    mov temp$28, eax
label54:
    mov eax, 1
    cmp eax, 0
    jz label54
label55:
    mov eax, temp$28
    imul eax, ind$2
    mov temp$29, eax
label56:
    mov eax, temp$27
    add eax, temp$29
    mov temp$30, eax
label57:
    mov eax, temp$30
    mov aaa$5, eax
label58:
    mov eax, temp$30
    mov temp$31, eax
label59:
    mov eax, 1
    cmp eax, 0
    jz label59
label60:
    mov eax, 1
    cmp eax, 0
    jz label60
label61:
    mov eax, n$3
    cmp eax, aaa$5
    je label64
label62:
    mov eax, 0
    mov temp$32, eax
label63:
    jmp label65
label64:
    mov eax, 1
    mov temp$32, eax
label65:
    mov eax, temp$32
    cmp eax, 0
    jnz label67
label66:
    jmp label71
label67:
    mov eax, 1
    cmp eax, 0
    jz label67
label68:
    mov eax, 1
    cmp eax, 0
    jz label68
label69:
    mov eax, n$3
    mov d$4, eax
    invoke $print, d$4
label70:
    mov eax, n$3
    mov temp$33, eax
label71:
    jmp label12
label72:
    invoke $$getch
    invoke ExitProcess, 0
END $main
