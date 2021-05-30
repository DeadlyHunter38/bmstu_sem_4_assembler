PUBLIC print_sign
PUBLIC print_bin
PUBLIC newline

EXTRN real_numb: near
EXTRN number: near
EXTRN bin_len: byte
EXTRN bin_str: byte
EXTRN hex_str: byte
EXTRN hex_len: byte

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    sign_msg   db "Unsigned number:"
               db 10
               db 13
               db "$"

    bin_msg    db "Signed binary:"
               db 10
               db 13
               db "$"

    hex_msg    db "Signed hexadecimal:"
               db 10
               db 13
               db "$"
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA
print_sign proc near
    call newline

    mov ah, 9
    mov dx, offset sign_msg
    int 21h

    mov dx, offset number
    int 21h

    call newline
    ret

print_sign endp

print_bin proc near
    call newline

    mov ah, 9
    mov dx, offset bin_msg
    int 21h

    mov dx, offset bin_str
	inc dx
    int 21h

    call newline
    ret

print_bin endp


print_hex proc near
    call newline
	mov hex_str[6], '$'
    mov ah, 9
    mov dx, offset hex_msg
    int 21h

    mov dx, offset hex_str
    ; add dx, 5
    ; mov al, hex_len
    ; sub dl, al
    int 21h

    call newline
    ret

print_hex endp


newline proc near
    mov ah, 2
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    ret
newline endp

SEGCODE ENDS
END
