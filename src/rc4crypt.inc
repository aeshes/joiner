.data
sbox		db 256 dup(0)
rc4key		db "XXX",0
rc4keylen	db 11

.code

rc4init PROC key : PCHAR, keylength : BYTE
	pushad
	xor 	eax, eax
	xor 	ebx, ebx
	xor 	ecx, ecx
	xor 	edx, edx
	mov 	edi, offset sbox
	mov	esi, key
;------------------------------------------------------------------;
; Init sbox, ESI = key, EDI = sbox, eax=0, ebx=j=0, ecx=i=0, edx=0 ;
;------------------------------------------------------------------;
init_sbox:
	stosb				; sbox[i] = i
	inc	al			; i++
	jnz 	init_sbox
;------------;	
; Scrambling ;
;------------;
init_key:
	mov 	al, cl			; key_idx
	mov 	dl, [edi + ecx]		; sbox[i]
	add	bl, dl			; j += sbox[i]
	add	bl, [esi + eax]		; j += key[key_idx % ???]
	xchg	dl, [edi + ebx]		; sbox[j] = sbox[i]
	mov	[edi + ecx], dl		; sbox[i] = sbox[j]
	inc	cl
	jnz	init_key
	popad
	ret 8
rc4init ENDP

crypt PROC data: PCHAR, datalength : DWORD
	invoke rc4init, offset rc4key, 11
	pushad
	xor	eax, eax		; i = 0
	xor	ebx, ebx
	xor	edx, edx
	mov	esi, offset sbox
	mov	edi, data
	mov	ecx, datalength
;--------------------------------------------------------------;
; ESI = sbox, EDI = data, ECX = size of data, EAX = i, EBX = j ;
;--------------------------------------------------------------;
crypt_data:
	inc	al			; i = (i + 1) % 256
	mov	dl, [esi + eax]		; dl = sbox[i]
	add	bl, dl			; bl = j = (j + sbox[i]) % 256
	xchg	dl, [esi + ebx]		; swap sbox[i], sbox[j], dl = sbox[j]
	mov	[esi + eax], dl		; sbox[i] = sbox[j], dl = sbox[j]
	add	dl, [esi + eax]		; dl = sbox[j] + sbox[i]
	mov	dl, [esi + edx]		; dl = sbox[sbox[i] + sbox[j]]
	xor	byte ptr[edi], dl	; *data ^= dl
	inc	edi			; ++data
	loop	crypt_data
	popad
	ret 8
crypt ENDP
