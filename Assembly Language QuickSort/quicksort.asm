MYSS SEGMENT PARA STACK 'STACK'
	DW 32 DUP(?)
MYSS ENDS

MYDS SEGMENT PARA 'DATA'
DIZI DB 100 DUP(0)
ELEMAN DB ?
CR EQU 13
LF EQU 10
HATA DB CR,LF,'GECERLI SAYI VERMEDINIZ YENIDEN GIRIS YAPINIZ',0
HATA2 DB CR,LF,'[-128,127] ARALIGINDA SAYI GIRINIZ',0
MSG1 DB CR,LF,'ELEMAN SAYISINI GIRINIZ',0
MSG2 DB CR,LF,'Ogrenci No:16011080  , Toygar KAYAS',0

	
	
MYDS ENDS

MYCS SEGMENT PARA 'CODE'
	ASSUME CS:MYCS,DS:MYDS,SS:MYSS
	
ANA PROC FAR

	PUSH DS
	XOR AX,AX
	PUSH AX
	MOV AX,MYDS
	MOV DS,AX
	
	MOV AX,OFFSET MSG2
	CALL PUT_STR
	MOV AX,OFFSET MSG1
    CALL PUT_STR
	CALL GETN
	MOV ELEMAN,AL
	
	XOR CX,CX
	MOV CL,ELEMAN
	LEA SI,DIZI

L1: 
	JMP GO
AGAIN:
	MOV AX,OFFSET HATA2
	CALL PUT_STR
GO:
	CALL GETN
	CMP AX,-128
	JL AGAIN
	CMP AX,127
	JG AGAIN
	MOV BYTE PTR [SI],AL
	INC SI
	LOOP L1
	
	XOR SI,SI
	XOR AX,AX
	MOV AL,ELEMAN
	MOV DI,AX
	DEC DI
	CALL QSORT
	

	XOR CX,CX
	MOV CL,ELEMAN
	LEA SI,DIZI
YAZDIR:	
	XOR AX,AX
	MOV AL,BYTE PTR [SI]
	CALL PUTN
	MOV DL,' '
	MOV AH,2
	INT 21H
	INC SI
	LOOP YAZDIR	
	
	
	
	RETF
ANA ENDP

QSORT PROC NEAR 
	CMP SI,DI
	JGE  CIKIS
	CALL PART
	PUSH SI
	PUSH BX
	INC BX
	MOV SI,BX
	CALL QSORT
	POP BX
	POP SI
	DEC BX
	MOV DI,BX
	CALL QSORT
CIKIS: 
    RET
QSORT ENDP

PART PROC NEAR
	MOV CX,DI
	SUB CX,SI
	MOV BX,SI
	MOV DX,SI
	PUSH DX
	MOV DL ,DIZI[DI]
	DEC SI
L3: 
	CMP DIZI[BX],DL
	JG X
	INC SI
	MOV AL,DIZI[SI]
	XCHG DIZI[BX],AL
	MOV DIZI[SI],AL
X:  
	INC BX
	LOOP L3
	INC SI 
	MOV AL,DIZI[DI]
	XCHG DIZI[SI],AL
	MOV DIZI[DI],AL
	MOV BX, SI
	POP SI
	RET
PART ENDP




GETC PROC NEAR
	MOV AH,1h
	INT 21H
	RET
GETC ENDP

PUTC PROC NEAR
	PUSH AX
	PUSH DX
	MOV DL,AL
	MOV AH,2
	INT 21H
	POP DX
	POP AX
	RET
PUTC ENDP

PUT_STR PROC NEAR
	PUSH BX
	MOV BX,AX
	MOV AL,BYTE PTR [BX]
PUT_LOOP:
	CMP AL,0
	JE PUT_FIN
	CALL PUTC
	INC BX
	MOV AL,BYTE PTR [BX]
	JMP PUT_LOOP
PUT_FIN:
	POP BX
	RET
PUT_STR ENDP
	
GETN PROC NEAR 
	PUSH BX
	PUSH CX
	PUSH DX
GETN_START:
	MOV DX,1
	XOR BX,BX
	XOR CX,CX
NEW:
	CALL GETC
	CMP AL,CR
	JE FIN_READ
	CMP AL,'-'
	JNE CTRL_NUM
NEGATIVE:
	MOV DX,-1
	JMP NEW
CTRL_NUM:
	CMP AL,'0'
	JB ERROR
	CMP AL,'9'
	JA ERROR
	SUB AL,'0'
	MOV BL,AL
	MOV AX,10
	PUSH DX
	MUL CX
	POP DX
	MOV CX,AX
	ADD CX,BX
	JMP NEW
ERROR:
	MOV AX,OFFSET HATA
	CALL PUT_STR
	JMP GETN_START
FIN_READ:
	MOV AX,CX
	CMP DX,1
	JE FIN_GETN
	NEG AX
FIN_GETN:
	POP DX
	POP CX
	POP DX
	RET
GETN ENDP

PUTN PROC NEAR
	PUSH CX
	PUSH DX
	XOR DX,DX
	PUSH DX
	MOV CX,10
	CMP AL,0
	JGE CALC_DIGITS
	NEG AL
	PUSH AX
	MOV AL,'-'
	CALL PUTC
	POP AX
CALC_DIGITS:
	DIV CX
	ADD DX,'0'
	PUSH DX
	XOR DX,DX
	CMP AL,0
	JNE CALC_DIGITS
DISP_LOOP:
	POP AX
	CMP AL,0
	JE END_DISP_LOOP
	CALL PUTC
	JMP DISP_LOOP
END_DISP_LOOP:
	POP DX
	POP CX
	RET
PUTN ENDP


MYCS ENDS
	END ANA