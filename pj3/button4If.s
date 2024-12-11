
.text
.global button4If	
	
button4If:
	.extern pause
	.extern button4
	
	BIC   #0x08  ,  &P2IFG       ; clear bit3 in P2IFG
	MOV   #1     ,  &pause       ; give the address of pause the value of 1
	MOV   #1     ,  &button4     ; give the address of button4 the value of 1

	MOV   #-1    ,  R12	   ; give r12 the value of -1
	CALL  #moveBird            ; moveBird is called with -1 as its parameter

	RET
