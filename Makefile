all: clean build

build:
	g++ -Wall -Wextra -Werror src/*.cpp -o target/ish
	g++ -Wall -Wextra -Werror -D PARSE_ONLY src/*.cpp -o target/ish_parse_only

clean:
	rm -rf target/
	mkdir target/

install:
	cp target/ish /usr/local/bin

.PHONY: build clean install
