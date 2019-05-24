#include "pwcrack.h"


void ReadLineCrack(char *passwords, char *hashfile) {
    DT_HashTable *hashes = ReadBinaryFile(hashfile);
    if(hashes == NULL) {
        return;
    }

    FILE *fp = fopen(passwords, "rb");
    if(fp == NULL) {
        DT_FreeHashTable(hashes);
        return;
    }

    // Passwords will be less than 2048 characters so this is more than enough
    // to store a single password in.
    char buffer[PASSWORD_LEN];  
    memset(buffer, 0, PASSWORD_LEN);

    SHA256_CTX ctx;
    sha256_init(&ctx);


    while(1) {
        memset(buffer, 0, PASSWORD_LEN);
        sha256_init(&ctx);
        char *read = fgets(buffer, PASSWORD_LEN, fp);
        if(read == NULL) {
            break;
        }
        
        for(int i=0; ; i++) {
            if(buffer[i] == 0) {
                break;
            }else if(buffer[i] == '\r') {
                buffer[i] = 0;
                break;
            }else if(buffer[i] == '\n') {
                buffer[i] = 0;
                break;
            }
        }

        sha256_update(&ctx, (unsigned char *)buffer, strlen(buffer));
        BYTE data[32];
        sha256_final(&ctx, data);

        char *hexstr = BytesToHexStr(data, 32);
        if(hexstr == NULL) {
            perror("Out of memory\n");
            exit(1);
        }

        char *value = DT_HashTable_Gets(hashes, hexstr, NULL);
        if(value != NULL) {
            printf("%s %s\n", buffer, value);
        }        
        free(hexstr);
    }

    DT_FreeHashTable(hashes);
    fclose(fp);
}