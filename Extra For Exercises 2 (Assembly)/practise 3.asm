ORG 0000H

MOV TMOD, #00010010B
MOV TL0,#0B9H
MOV TH0, #0B9H
SETB TR0
BACK: 
SETB P1.7
CLR TF0
JNB TF0,$

CLR P1.7
CLR TF0
JNB TF0,$
SJMP BACK

;------------------------------------------
STOP: CLR TR1
MOV TH1, #0FBH
MOV TL1, #50H
SETB TR1
SETB P1.6
CLR TF1
JNB TF1, $

CLR P1.6
CLR TR1
MOV TH1, #0FBH
MOV TL1, #50H
SETB TR1
CLR TF1
JNB TF1,$
SJMP STOP















