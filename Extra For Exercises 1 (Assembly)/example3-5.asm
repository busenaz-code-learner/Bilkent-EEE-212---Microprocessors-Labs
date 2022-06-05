;Find the sum of the values 79H, F5H, and E2H. 
;Put the sum in registers R0 (low byte) and R5 (high byte).

ORG 0000H
MOV A, #79H
MOV R5, #00H

ADD A, #0F5H
JNC NEXT
INC R5

NEXT:
ADD A, #0E2H
JNC NEXT1
INC R5

NEXT1: 
MOV R0,A

