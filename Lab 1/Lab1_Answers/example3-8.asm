;Write a program to toggle all the bits of port 1 by sending to it
;the values 55H and AAH continuously. Put a time delay in
;between each issuing of data to port 1.

ORG 0000H

BACK:
MOV A, #55H
MOV P1, A
LCALL DELAY
MOV A, #0AAH
MOV P1, A
LCALL DELAY
SJMP BACK



ORG 300H
DELAY:
MOV R5,#0FFH
AGAIN:DJNZ R5,AGAIN
RET 
END