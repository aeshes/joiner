.code

; Delete .tmp file. 
; Change extension in the full path.
; Create new file.
ChangeFileExtension PROC filename : DWORD, ext : DWORD
	invoke DeleteFile, filename
	invoke PathRenameExtension, filename, ext
	invoke CreateFile, filename, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, 0
	invoke CloseHandle, eax
	
	ret 8
ChangeFileExtension ENDP

WriteFunc PROC filename : DWORD, filesize : DWORD
	local hMem	   : DWORD
	local hFile    : DWORD
	local nBytes   : DWORD
	
	invoke CreateFile, filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0
	cmp eax, INVALID_HANDLE_VALUE
	jz WF_ERROR
	mov hFile, eax
	
	invoke GlobalAlloc, GMEM_FIXED, filesize
	cmp eax, INVALID_HANDLE_VALUE
	jz WF_ERROR
	mov hMem, eax
	
	invoke ReadFile, hThisModule, hMem, filesize, addr nBytes, 0
	cmp nBytes, 0
	jz WF_ERROR
	invoke WriteFile, hFile, hMem, filesize, addr nBytes, 0
	
	invoke GlobalFree, hMem
WF_ERROR:
	invoke CloseHandle, hFile
	ret 8
WriteFunc ENDP