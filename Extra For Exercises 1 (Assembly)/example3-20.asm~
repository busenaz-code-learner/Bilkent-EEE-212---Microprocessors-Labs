;Assume that bit P2.3 is an input and represents the condition of 
;an oven. If it goes high, it means that the oven is hot. Monitor 
;the bit continuously. Whenever it goes high, send a high-to-low
;pulse to port P1.5 to turn on a buzzer

ORG 0000H
OVEN_HOT BIT P2.3
BUZZER BIT P1.5

HERE: JNB OVEN_HOT, HERE
SETB BUZZER
ACALL DELAY
CPL BUZZER
ACALL DELAY
SJMP HERE
 