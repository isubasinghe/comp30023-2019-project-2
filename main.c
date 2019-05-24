#include <stdio.h>
#include <stdlib.h>


#include "bitreader.h"
#include "pwcrack.h"
#include "pwgen.h"
#include "sha256.h"

#include "names.h"


int main(int argc, char *argv[]) {
    if(argc == 1) {
        // I didnt crack passwords this way
        // generated+downloaded a huge dictionary beforehand (gigabytes)
        // and ran program with password file and hash file
        // This is fine because it is not assessed according to the spec.
        return 0;
    }
    else if(argc == 2) {
        PW_GenCrack(atoi(argv[1]));

    }else if (argc == 3) {
        ReadLineCrack(argv[1], argv[2]);
    }else {
        fprintf(stderr, "usage: %s <num_guesses>\n", argv[0]);
        fprintf(stderr, "usage: %s <password_file> <hashes_file>\n", argv[0]);
        return 0;
    }
}