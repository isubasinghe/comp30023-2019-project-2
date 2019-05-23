#include "pwgen.h"

void PW_GenCrack(int stop) {
        
}


int PW_NameCrack(int stop) {
    if(stop < 1) {
        return 0;
    }

    return 0;
}

int PW_GenCrackNumbers(int stop) {
    if(stop < 1) {
        return 0;
    }
    return 0;
}




void PW_GenLen4(char *buffer, int stop) {
    int i = 0;

    for(int i1=ASCII_START; i1 < ASCII_END && i < stop; i1++) {
        for(int i2=ASCII_START; i2 < ASCII_END && i < stop; i2++) {
            for(int i3 = ASCII_START; i3 < ASCII_END && i < stop; i3++) {
                for(int i4 = ASCII_START; i4 < ASCII_END && i < stop; i4++) {
                    buffer[0] = i1;
                    buffer[1] = i2;
                    buffer[2] = i3;
                    buffer[3] = i4;
                    i++;
                }
            }
        }
    }
}

void PW_GenLen6(char *buffer, unsigned long long stop) {
    unsigned long long i = 0;
    for(int i1=ASCII_START; i1 < ASCII_END && i < stop; i1++) {
        for(int i2=ASCII_START; i2 < ASCII_END && i < stop; i2++) {
            for(int i3 = ASCII_START; i3 < ASCII_END && i < stop; i3++) {
                for(int i4 = ASCII_START; i4 < ASCII_END && i < stop; i4++) {
                    for(int i5 = ASCII_START; i5 < ASCII_END 
                        && i < stop; i5++) {
                        for(int i6 = ASCII_START; i6 < ASCII_END 
                            && i < stop; i6++) {
                            buffer[0] = i1;
                            buffer[1] = i2;
                            buffer[2] = i3;
                            buffer[3] = i4;
                            buffer[4] = i5;
                            buffer[5] = i6;
                            i++;
                        }
                    }
                }
            }
        }
    }
}


// The loops are hard coded in sure, but this is because I dont wont 
// my RAM to be slaughtered, having chrome and vscode open is enough
// My dynamic solution for this would be this.

// While the password of desired length has not been reached
//      generate an array of passwords based on looping over all previous passwords
//      and appending a new character to each string (two for loops here, all password 
//      need to have all characters iterated on them)
//      if you are just starting, that is you have no new passwords generate characters 
//      from ASCII_START to ASCII_END and then go to the
//      step at the begning of the while loop
void PW_BruteForce(int num, unsigned long long stop) {
    if(num != 4 || num != 6) {
        perror("For efficiency (memory) reasons, loop is hardcoded in, this way \
        we can have O(1) memory usage\n");

        perror("In order to acheive brute force for all lengths, \
        use dynamic programming and memotize the previous generated passwords\n");

        exit(1);
    }

    char *buffer = malloc(num*sizeof(char));
    if(buffer == NULL) {
        return;
    }
    memset(buffer, ASCII_START, num*sizeof(char));


    if(num == 4) {
        PW_GenLen4(buffer, num);
    }else if(num == 6) {
        PW_GenLen6(buffer, num);
    }

    free(buffer);

}