CC = cl
LN = link
OBJ_LIST = main.obj list.obj hash_table.obj
CFLAGS = /nologo /W3 /D_CRT_SECURE_NO_DEPRECATE
LFLAGS = /nologo

build: tema1.exe

tema1.exe: $(OBJ_LIST)
	$(LN) $(LFAGS) /out:$@ $** hash.lib

main.obj: main.c hash_table.h utils.h list.h
	$(CC) $(CFLAGS) /c %s /Fo$@

hash_table.obj: hash_table.c hash_table.h utils.h list.h
	$(CC) $(CFLAGS) /c %s /Fo$@

list.obj: list.c utils.h list.h
	$(CC) $(CFLAGS) /c %s /Fo$@

clean :
	del *.obj tema1.exe