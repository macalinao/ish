all: clean build package

build:
	g++ -Wall -Wextra -Werror src/*.cpp -o target/ish

build-parse-only: build
	g++ -Wall -Wextra -Werror -D PARSE_ONLY src/*.cpp -o target/ish_parse_only

clean:
	rm -rf target/
	mkdir target/

install:
	cp target/ish /usr/local/bin

package: clean
	tar --exclude='./target/' --exclude='.git' -czf target/ish.tar.gz .

.PHONY: build clean install
