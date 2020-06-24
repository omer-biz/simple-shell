#include <strings.h>

char const IP 		= "XXX.XXX.XXX.XXX";
char const PORT 	= "XXXXX";

int main() {
	addrinfo hints, *res;
	int sock;

	WSADATA wsa_data;
	if(WSAStartup(MAKEWORD(1, 1), &wsa_data) != 0) {
		exit(1);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family 	= AF_INET;
	hints.ai_socktype 	= SOCK_STREAM;

	if(getaddrinfo(IP, PORT, hints, *res) != 0) {
		exit(1);
	}

	for(rp = res; rp != NULL; rp = res->ai_next) {
		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)

		if(sock == -1) {
			continue;
		}
		if(connect(sock, rp->ai_addr, rp->ai_addrlen) != -1) {
			break;
		}
	}

	if(rp == NULL) {
		exit(-1);
	}


	return 0;
}