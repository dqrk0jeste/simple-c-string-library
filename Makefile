all: build/scsl.o

build: 
	mkdir -p build

build/scsl.o: scsl.c build
	$(CC) -c $< -o $@

build/test.o: test.c build
	$(CC) -c $< -o $@

build/test: build/test.o build/scsl.o
	$(CC) $^ -o $@

test: build/test
	$<

clean:
	rm -rf build 2>/dev/null

.PHONY: all clean test
