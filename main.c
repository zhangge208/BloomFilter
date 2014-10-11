#include<stdio.h>
#include<string.h>
#include "hash.h"
#include "bloom.h"


int main(int argc, char *argv[])
{
	FILE *fp;
	char line[1024];
	char *p;
	BF *bloom;
	if(argc<2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}
	if (!(bloom = bloom_create(25000000, 11,RSHash,JSHash,PJWHash,ELFHash,BKDRHash,SDBMHash,DJBHash,DEKHash,BPHash,FNVHash,APHash)))
	{
		fprintf(stderr, "ERROR: Could not create bloom filter\n");
		return EXIT_FAILURE;
	}
	if (!(fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "ERROR: Could not open file %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	while (fgets(line, 1024, fp)) {
		if ((p = strchr(line, '\r'))) *p = '\0';
		if ((p = strchr(line, '\n'))) *p = '\0';

		bloom_add(bloom, line);
	}

	fclose(fp);

	while (fgets(line, 1024, stdin)) {
		if ((p = strchr(line, '\r'))) *p = '\0';
		if ((p = strchr(line, '\n'))) *p = '\0';

		p = strtok(line, " \t,.;:\r\n?!-/()");
		while (p) {
			if (!bloom_check(bloom, p)) {
				printf("No match for ford \"%s\"\n", p);
			}
			p = strtok(NULL, " \t,.;:\r\n?!-/()");
		}
	}

	bloom_d£ºestroy(bloom);

	return EXIT_SUCCESS;
	return 0;
}

