
ORG 0000H
MAIN:
LCALL COUNTDOWN

COUNTDOWN:
MOV R1,#50D
MOV R2,#10D
MOV R3,#00D


MOV R7,01H

COUNTING:
MOV A, R3
CJNE A,02H,NEXT
MOV R7, 01H
MOV R3,#00H


NEXT: ACALL DELAY 
INC R3
DJNZ R1,COUNTING
RET



DELAY: MOV R6,#5D 
       MOV R5,#10D 
LABEL1: DJNZ R6,LABEL1 
LABEL2: DJNZ R5,LABEL2 
        RET 