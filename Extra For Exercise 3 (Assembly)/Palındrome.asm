ORG 0000H
MOV R1,#40H
MOV DPTR , #WORD

LOOP:
CLR A
MOVC A,@A+DPTR
JZ PALINDROME
MOV @R1, A
INC R1
INC DPTR
SJMP LOOP


PALINDROME:
MOV R0, #40H
LENGHT: 
MOV A, R1
SUBB A, R0
PUSH A
DEC R1
MOV A,@R0
MOV 02,@R1
CJNE A, 02, JUMP
POP A
MOV B, #02H
DIV AB
INC R0
JZ JUMP2
SJMP LENGHT



JUMP:
CLR P1.1
GO: SJMP $

JUMP2:
SETB P1.1 
GO2: SJMP $



ORG 1000H
WORD: DB 'tenet',0
END
