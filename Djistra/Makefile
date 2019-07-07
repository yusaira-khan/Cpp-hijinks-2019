CC=/usr/local/opt/llvm/bin/clang
CXX=/usr/local/opt/llvm/bin/clang++
LDFLAGS="-L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib"
CPPFLAGS="-I/usr/local/opt/llvm/include -std=c++11"
LD=/usr/local/opt/llvm/bin/ld64.lld
# DEPS = hellomake.h

%.o: %.cpp $(DEPS)
	$(CXX) -o $@ $< $(CPPFLAGS)

short: src/Graph.o
	$(LD) $? $(LDFLAGS) -o $@

