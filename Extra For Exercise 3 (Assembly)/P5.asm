ORG 0H



MOV A, #02H
MOV R1, #5AH

ACALL CALC
ORG 0100H

CALC:
CLR C
RRC A
PUSH A 
MOV A, R1
RRC A 
MOV R1, A
POP A
CLR C
RRC A
PUSH ACC
MOV A, R1
RRC A
MOV R1, A
POP A 
JC ROUND
RET 

ROUND:
INC R1
RET


