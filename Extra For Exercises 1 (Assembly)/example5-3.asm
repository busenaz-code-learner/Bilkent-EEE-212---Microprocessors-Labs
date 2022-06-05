;Assuming that ROM space starting at 250H contains “America”, write 
;a program to transfer the bytes into RAM locations starting at 40H.

;Solution (a) This method uses a counte

ORG 000H

MOV DPTR,#DATA
MOV R1, #40H
MOV R2, #7H


BACK: 
MOVC A, @A+DPTR
MOV @R1, A
CLR A
INC DPTR
INC R1
DJNZ R2,BACK



ORG 250H
DATA: DB 'AMERICA'