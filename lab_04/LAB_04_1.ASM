;Программа из двух модулей. В первом модуле ввести латинскую букву,
;затем передать управление во второй с помощью дальнего перехода,
;где вывести через пробел букву, расположенную на симметричной
;позиции с конца алфавита

EXTRN letter: far
PUBLIC end_program

STK SEGMENT para STACK 'STACK'
	db 100 dup (0)
STK ENDS

CSEG SEGMENT para public 'CODE'
	assume CS:CSEG, SS:STK
main:
	mov AH, 01h
	int 21h

	jmp letter
		
end_program:
	
	mov AX, 4c00h
	int 21h
	
CSEG ENDS

END main