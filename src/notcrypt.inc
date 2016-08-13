.code

; cData - pointer to data, cSize - size of data
crypt PROC cData : PCHAR, cSize : DWORD
	mov eax, cData
	.WHILE cSize > 0
		not byte ptr [eax]
		inc eax
		dec cSize
	.ENDW
	ret
crypt ENDP