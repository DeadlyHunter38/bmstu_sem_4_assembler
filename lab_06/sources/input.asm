PUBLIC number
PUBLIC len
PUBLIC real_numb
PUBLIC bin_len
PUBLIC bin_str
PUBLIC hex_len
PUBLIC hex_str

EXTRN newline: near
EXTRN convert_to_real_numb: near
EXTRN convert_to_bin: near
EXTRN convert_to_hex: near

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    max_size   db 9
    len        db 0
    number     db 9 DUP ("$")

    bin_len    db 0
    bin_str    db 17 DUP ("0")
               db "$"

    hex_len    db 0
    hex_str    db 5 DUP ("$")
               db "$"

    real_numb  dw 0

    ent_msg  db "Input number: $"
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA
read_number proc near
    call fill_nulls
    call newline

    mov ah, 9
    mov dx, offset ent_msg
    int 21h

    mov ah, 0ah
    mov dx, offset max_size
    int 21h

    call convert_to_real_numb
    call convert_to_bin
    call convert_to_hex
    call newline

    ret

read_number endp


fill_nulls proc near
    mov len, 0
    mov bin_len, 0
    mov hex_len, 0
    mov word ptr[real_numb], 0

    mov ax, seg number
    mov es, ax
    mov di, offset number
    mov al, "$"
    mov cx, 8
	;копирует байт из AL в место памяти, на которое указывает di
	;повторить несколько раз (сх)
	;(инициализация блока памяти)
    rep stosb

    mov ax, seg bin_str
    mov es, ax
    mov di, offset bin_str
    mov al, "0"
    mov cx, 16
    rep stosb

    mov ax, seg hex_str
    mov es, ax
    mov di, offset hex_str
    mov al, "$"
    mov cx, 6
    rep stosb

    ret

fill_nulls endp

SEGCODE ENDS
END
