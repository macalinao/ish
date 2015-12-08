# ish

ian shell. A really crappy shell written in C++.

## Features

* Running a command with arguments and options, e.g. `ls -hail /`
* Piping, e.g. `ls -l | grep . | wc -l`.
* Redirecting a file as input, e.g. `cat < README.md`
* Redirecting output to file, e.g. `ls > files.txt`
* Appending output to file, e.g. `ls >> files_appended.txt`

### Parse only

Run `make all build-parse-only` to build the parse only build. This does not run the command but instead displays what will be run.

```
$ ls -hail / | grep . | wc -l > summary
Command: ls
Options: -hail
Arguments: /
Pipe
Command: grep
Options:
Arguments: .
Pipe
Command: wc
Options: -l
Arguments:
File Redirection: >
File: summary
```

## Installing

Run `make` then `make install` to put `isc` in `/usr/local/bin`.

## License

ISC
