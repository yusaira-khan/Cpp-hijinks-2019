CC=/usr/local/opt/llvm/bin/clang
LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
CPPFLAGS="-I/usr/local/opt/llvm/include"

# DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

short: src/Graph.cpp
	$(CC) $(CPPFLAGS) $? $(LDFLAGS) -o $@

