EXTRN n: byte
EXTRN m: byte
EXTRN input_matrix: byte
EXTRN result_matrix: byte

PUBLIC newline
PUBLIC print_matrix
PUBLIC add_space

SEGMATRIX SEGMENT para PUBLIC 'DATA'
SEGMATRIX ENDS

CSEG SEGMENT para public 'CODE'
    assume CS: CSEG
add_space proc near
	mov AH, 02h
	mov DL, ' '
	int 21h
	ret
add_space endp

newline proc near
    mov ah, 2
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    ret
newline endp

print_matrix proc near
	;mov ah, 2
	;mov si, 0
	;обнуляем индексный регистр si
	xor si, si           
	
	mov al, m
	mul n
	mov cx, ax
	print_elem:
		mov dl, result_matrix[si]
		add dl, '0'
		mov ah, 2
		int 21h
		inc si
		
		call add_space
		
		mov AX, SI
		mov DH, n
		div DH
		
		cmp AH, 0
		je print_new_line
		
		continue_print_elem:
			loop print_elem	
	ret
	
print_new_line:
	call newline
	jmp continue_print_elem
print_matrix endp

CSEG ENDS
END
