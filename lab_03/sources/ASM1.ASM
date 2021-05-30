StkSeg SEGMENT PARA STACK 'STACK'
	   DB      200h DUP (?)
StkSeg ENDS
;
DataS  SEGMENT WORD 'DATA'
HelloMessage   DB    13              ;поместить курсор в начало строки
               DB    10              ;перевести курсор на новую строку
	           DB    'Hello, world!' ;текст сообщения
			   DB    '$'             ;ограничитель для функции DOS
DataS  ENDS
;
Code   SEGMENT WORD 'CODE'
	   ASSUME  CS:Code, DS:DataS
DispMsg:
	   mov  AX,DataS                ;загрузка в АХ адреса сегмента данных
	   mov  DS,AX                   ;установка DS
	   mov  CX, 3
	   mov  DX,OFFSET HelloMessage   ;DS:DX - адрес строки
	   mov  AH,9                     ;AH=09h выдать на дисплей строку	   
	label1:
	   
	   int  21h 
	   loop label1
	   mov  AH,7                     ;AH=07h ввести символ без эха
	   INT  21h                       ;вызов функции DOS
	   mov  AH,4Ch                   ;AH=4Ch завершить процесс
	   int  21h                       ;вызов функции dos
Code   ENDS
       END   DispMsg
	