/*
    uksmstat — small tool to show UKSM statistics
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
#include <sysexits.h>
#include <errno.h>

#define UKSMDIR		"/sys/kernel/mm/uksm"
#define UKSMRUN		UKSMDIR"/run"
#define UKSMUNSHARED	UKSMDIR"/pages_unshared"
#define UKSMSHARED	UKSMDIR"/pages_sharing"
#define UKSMSCANNED	UKSMDIR"/pages_scanned"

void show_help()
{
	fprintf(stdout, "Usage: uksmstat <options>\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "  -a, --active             show whether UKSM is active or not\n");
	fprintf(stdout, "  -u, --unshared           show unshared memory\n");
	fprintf(stdout, "  -s, --shared             show shared memory\n");
	fprintf(stdout, "  -c, --scanned            show scanned memory\n");
	fprintf(stdout, "  -k, --kibibytes          use kibibytes\n");
	fprintf(stdout, "  -m, --mebibytes          use mebibytes\n");
	fprintf(stdout, "  -g, --gibibytes          use gibibytes\n");
	fprintf(stdout, "  -p, --precision          increase precision (-pppp… for more precision)\n");
	fprintf(stdout, "  -v, --verbose            be verbose (-vv to be more verbose)\n");
	fprintf(stdout, "  -h, --help               show this help\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "Example:\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "uksmstat -sppv\n");
	exit(EX_OK);
}

int main(int argc, char **argv)
{
	// define vars
	int opts = 0, active = 0, unshared = 0, shared = 0, scanned = 0, verbose = 0, precision = 0;
	char *units = "MiB";
	unsigned long divisor = 1024 * 1024;
	struct stat sb;
	FILE *f;

	// check if there's uksm
	if (0 != stat(UKSMDIR, &sb) && S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "Unable to find uksm interface in %s\n", UKSMDIR);
		exit(EX_OSFILE);
	}

    struct option longopts[] = {
        {"active",    0, NULL, 'a'},
        {"unshared",  0, NULL, 'u'},
        {"shared",    0, NULL, 's'},
        {"scanned",   0, NULL, 'c'},
        {"kibibytes", 0, NULL, 'k'},
        {"mebibytes", 0, NULL, 'm'},
        {"gibibytes", 0, NULL, 'g'},
        {"precision", 0, NULL, 'p'},
        {"verbose",   0, NULL, 'v'},
        {"help",      0, NULL, 'h'},
        {0, 0, 0, 0}};

	// parse cmdline options
	while (-1 != (opts = getopt_long(argc, argv, "ausckmgpvh", longopts, NULL)))
	{
		switch (opts)
		{
			case 'a':
				active = 1;
				break;
			case 'u':
				unshared = 1;
				break;
			case 's':
				shared = 1;
				break;
			case 'c':
				scanned = 1;
				break;
			case 'k':
				units = "KiB";
				divisor = 1024;
				break;
			case 'm':
				units = "MiB";
				divisor = 1024 * 1024;
				break;
			case 'g':
				units = "GiB";
				divisor = 1024 * 1024 * 1024;
				break;
			case 'p':
				precision++;
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

	// check if UKSM is active
	if (1 == active)
	{
		f = fopen(UKSMRUN, "r");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open run file\n");
			exit(EX_OSFILE);
		}
		unsigned int run;
		errno = 0;
		fscanf(f, "%u", &run);
		if (0 != errno)
		{
			fprintf(stderr, "Unable to read value from run file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close run file\n");
			exit(EX_OSFILE);
		}

		if (1 == run)
			fprintf(stdout, "UKSM is active\n");
		else if (0 == run)
			fprintf(stdout, "UKSM is inactive\n");
	}

	// find out page size
	long page_size = sysconf(_SC_PAGESIZE);
	if (-1 == page_size)
	{
		fprintf(stderr, "Unable to get page size\n");
		exit(EX_OSERR);
	}

	// show unshared mem
	if (1 == unshared)
	{
		f = fopen(UKSMUNSHARED, "r");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open pages_unshared file\n");
			exit(EX_OSFILE);
		}
		unsigned long long pages_unshared;
		errno = 0;
		fscanf(f, "%llu", &pages_unshared);
		if (0 != errno)
		{
			fprintf(stderr, "Unable to read value from pages_unshared file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close pages_unshared file\n");
			exit(EX_OSFILE);
		}

		switch (verbose)
		{
			case 0:
				fprintf(stdout, "%1.*lf\n", precision, (double)page_size * pages_unshared / divisor);
				break;
			case 1:
				fprintf(stdout, "%1.*lf %s\n", precision, (double)page_size * pages_unshared / divisor, units);
				break;
			case 2:
				fprintf(stdout, "Unshared pages: %1.*lf %s\n", precision, (double)page_size * pages_unshared / divisor, units);
				break;
		}
	}

	// show shared (saved) mem
	if (1 == shared)
	{
		f = fopen(UKSMSHARED, "r");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open pages_sharing file\n");
			exit(EX_OSFILE);
		}
		unsigned long long pages_shared;
		errno = 0;
		fscanf(f, "%llu", &pages_shared);
		if (0 != errno)
		{
			fprintf(stderr, "Unable to read value from pages_sharing file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close pages_sharing file\n");
			exit(EX_OSFILE);
		}

		switch (verbose)
		{
			case 0:
				fprintf(stdout, "%1.*lf\n", precision, (double)page_size * pages_shared / divisor);
				break;
			case 1:
				fprintf(stdout, "%1.*lf %s\n", precision, (double)page_size * pages_shared / divisor, units);
				break;
			case 2:
				fprintf(stdout, "Shared pages: %1.*lf %s\n", precision, (double)page_size * pages_shared / divisor, units);
				break;
		}
	}

	// show scanned (total during kernel uptime) mem
	if (1 == scanned)
	{
		f = fopen(UKSMSCANNED, "r");
		if (NULL == f)
		{
			fprintf(stderr, "Unable to open pages_scanned file\n");
			exit(EX_OSFILE);
		}
		unsigned long long pages_scanned;
		errno = 0;
		fscanf(f, "%llu", &pages_scanned);
		if (0 != errno)
		{
			fprintf(stderr, "Unable to read value from pages_scanned file\n");
			fclose(f);
			exit(EX_OSFILE);
		}
		if (0 != fclose(f))
		{
			fprintf(stderr, "Unable to close pages_scanned file\n");
			exit(EX_OSFILE);
		}

		switch (verbose)
		{
			case 0:
				fprintf(stdout, "%1.*lf\n", precision, (double)page_size * pages_scanned / divisor);
				break;
			case 1:
				fprintf(stdout, "%1.*lf %s\n", precision, (double)page_size * pages_scanned / divisor, units);
				break;
			case 2:
				fprintf(stdout, "Scanned pages: %1.*lf %s\n", precision, (double)page_size * pages_scanned / divisor, units);
				break;
		}
	}

	return EX_OK;
}

