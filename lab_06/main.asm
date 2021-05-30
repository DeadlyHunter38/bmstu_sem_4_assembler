;вход знакового в 8 с/с
;беззнаковое в 2 с/с
;знаковое в 16 с/с

EXTRN print_sign: near
EXTRN print_bin: near
EXTRN print_hex: near
EXTRN read_number: near
EXTRN newline: near

STK SEGMENT PARA STACK 'STACK'
    db 200 dup (?)
STK ENDS

SEGDATA SEGMENT PARA PUBLIC 'DATA'
    menu_prnt db "1. Input number in 8 system"
			  db 10, 13
              db "2. Output signed number"
			  db 10, 13
              db "3. Convert to signed hexadecimal"
			  db 10, 13
              db "4. Convert to unsigned binary"
			  db 10, 13
              db "0. Exit"
			  db 10, 13
              db 10, 13
              db "Input menu item: $"
			  
	func_ptr dw exit, read_number, print_sign, print_hex, print_bin
SEGDATA ENDS

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE, DS:SEGDATA, SS:STK
main:
    mov ax, SEGDATA
    mov ds, ax

    menu:
        mov ah, 9
        mov dx, offset menu_prnt
        int 21h

        mov ah, 1
        int 21h

        mov ah, 0
        sub al, '0'
        shl ax, 1
        mov bx, ax
		;shl bx, 1

        call newline
        call func_ptr[bx]
        call newline
    jmp menu

exit proc near
    mov ax, 4c00h
    int 21h
exit endp

SEGCODE ENDS
END MAIN
