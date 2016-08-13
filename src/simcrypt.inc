.data?
xorbyte	db ?

.code

; cData - pointer to data, cSize - size of data
crypt PROC cData : PCHAR, cSize : DWORD
	mov eax, cData
	.WHILE cSize > 0
		inc xorbyte
		xor xorbyte, 0AAh
		rol xorbyte, 1
		
		mov cl, xorbyte
		xor byte ptr [eax], cl
		inc eax
		dec cSize
	.ENDW
	ret
crypt ENDP