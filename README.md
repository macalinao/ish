# ish

ian shell. A really crappy shell written in C++.

## Features

* Running a command with arguments and options, e.g. `ls -hail /`
* Piping, e.g. `ls -l | wc -l`.
* Redirection operators `>`, `>>`, and `<`. Note that these only work at the end and the beginning of the pipeline.

## Installing

Run `make` then `make install` to put `isc` in `/usr/local/bin`.

## License

ISC
