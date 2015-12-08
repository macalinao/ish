# ish

ian shell. A really crappy shell written in C++.

## Features

* Running a command with arguments and options, e.g. `ls -hail /`
* Piping, e.g. `ls -l | wc -l`.
* Redirecting a file as input, e.g. `cat < README.md`
* Redirecting output to file, e.g. `ls > files.txt`
* Appending output to file, e.g. `ls >> files_appended.txt`

## Installing

Run `make` then `make install` to put `isc` in `/usr/local/bin`.

## License

ISC
