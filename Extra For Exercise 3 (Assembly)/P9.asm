ORG 0000H

MOV R1, #44H
MOV R0, #80H
MOV R5, #30D
LOOP:
MOV @R0, 01H
INC R1
INC R0
DJNZ R5, LOOP
MOV R5, #30D
MOV R0, #80H

COUNT:
MOV A, @R0
MOV B,#10H
DIV AB
CJNE A, B, NEXT
INC R6

NEXT:
ANL A, #00000001B
JNZ EXIT
ANL B, #00000001B
CJNE A, B, EXIT
INC R7


EXIT:INC R0
DJNZ R5, COUNT

