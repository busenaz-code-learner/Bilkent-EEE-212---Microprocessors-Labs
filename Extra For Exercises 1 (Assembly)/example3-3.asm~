;Write a program to 
;(a) load the accumulator with the value 55H, and 
;(b) complement the ACC 700 times.

ORG 0000H
MOV A, #55H

MOV R2,#10H
BACK2:MOV R3, #70H
BACK:CPL A
DJNZ R3, BACK
DJNZ R2, BACK2
  
