all: build/scsl.o build/scsl.so

build: 
	mkdir -p build

build/scsl.o: scsl.c build
	$(CC) -c $< -o $@

build/libscsl.so: scsl.c build
	$(CC) -shared $< -o $@

build/test.o: test.c build
	$(CC) -c $< -o $@

build/test: build/test.o build/scsl.o
	$(CC) $^ -o $@

test: build/test
	$<

install: build/libscsl.so scsl.h
	sudo cp build/libscsl.so /usr/lib/libscsl.so
	sudo cp scsl.h /usr/include/scsl.h

uninstall:
	sudo rm $< /usr/lib/libscsl.so 2>/dev/null

clean:
	rm -rf build 2>/dev/null

.PHONY: all clean test install uninstall
