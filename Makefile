all: benchmark open_shim.so

benchmark: benchmark.cpp
	g++ benchmark.cpp -o benchmark

open_shim.so: open_shim.cpp
	g++ -shared -fPIC open_shim.cpp -o open_shim.so

clean:
	rm *.so benchmark *.txt
