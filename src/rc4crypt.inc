.data
sbox	db 256 dup(0)

.code

rc4init PROC key : PCHAR, keylength : BYTE
	pushad
	xor 	eax, eax
	xor 	ebx, ebx
	xor 	ecx, ecx
	xor 	edx, edx
	mov 	edi, offset sbox
	mov		esi, key
;------------------------------------------------------------------;
; Init sbox, ESI = key, EDI = sbox, eax=0, ebx=j=0, ecx=i=0, edx=0 ;
;------------------------------------------------------------------;
init_sbox:
	stosb							; sbox[i] = i
	inc		al						; i++
	jnz 	init_sbox
;------------;	
; Scrambling ;
;------------;
init_key:
	mov 	al, cl					; key_idx
	mov 	dl, [edi + ecx]			; sbox[i]
	add		bl, dl					; j += sbox[i]
	add		bl, [esi + eax]			; j += key[key_idx % ???]
	xchg	dl, [edi + ebx]			; sbox[j] = sbox[i]
	mov		[edi + ecx], dl			; sbox[i] = sbox[j]
	inc		cl
	jnz		init_key
	popad
	ret 8
rc4init ENDP