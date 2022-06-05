;Write a program to get the x value from P1 and send x2 to P2,
;continuously.

ORG 0000H


MOV DPTR,#NUMBERX
MOV P1, #0FFH
CLR A

BACK:PUSH A
MOVC A , @A+DPTR
CJNE A, #02H,NEXT
SJMP EXIT
NEXT:MOV P2, A
POP A
MOV P1,A
INC A
SJMP BACK

EXIT: SJMP EXIT 















ORG 1000H
NUMBERX: DB 0,1,4,9,16,25,36,49,64,81,2
