.MODEL TINY
.DOSSEG
.DATA
		MSG DB "Hello, world!", 0Dh, 0Ah, '$'
.CODE
.STARTUP
		MOV BX, 1
		ADD BX, 9
		MOV AH, 09h
		MOV DX, OFFSET MSG
		ADD BX, 10
		INT 21h
		MOV AH, 4Ch
		INT 21h
END
