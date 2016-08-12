.386
.model flat, stdcall
option casemap:none

include windows.inc
include kernel32.inc
include shell32.inc
include shlwapi.inc
include config.inc
include file.inc
includelib kernel32.lib
includelib shell32.lib
includelib shlwapi.lib


.data?
	selfname		db MAX_PATH dup (?)
	currname		db MAX_PATH dup (?)
	szModulePath	dw MAX_PATH dup (?)

.code

Main PROC
	invoke GetModuleFileName, NULL, offset szModulePath, 100h
	invoke CreateFile, offset szModulePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0
	cmp eax, INVALID_HANDLE_VALUE
	jz EXIT
	mov hThisModule, eax		; Save handle for opened file
	
	invoke SetFilePointer, hThisModule, LdrSize, 0, FILE_BEGIN
	
	mov ecx, nFilesJoined
	mov esi, offset nFileSizes
	EXTRACT_LOOP:
		push ecx
		invoke GetTempFileName, offset tmpdir, offset tmpprefix, FALSE, offset currname
		invoke ChangeFileExtension, offset currname, offset tmpext
		
		invoke WriteFunc, addr currname, dword ptr [esi]
		invoke ShellExecute, NULL, 0, addr currname, NULL, NULL, SW_SHOW
		add esi, 4
		
		pop ecx
	loop EXTRACT_LOOP
		
		; Close loader handle
		invoke  CloseHandle, hThisModule

EXIT:					   
	push 0
	call ExitProcess
Main ENDP

end Main