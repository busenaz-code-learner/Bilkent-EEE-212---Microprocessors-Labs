ORG 0000H


MOV R7,#56H
MOV R6, #0A8H
MOV R5, #4EH

;---------------------------------------------------------
MOV A, R7
MOV B, R5
MUL AB
MOV R2, A
MOV R3,B

;---------------------------------------------------------
MOV A, R7
MOV B, R6
MUL AB
ADDC A, R3
MOV R3, A
MOV A, B
ADDC A, R4
MOV R4,A