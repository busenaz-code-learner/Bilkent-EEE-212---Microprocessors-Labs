ORG 0H
MOV R4,#10H
MOV R5,#10
ACALL DELAY
MOV R2,#56H
SETB 10
SETB 42h
SETB PSW.4
MOV R0,#90H
MOV R1,#78H
MOV R4,#56H
MOV A,16
PUSH 4
PUSH 40
LCALL DELAY
PUSH 1
POP 20H
POP 29
POP 12H
MOV R0,#21h
MOV @R0,#0FFh
CPL 120
MOV C,120
MOV 0,C
CPL 10
NOP
HERE: SJMP HERE
ORG 0555h
DELAY: PUSH ACC 
MOV 5,#1
BACK5: MOV 4,#1
BACK4: NOP
NOP
NOP
CPL 10
DJNZ 4,BACK4
DJNZ 5,BACK5
POP ACC
RET 
END