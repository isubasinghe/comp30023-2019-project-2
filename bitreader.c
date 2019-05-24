#include "bitreader.h"


char *BytesToHexStr(unsigned char *bytes, int num) {
  
    char *hexstr = malloc( (num*2*sizeof(num) )+ 1);
    memset(hexstr, 0, (num*2*sizeof(num) )+ 1);

    if(hexstr == NULL) {
        return NULL;
    }

    for(size_t i =0; i < num; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", bytes[i]);
        strcat(hexstr, buffer);
    }

    
    return hexstr;
}

DT_HashTable *ReadBinaryFile(char *fname) {
    FILE *fp = fopen(fname, "rb");
    if(fp == NULL) {
        return NULL;
    }

    DT_HashTable *hashtable = DT_CreateHashTable(128);
    if(hashtable == NULL) {
        fclose(fp);
        return NULL;
    }


    unsigned char buffer[32];
    memset(buffer, 0, 32*sizeof(char));

    int hashes = 1;

    while(1) {
        int read = fread(buffer, 1, 32*sizeof(char), fp);
        if(read == 0) {
            break;
        }
        if(read != 32) {
            perror("Was expecting 32 bytes to read\n");
            exit(1);
        }
        char *hexstr = BytesToHexStr(buffer, 32*sizeof(char));

        if(hexstr == NULL) {
            perror("Out of memory, exiting program bye :(\n");
            exit(1);
        }

        char countstr[1024];
        memset(countstr, 0, 1024*sizeof(char));

        sprintf(countstr, "%d", hashes);

        DT_HashTable_Put(hashtable, hexstr, strdup(countstr));
        memset(buffer, 0, 32);

        hashes++;
    }

    fclose(fp);

    return hashtable;
}