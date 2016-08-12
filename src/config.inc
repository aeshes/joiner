.data
	
hThisModule		dd 0
hNewFile		dd 0
hAllocMem		dd 0
nBytesRead		dd 0
	
LdrSize			dd 2560
nFilesJoined 	dd 1
nFileSizes		dd 1 dup(29696)

tmpdir			db ".", 0
tmpprefix		db "jn", 0
tmpext			db ".exe", 0