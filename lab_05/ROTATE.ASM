EXTRN n: byte
EXTRN m: byte
EXTRN input_matrix: byte
EXTRN result_matrix: byte

PUBLIC rotate_matrix_clockwise

CSEG SEGMENT para public 'CODE'
	assume CS: CSEG
rotate_matrix_clockwise proc near
	xor si, si
	;зануляем ah, чтобы избавиться от мусора,
	;которое туда положило прерывание 21h
	xor ah, ah
	mov al, m
	mov dl, 1
	;внешний цикл - количество строк новой матрицы
	mov cx, ax 
	
	
	;смещение относительно ряда матрицы
	mov dh, 0
	;позиция элемента в матрице как массив: кол-во элементов в
	;столбце * размер элемента (в байтах) * номер ряда + смещение
	;в ряду
	run_column_input_mtr:
		;количество столбцов новой матрицы
		mov bl, n
		run_row_input_mtr:
			sub bl, dl		
			mov al, m		;число элементов в строке
			mul dl			;размер элемента
			mul bl			;нужный ряд
			add al, dh      ;нужное смещение в ряду
			
			xor ah, ah
			mov di, ax
			mov bh, input_matrix[di]
			mov result_matrix[si], bh
			inc si	
			
			cmp bl, 0
			jg run_row_input_mtr
			
		add dh, 1
		
		loop run_column_input_mtr
	ret
	
rotate_matrix_clockwise endp
CSEG ENDS
END
