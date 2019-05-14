#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>


static const int g = 15;
static const int p = 97;

int mod_exp(int base, int expn, int mod) {
    int result = 1;
    base = base % mod;
    while (expn > 0) {
        if(expn%2 == 1) {
            result = (result*base)%mod;
        }
        expn = expn >> 1;
        base = (base*base)%mod;
    }
    return result;
}

/* Create and return a socket bound to the given port and server */
int setup_client_socket(const int port, const char* server_name,
						struct sockaddr_in* serv_addr) {
	int sockfd;
	struct hostent* server;

	server = gethostbyname(server_name);
	if (!server) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(EXIT_FAILURE);
	}
	bzero((char*)serv_addr, sizeof(serv_addr));
	serv_addr->sin_family = AF_INET;
	bcopy(server->h_addr_list[0], (char*)&serv_addr->sin_addr.s_addr,
		  server->h_length);
	serv_addr->sin_port = htons(port);

	/* Create socket */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        return 0;
    }

    int b = 1;
    b = atoi(argv[1]);

    printf("b is %d\n", b);
    
    struct sockaddr_in server;
    int sockfd = setup_client_socket(7800, "172.26.37.44", &server);

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) <
        0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    if( write(sockfd, "isubasinghe\n", strlen("isubasinghe\n")) < 0) {
        perror("1\n");
        return -1;
    }

    char writebuffer[1024];
    memset(writebuffer, 0, 1024);

    sprintf(writebuffer, "%d\n", mod_exp(g, b, p));

    printf(" g^bmodp is %s\n", writebuffer);

    if(write(sockfd, writebuffer, strlen(writebuffer)) < 0) {
        perror("2\n");
        return -1;
    }

    char buffer[1024];
    memset(buffer, 0, 1024);
    buffer[1023] = 0;

    if(read(sockfd, buffer, 1024) < 1) {
        perror("3\n");
        return -1;
    }

    printf("Return: %s\n", buffer);

    int gbmodp = atoi(buffer);
    memset(writebuffer, 0, 1024);

    sprintf(writebuffer, "%d\n", mod_exp(gbmodp, b, p));

    printf("The gbmodp ^b mod p is %s\n", writebuffer);

    if(write(sockfd, writebuffer, strlen(writebuffer)) < 0) {
        perror("4\n");
        return -1;
    }

    memset(buffer, 0, 1024);

    if(read(sockfd, buffer, 1024) < 1) {
        perror("5\n");
        return -1;
    }

    printf("Return: %s\n", buffer);


    close(sockfd);

    return 0;

}