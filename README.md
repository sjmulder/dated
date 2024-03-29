dated
=====
[![Build status](
 https://builds.sr.ht/~sjmulder/dated.svg)](
 https://builds.sr.ht/~sjmulder/dated)

Add a timestamp to every line of a stream:

... | **dated** [**-f** *format*]

Description
-----------
**dated** copies standard input to standard output, prepending the date and
time to every line.

The **-f** option changes the prefix format string to format, which is passed
to [strftime(3)](http://man.openbsd.org/strftime.3). The default is "%x %X ":
the local date notation, a space, the local time notation, and another space.

Note: there is no way to get subsecond precision, a limitation of
[strftime(3)](http://man.openbsd.org/strftime.3).

Examples
--------
Watch a file with [tail(1)](http://man.openbsd.org/tail.1) and see when lines
were added:

    $ tail -f test.txt | dated
    11/07/18 21:28:31 Hello
    11/07/18 21:28:40 World!

Change the output format:

    $ tail -f test.txt | dated -f "[%H:%M] "
    [21:32] Hello
    [21:33] World!

Running
-------
Should work on any Unix, including Linux and macOS.

Mac users can install from
[my Homebrew tap](https://github.com/sjmulder/homebrew-tap)

    brew install sjmulder/tap/dated

To compile, install and uninstal from source:

    make
    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]

Authors
-------
Sijmen J. Mulder (<ik@sjmulder.nl>)
