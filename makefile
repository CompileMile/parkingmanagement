server: server.c
		gcc -o server server.c `mysql_config --cflags --libs`
