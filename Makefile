all: clean build

build:
	g++ src/ish.cpp -o target/ish

clean:
	rm -rf target/
	mkdir target/

install:
	cp target/ish /usr/local/bin

.PHONY: build clean install
