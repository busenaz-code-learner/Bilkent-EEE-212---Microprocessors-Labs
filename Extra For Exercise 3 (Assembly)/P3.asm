MOV R6, #0A5H ;MSB1
MOV R7, #05AH ;LSB1

MOV R4, #0B6H ;MSB2
MOV R5, #06BH ;LSB2
;--------------------------------------------------

MOV A, R7
MOV B, R5
MUL AB
MOV R3,A
MOV R2, B
;--------------------------------------------------

MOV A, R5
MOV B, R6
MUL AB 
ADD A, R2
MOV R2, A
MOV A, B
ADDC A, #00H  ; IF ANY CARRY IS THERE ADD 
MOV R1,A

;----------------------------------------------------

MOV A, R4
MOV B, R7
MUL AB
ADD A, R2
MOV R2, A
MOV A, B
ADDC A, R1
MOV R1, A
ADD A,#00H
ADDC A, #00H  ; IF ANY CARRY IS THERE ADD 
MOV R0,A

;------------------------------------------------

MOV A, R4
MOV B, R6
MUL AB
ADD A, R1
MOV R1, A
MOV A, B
ADDC A, #00H
MOV R0, A





