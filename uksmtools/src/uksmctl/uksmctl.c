/*
    uksmctl — small tool to control UKSM
    Copyright © 2012–2013 Oleksandr Natalenko aka post-factum <oleksandr@natalenko.name>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sysexits.h>
#include <errno.h>

#define UKSMDIR		"/sys/kernel/mm/uksm"
#define UKSMRUN		UKSMDIR"/run"

void show_help()
{
	fprintf(stdout, "Usage: uksmctl <options>\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "  -a, --activate             activate UKSM\n");
	fprintf(stdout, "  -d, --deactivate           deactivate UKSM\n");
	fprintf(stdout, "  -t, --toggle               toggle UKSM\n");
	fprintf(stdout, "  -v, --verbose              be verbose (-vv to be more verbose)\n");
	fprintf(stdout, "  -h, --help                 show this help\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "Example:\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "sudo uksmctl -a\n");
	exit(EX_OK);
}

int main(int argc, char **argv)
{
	// define vars
	int opts = 0, activate = 0, deactivate = 0, toggle = 0, verbose = 0;
	struct stat sb;
	FILE *f;

	// check root privileges
	if (0 != getuid())
	{
		fprintf(stderr, "You have to be root in order to use uksmctl\n");
		exit(EX_NOPERM);
	}

	// check if there's uksm
	if (0 != stat(UKSMDIR, &sb) && S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "Unable to find uksm interface in %s\n", UKSMDIR);
		exit(EX_OSFILE);
	}

    struct option longopts[] = {
        {"activate",   0, NULL, 'a'},
        {"deactivate", 0, NULL, 'd'},
        {"toggle",     0, NULL, 't'},
        {"verbose",    0, NULL, 'v'},
        {"help",       0, NULL, 'h'},
        {0, 0, 0, 0}};

	// parse cmdline options
	while (-1 != (opts = getopt_long(argc, argv, "adtvh", longopts, NULL)))
	{
		switch (opts)
		{
			case 'a':
				activate = 1;
				break;
			case 'd':
				deactivate = 1;
				break;
			case 't':
				toggle = 1;
				break;
			case 'v':
				verbose++;
				if (verbose > 2)
				{
					fprintf(stderr, "Invalid -v switches count\n");
					exit(EX_USAGE);
				}
				break;
			case 'h':
				show_help();
				break;
			default:
				fprintf(stderr, "Unknown option: %c\n", opts);
				exit(EX_USAGE);
				break;
		}
	}

	// activate UKSM
	if (1 == activate)
	{
		f = fopen(UKSMRUN, "w");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open run file\n");
			exit(EX_OSFILE);
		}
		if (fprintf(f, "%d", 1) < 0)
		{
			fprintf(stderr, "Unable to write to run file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close run file\n");
			exit(EX_OSFILE);
		}

		switch (verbose)
		{
			case 1:
				fprintf(stdout, "1\n");
				break;
			case 2:
				fprintf(stdout, "UKSM activated\n");
		}

		exit(EX_OK);
	}

	// deactivate UKSM
	if (1 == deactivate)
	{
		f = fopen(UKSMRUN, "w");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open run file\n");
			exit(EX_OSFILE);
		}
		if (fprintf(f, "%d", 0) < 0)
		{
			fprintf(stderr, "Unable to write to run file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close run file\n");
			exit(EX_OSFILE);
		}

		switch (verbose)
		{
			case 1:
				fprintf(stdout, "0\n");
			case 2:
				fprintf(stdout, "UKSM deactivated\n");
		}

		exit(EX_OK);
	}

	// toggle UKSM state
	if (1 == toggle)
	{
		f = fopen(UKSMRUN, "r");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open run file\n");
			exit(EX_OSFILE);
		}
		unsigned int run = 0;
		errno = 0;
		fscanf(f, "%u", &run);
		if (0 != errno)
		{
			fprintf(stderr, "Unable to read run file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close run file\n");
			exit(EX_OSFILE);
		}
		
		switch (run)
		{
			case 0:
				run = 1;
				switch (verbose)
				{
					case 2:
						fprintf(stdout, "UKSM was inactive, activating\n");
						break;
				}
				break;
			case 1:
				run = 0;
				switch (verbose)
				{
					case 2:
						fprintf(stdout, "UKSM was active, deactivating\n");
						break;
				}
				break;
		}

		f = fopen(UKSMRUN, "w");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open run file\n");
			exit(EX_OSFILE);
		}
		if (fprintf(f, "%d", run) < 0)
		{
			fprintf(stderr, "Unable to write to run file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close run file\n");
			exit(EX_OSFILE);
		}

		switch (run)
		{
			case 0:
				switch (verbose)
				{
					case 1:
						fprintf(stdout, "0\n");
						break;
					case 2:
						fprintf(stdout, "UKSM deactivated\n");
						break;
				}
				break;
			case 1:
				switch (verbose)
				{
					case 1:
						fprintf(stdout, "1\n");
						break;
					case 2:
						fprintf(stdout, "UKSM activated\n");
						break;
				}
				break;
		}

		exit(EX_OK);
	}

	return EX_OK;
}

