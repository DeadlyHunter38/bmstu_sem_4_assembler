EXTRN end_program: far
PUBLIC letter

CSEGLETTER SEGMENT para public 'CODE'
	assume CS:CSEGLETTER
letter:
	mov CL, AL
	mov DL, ' '
	mov AH, 02h
	int 21h
	
	mov AL, CL
	cmp AL, 'Z'
	jle big_letter
	
	jmp low_letter
	
big_letter:
	mov CL, 'Z'
	mov DL, 'A'
	jmp end_letter
	
low_letter:
	mov CL, 'z'
	mov DL, 'a'
	jmp end_letter
	
end_letter:
	sub CL, AL
	add DL, CL
	mov AH, 02h
	int 21h
	
	jmp end_program
CSEGLETTER ENDS
END
	
	
