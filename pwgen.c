#include "pwgen.h"

void PW_GenCrack(int stop) {
    int done = 0;

    done = PW_WordCrack(stop);
    stop = stop - done;

    done = PW_NameCrack(stop);
    stop = stop-done;

    PW_BruteForce(4, stop);
    stop = stop - BRUTEFORCE_MAX4;

    PW_BruteForce(6, stop);

    return;

}


int PW_NameCrack(int stop) {
    if(stop < 1) {
        return 0;
    }

    int total_done = 0;

    int done = 0;

    for(int i=0; i < NUM_NAMES && done < stop; i++) {
        int name_len = strlen(names[i]);
        if(name_len == 4 || name_len ==6) {
            printf("%s\n", names[i]);
            done++;
        }
    }

    stop = stop - done;
    total_done = done;
    done = 0;

    for(int i=0; i < NUM_NAMES && done < stop; i++) {
        int name_len = strlen(names[i]);
        if(name_len == 4 || name_len ==5) {
            int done_here = PW_Transform((char *)names[i], stop);
            stop = stop - done_here;
            done += done_here;
        }
    }

    total_done += done;
    return total_done;
}


// Crack possible words
int PW_WordCrack(int stop) {
    if(stop < 1 ) {
        return 0;
    }

    int total_done = 0;
    int done = 0;
    
    // Crack normal words of length 4
    for(int i=0; i < WORDS4 && done < stop; i++) {
        printf("%s\n", words4[i]);
        done++;
    }

    stop = stop - done;
    total_done = done;
    done = 0;

    // Crack normal words of length 6
    for(int i=0; i < WORDS6 && done < stop; i++) {
        printf("%s\n", words6[i]);
        done++;
    }

    // Crack words with transformations such as leet speek and possible
    // birthyear applied to them.
    stop = stop - done;
    total_done += done;
    done = 0;
    for(int i=0; i < WORDS4 && done < stop; i++) {
        int done_here = PW_Transform((char *)words4[i], stop);
        stop = stop - done_here;
        done += done_here;
    }

    stop = stop - done;
    total_done += done;
    done = 0;
    for(int i=0; i < WORDS6 && done < stop; i++) {
        int done_here = PW_Transform((char *)words6[i], stop);
        stop = stop - done_here;
        done += done_here;
    }

    total_done += done;
    return total_done;

}


int PW_Transform(char *buffer, int stop) {
    if(stop < 1) {
        return 0;
    }
    int done = 0;

    done += PW_Leetify(buffer, stop);
    stop = stop - done;

    done += PW_AddChar(buffer, stop);
    stop = stop - done;

    return done;
}

int PW_Leetify(char *buffer, int stop) {
    if(stop < 1) {
        return 0;
    }

    char *newbuffer = malloc((strlen(buffer)+1)*sizeof(char));
    memset(newbuffer, 0, (strlen(buffer)+1)*sizeof(char));

    for(int i= 0; i < strlen(buffer); i++) {
        char c = buffer[i];
        char curr = tolower(buffer[i]);
        switch(curr) {
            case 'a':
                c = '4';
                break;
            case 'e':
                c = '3';
                break;
            case 'i':
                c = '1';
                break;
            case 'o':
                c = '0';
                break;
            case 's':
                c = '5';
                break;
            case 't':
                c = '7';
                break;
            default:
                c = buffer[i];
                break;
        }
        newbuffer[i] = c;
    }
    printf("%s\n", newbuffer);
    free(newbuffer);

    return 1;
}

int PW_AddChar(char *buffer, int stop) {
    int done = 0;
    int buflen = strlen(buffer);
  

    if(buflen == 4) {
        // Try the possible birthyears as ending the password
        for(int i=50; i < 99 && (i-50) < stop; i++) {
            printf("%s%d\n", buffer, i);
            done++;
        }
    }else if(buflen == 5){
        for(unsigned char i=ASCII_START; i < ASCII_END && (i-ASCII_START) < stop; i++) {
            printf("%s%c\n", buffer, i);
            done++;
        }
    }

    return done;
}

void PW_GenLen4(char *buffer, int stop) {
    if(stop < 1) {
        return;
    }
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
                    printf("%s\n", buffer);
                }
            }
        }
    }
}

void PW_GenLen6(char *buffer, long long stop) {
    if(stop < 1) {
        return;
    }
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
                            printf("%s\n", buffer);
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
void PW_BruteForce(int num, long long stop) {
    if(num != 4 && num != 6) {
        perror("For efficiency (memory) reasons, loop is hardcoded in, this way \
        we can have O(1) memory usage\n");

        perror("In order to acheive brute force for all lengths, \
        use dynamic programming and memotize the previous generated passwords\n");

        exit(1);
    }

    if(stop < 1) {
        return;
    }

    char *buffer = malloc((num+1)*sizeof(char));
    if(buffer == NULL) {
        return;
    }
    memset(buffer, ASCII_START, (num+1)*sizeof(char));


    if(num == 4) {
        PW_GenLen4(buffer, stop);
    }else if(num == 6) {
        PW_GenLen6(buffer, stop);
    }

    free(buffer);

}