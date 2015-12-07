all: clean build

build:
	g++ -Wall -Wextra -Werror src/*.cpp -o target/ish

clean:
	rm -rf target/
	mkdir target/

install:
	cp target/ish /usr/local/bin

.PHONY: build clean install
