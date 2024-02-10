# mingw32-make.exe {target}
CC = GCC
FLAGS = -lws2_32 -Wall -Wextra -Werror -ggdb

httpServer: httpServer.c
	$(CC) httpServer.c -o httpServer.exe $(FLAGS)

hello:
	@ECHO "Mingw32-make!"