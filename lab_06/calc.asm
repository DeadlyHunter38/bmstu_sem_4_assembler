;хранить реальное значение
PUBLIC convert_to_real_numb
PUBLIC convert_to_bin

EXTRN real_numb: word
EXTRN len: byte
EXTRN number: byte
EXTRN bin_len: byte
EXTRN bin_str: byte
EXTRN hex_len: byte
EXTRN hex_str: byte

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:SEGCODE
convert_to_real_numb proc near
    xor cx, cx

    mov cl, len
    dec cx
    mov si, 1
    xor ax, ax
    xor bx, bx
	mov dx, 3
    to_real_lbl:
		xchg cl, dl
		shl bx, cl
		xchg cl, dl
		
		;нужно интерпретировать размер как однобайтовый
		;считываем цифру из строки и вычитаем '0'
        mov al, byte ptr[number + si]
        sub ax, "0"
		;записываем в двубайтовое число
        add bx, ax

        inc si

        loop to_real_lbl
	cmp byte ptr[number], '-'
	jne endproc
	neg bx
	endproc:
	mov real_numb, bx
    ret

convert_to_real_numb endp


convert_to_bin proc near
	
	mov ax, real_numb
	
	mov si, 16

    lbl:
        shr ax, 1
		jc add_one
		mov bin_str[si], 0
		
		end_add_one:
        add bin_str[si], "0"
        inc bin_len

        dec si
        cmp ax, 0
        jne lbl

    ret
	
	add_one:
		mov bin_str[si], 1
		jmp end_add_one
convert_to_bin endp


convert_to_hex proc near
	mov si, 5
	inc hex_len
	
	
	mov ax, real_numb
	
    cmp real_numb, 0
    jge start
    mov hex_str[0] , "-"
	neg ax
	
	jmp notplus
    start:
	mov hex_str[0] , "+"
	
	notplus:
	
    xor cx, cx
    mov bx, 16
    
    xor dx, dx

    to_hex_lbl:
        div bx
        mov hex_str[si], dl

        cmp dl, 9
		;если остаток от деления больше 9
        jg hex_char
        add hex_str[si], "0"

        back:
			xor dx, dx
			inc hex_len

			dec si
			cmp si, 1
			jne to_hex_lbl

    ret

	;получить букву (A,B,C,D,E,F)
    hex_char:
        add hex_str[si], 55
        jmp back

convert_to_hex endp

SEGCODE ENDS
END
