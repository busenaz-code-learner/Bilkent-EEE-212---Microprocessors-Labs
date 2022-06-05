ORG 0000H
;-----------INITALIZE---------------;
MOV R0, #20D
;MOV 30H,#'U' ; The pivot word
MOV 31H,#04H ; Index of the pivot word
MOV 32H,#05H; Length 

MOV A, #'A'
ADD A,R0
MOV 30H,A 
;-----------FIND INDEX OF 'U'---------------;
MOV DPTR, #ENCRYPT
MOV A,31H
MOVC A, @A+DPTR ; A = 'U'

SUBB A, #41H ; U(ASCII) - A(ASCII) = 55 - 41 = INDEX OF 'U'

MOV R2,A            ;index of 'U' at first alphabet

;-----------FIND INDEX OF 'K'---------------;
MOV A,30H
SUBB A,#27H 
MOV R3, A ; index of 'K' at second alphabet


;-----------MOV 'LAMLU' TO 40H----------------;
MOV DPTR, #ENCRYPT
MOV R1,#40H
BACK:CLR A
MOVC A, @A+DPTR
CJNE A,#'0',GO
SJMP EXIT
GO:MOV @R1, A
INC DPTR
INC R1
SJMP BACK
EXIT:

;-----------FIND THE INDEX OF THE "LAMLU" AT ALPHABET----------------;
MOV A, R2
MOV R0, #40H
MOV R1, #60H
MOV DPTR, #ALPHABET
BACK1:
MOV R5, #26D
BACK0:
PUSH ACC 
MOVC A, @A+DPTR
CLR C 
SUBB A, @R0
JNZ NOTSAME
POP ACC
SUBB A,R2
MOV @R1, A
INC R1
INC R0
SJMP NEXT
NOTSAME:
POP ACC
INC A 
DJNZ R5, BACK0; THE ALPHABET
NEXT:MOV A, R2
DJNZ 32h, BACK1;THE NUMBER

;-----------FIND THE DECYRPT WORD----------------;
MOV R1,#60H
MOV R0,#80H
MOV 32H,#05H 
MOV DPTR, #ALPHABET
BACK3:
MOV A, R3
SUBB A, @R1
MOVC A, @A+DPTR
MOV @R0,A
INC R1
INC R0
DJNZ 32H, BACK3


acall	CONFIGURE_LCD

MOV 32H,#05H  
MOV R0, #80H
KEYBOARD_LOOP:MOV A,@R0
acall SEND_DATA
INC R0
DJNZ 32H, KEYBOARD_LOOP
WAIT:sjmp WAIT


CONFIGURE_LCD:	;THIS SUBROUTINE SENDS THE INITIALIZATION COMMANDS TO THE LCD
	mov a,#38H	;TWO LINES, 5X7 MATRIX
	acall SEND_COMMAND
	mov a,#0FH	;DISPLAY ON, CURSOR BLINKING
	acall SEND_COMMAND
	mov a,#06H	;INCREMENT CURSOR (SHIFT CURSOR TO RIGHT)
	acall SEND_COMMAND
	mov a,#01H	;CLEAR DISPLAY SCREEN
	acall SEND_COMMAND
	mov a,#80H	;FORCE CURSOR TO BEGINNING OF THE FIRST LINE
	acall SEND_COMMAND
	ret



SEND_COMMAND:
	mov p1,a		;THE COMMAND IS STORED IN A, SEND IT TO LCD
	clr p3.5		;RS=0 BEFORE SENDING COMMAND
	clr p3.6		;R/W=0 TO WRITE
	setb p3.7	;SEND A HIGH TO LOW SIGNAL TO ENABLE PIN
	acall DELAY
	clr p3.7
	ret


SEND_DATA:
	mov p1,a		;SEND THE DATA STORED IN A TO LCD
	setb p3.5	;RS=1 BEFORE SENDING DATA
	clr p3.6		;R/W=0 TO WRITE
	setb p3.7	;SEND A HIGH TO LOW SIGNAL TO ENABLE PIN
	acall DELAY
	clr p3.7
	ret


DELAY:
	push 0
	push 1
	mov r0,#50
DELAY_OUTER_LOOP:
	mov r1,#255
	djnz r1,$
	djnz r0,DELAY_OUTER_LOOP
	pop 1
	pop 0
	ret




ORG 1000h
ALPHABET: DB 'ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ'
ENCRYPT: DB 'TESTK0'
END 
