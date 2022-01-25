#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_net.h>

#define MAX_CLIENT 100
#define MAX_LENGTH 1024

int strjoin(char** dst, char* src);

int main(int argc, char** argv) {
	bool running = true;
	if (SDL_Init(SDL_INIT_EVENTS)) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(-1);
	}
	if (SDLNet_Init()) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(-2);
		running = false;
	}

	IPaddress selfIP;
	if (SDLNet_ResolveHost(&selfIP, NULL, short(71625))) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-3);
	}
	TCPsocket selfSocket = SDLNet_TCP_Open(&selfIP);
	if (selfSocket == NULL) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(-4);
	}
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_CLIENT + 1);
	if (socketSet == NULL) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(-5);
	}
	if (!SDLNet_TCP_AddSocket(socketSet, selfSocket)) {
		printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-6);
	}
	TCPsocket clientsSocket[MAX_CLIENT];
	int connectedClient = 0;

	SDL_Event event;
	printf("Start Server\n");
	while (running)
	{
		int clientActive = SDLNet_CheckSockets(socketSet, 0);
		//printf("SDLNet_CheckSockets: %d\n", clientActive);
		if (clientActive) {
			int active = SDLNet_SocketReady(selfSocket);
			//printf("SDLNet_SocketReady: selfSocket: %d\n", active);
			if (active && connectedClient < MAX_CLIENT) {
				clientsSocket[connectedClient] = SDLNet_TCP_Accept(selfSocket);
				if (clientsSocket[connectedClient] != NULL) {
					int added = SDLNet_TCP_AddSocket(socketSet, clientsSocket[connectedClient]);
					//printf("SDLNet_TCP_AddSocket: %d\n", added);
					if (added) {
						const char* msg = "Welcome to Zerock Server";
						int len = (int)strlen(msg) + 1;
						int send = SDLNet_TCP_Send(clientsSocket[connectedClient], msg, len);
						//printf("Send welcome: %d\n", send);
						if (send >= len) {
							//printf("Successfull welcome\n");
						}
						printf("%s connected successfully\n", SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(clientsSocket[connectedClient])));
						connectedClient++;
					}
					else {
						//printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
						SDLNet_TCP_Close(clientsSocket[connectedClient]);
					}
				}
				clientActive--;
				active = 0;
			}
			for (int i = 0; i < connectedClient && clientActive; i++) {
				//printf("Client active: %d\n", clientActive);
				int ready = SDLNet_SocketReady(clientsSocket[i]);
				//printf("SDLNet_SocketReady: client[%d]: %d\n", i, ready);
				if (ready) {
					char dataIn[MAX_LENGTH];
					int recieve = SDLNet_TCP_Recv(clientsSocket[i], dataIn, MAX_LENGTH);
					//printf("SDLNet_TCP_Recv: %d\n", recieve);
					if (recieve > 0) {
						char* from = (char*)SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(clientsSocket[i]));
						printf("%s>> %s\n",from , dataIn);
						strjoin(&from, (char*)">> ");
						strjoin(&from, dataIn);
						for (int j = 0; j < connectedClient; j++) {
							if (j != i) {
								SDLNet_TCP_Send(clientsSocket[j], from, MAX_LENGTH);
							}
						}
					}
					else {
						printf("%s Disconnected: %d\n", SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(clientsSocket[i])), recieve);
						printf("SDLNet_TCP_Recv: %s\n", SDL_GetError());
						SDLNet_TCP_DelSocket(socketSet, clientsSocket[i]);
						SDLNet_TCP_Close(clientsSocket[i]);
						connectedClient--;
					}
					clientActive--;
					ready = 0;
				}
			}
			clientActive = 0;
		}

		//Event Endling
		if (SDL_PollEvent(&event)) {
			switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
	}

	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

int strjoin(char** dst, char* src) {
	int dstLen = strlen(*dst);
	int srcLen = strlen(src);
	int joinLen = dstLen + srcLen + 1;
	char* join = (char*)malloc(joinLen);
	char* tmp = *dst;
	for (int i = 0; i < dstLen; i++) {
		*(join+i) = *(tmp + i);
	}
	for (int i = 0; i < srcLen; i++) {
		*(join+i + dstLen) = src[i];
	}
	*(join+joinLen-1) = '\0';
	*dst = join;
	return joinLen;
}
