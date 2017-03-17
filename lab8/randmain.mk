randmain: randmain.c
	$(CC) $(CFLAGS) randmain.c randcpuid.c -ldl -Wl,-rpath,$(PWD) -o $@

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -shared -fPIC -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -shared -fPIC -o randlibsw.so