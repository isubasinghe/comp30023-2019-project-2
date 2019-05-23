#include <stdio.h>
#include <stdlib.h>


#include "bitreader.h"
#include "pwcrack.h"
#include "pwgen.h"
#include "sha256.h"

#include "names.h"

int main(int argc, char *argv[]) {

    if(argc == 1) {
        
    }
    else if(argc == 2) {
        
    }else if (argc == 3) {
        ReadLineCrack(argv[1], argv[2]);
    }else {
        printf("usage: %s <num_guesses>\n", argv[0]);
        printf("usage: %s <password_file> <hashes_file>\n", argv[0]);
        return 0;
    }
}