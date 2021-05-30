;повернуть числовую матрицу на 90 градусов по часовой стрелке
EXTRN newline: near
EXTRN print_matrix: near
EXTRN add_space: near
EXTRN rotate_matrix_clockwise: near

PUBLIC n
PUBLIC m
PUBLIC input_matrix
PUBLIC result_matrix

STK SEGMENT para STACK 'STACK'
	db 200 dup (?)
STK ENDS

SEGMATRIX SEGMENT para PUBLIC 'DATA'
	n db 1; количество строк
	m db 1; количество столбцов
	input_matrix db 81 dup (0)
	result_matrix db 81 dup (0)
SEGMATRIX ENDS

CSEG SEGMENT para public 'CODE'
	assume CS:CSEG, DS:SEGMATRIX, SS:STK

main:
	mov AX, SEGMATRIX
	mov DS, AX
	
	;вводим с клавиатуры количество строк
	mov AH, 01h
	int 21h
	mov n, AL
	sub n, "0"
	
	;вводим пробел
	call add_space
	
	;вводим с клавиатуры количество столбцов
	mov AH, 01h
	int 21h
	mov m, AL
	sub m, "0"
	
	;вводим новую строку
	call newline
	mov AH, 0
	mov AL, n
	mul m
	mov CX, AX
	read_matrix:
		;считываем элемент матрицы
		mov AH, 1
		int 21h
		sub al, '0'
		mov input_matrix[SI], AL
		inc SI
		
		;вызываем вывод пробела
		call add_space
		
		;вывод символа перевода строки
		mov AX, SI
		mov DH, m
		div DH
		
		cmp AH, 0
		je call_new_line
		
		;возвращаемся, чтобы ввести новую строку
		go_back:
			loop read_matrix
		
	call newline
	call rotate_matrix_clockwise
	call print_matrix
	
	mov AX, 4c00h
	int 21h
	
call_new_line:
	call newline
	jmp go_back
CSEG ENDS
END main