dated
=====

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

Should work on an Unix, including Linux and macOS. To compile:

    make

To install and uninstall:

    make install   [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]
    make uninstall [DESTDIR=] [PREFIX=/usr/local] [MANPREFIX=PREFIX/man]


Legal
-----

Copyright (c) 2018, Sijmen J. Mulder (<ik@sjmulder.nl>)

dated is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

dated is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
more details.

You should have received a copy of the GNU Affero General Public License
along with dated. If not, see <https://www.gnu.org/licenses/>.
