;Write a subroutine to read a 4K block from 
;the internal ROM located at 1000h and write 
;it into a block beginning at 3800h in the 
;external RAM

ORG 0000H
MOV DPTR, #1000H
MOV R1,#3800H
LOOP:
CLR A
MOVC A,@A+DPTR
PUSH A
MOV A,R1
MOVX A,R1
INC R1
POP A 
INC DPTR
CJNE A,#0FFH,LOOP
RET 


