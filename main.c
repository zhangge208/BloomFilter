#include<stdio.h>
#include<string.h>

#include"bloom.h"
#include"hash.h"

int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    
    int  i = 0;
    char line[1024];
    char *p;
    BF *bloom;
    
    if(argc<2) {
        fprintf(stderr, "ERROR: No word file specified\n");
        return EXIT_FAILURE;
    }
    if(!(bloom=bloom_create(200000000, 11, RSHash, JSHash, PJWHash, ELFHash, BKDRHash, SDBMHash, DJBHash, DEKHash, BPHash, FNVHash, APHash))) {
        fprintf(stderr, "ERROR: Could not create bloom filter\n");
        return EXIT_FAILURE;
    }

    if(!(fp1=fopen(argv[1], "r"))) {
        fprintf(stderr, "ERROR: Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    while(fgets(line, 1024, fp1)) {
        if((p=strchr(line, '\r'))) *p='\0';
        if((p=strchr(line, '\n'))) *p='\0';
        bloom_add(bloom, line);
    }

    fclose(fp1);

    if(!(fp2=fopen(argv[2], "r"))) {
        fprintf(stderr, "ERROR: Could not open file %s\n", argv[2]);
        return EXIT_FAILURE;
    }
    if(!(fp3=fopen("checkedemailresult.dat","w"))){
                fprintf(stderr, "ERROR:Could not open file");
                return EXIT_FAILURE;
    }
    
    while(fgets(line, 1024, fp2)) {
        i++;
        if((p=strchr(line, '\r'))) *p='\0';
        if((p=strchr(line, '\n'))) *p='\0';
        p=strtok(line, "\r\n");
        while(p) {
            if(bloom_check(bloom, line)==1) {
            fputs("yes\n",fp3);
            }
            else{fputs("no\n",fp3);}
          p=strtok(NULL, "\r\n");
        }
    }

    fclose(fp3);     
    fclose(fp2);

    bloom_destroy(bloom);

    return EXIT_SUCCESS;
}
