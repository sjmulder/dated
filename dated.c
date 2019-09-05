#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <err.h>
#include <getopt.h>
#include <fcntl.h>

static const char usage[] =
"usage: ... | dated [-f format]\n";

int
main(int argc, char **argv)
{
	int c;
	char *format = "%x %X ";
	fd_set fds;
	int flags;
	time_t now;
	struct tm *now_tm;
	char now_str[512];
	char buf[4096];
	ssize_t nread, i;
	int newline = 1;

#if defined(__OpenBSD)
	pledge("stdio", NULL);
#endif

	while ((c = getopt(argc, argv, "f:")) != -1) {
		switch (c) {
		case 'f':
			format = optarg;
			break;
		default:
			fputs(usage, stderr);
			return 1;
		}
	}

	if (argc > optind) {
		fputs(usage, stderr);
		return 1;
	}

	FD_ZERO(&fds);

	/*
	 * We want to take the time the moment data is put on stdin, not when
	 * we happen to output it. To this, we use select() to wait for data,
	 * taking the time once, then processing all available data. To know
	 * what "all available", we make the stream nonblocking.
	 */
	
	if ((flags = fcntl(STDIN_FILENO, F_GETFL)) == -1)
		err(1, "F_GETFL");
	if (fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK) == -1)
		err(1, "F_SETFL");

	while (1) {
		FD_SET(STDIN_FILENO, &fds);
		if (select(STDIN_FILENO+1, &fds, NULL, NULL, NULL) == -1)
			err(1, "select");

		if ((now = time(NULL)) == (time_t)-1)
			err(1, "time");
		if (!(now_tm = localtime(&now)))
			err(1, "localtime");
		if (!strftime(now_str, sizeof(now_str), format, now_tm))
			err(1, "strftime");

		while ((nread = read(STDIN_FILENO, buf, sizeof(buf))) != -1) {
			if (!nread)
				return 0;

			for (i = 0; i < nread; i++) {
				if (newline)
					fputs(now_str, stdout);
				putchar(buf[i]);
				newline = buf[i] == '\n';
			}
		}

		if (errno != EAGAIN)
			err(1, NULL);
	}
}
