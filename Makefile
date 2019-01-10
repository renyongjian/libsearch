OBJS= libsearch.c test.c

search:
	gcc $(OBJS) -o $@ -DDEBUG -g
clean:
	rm search;
