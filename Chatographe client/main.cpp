#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <xthreads.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_net.h>
#include <kiss_sdl.h>

#define MAX_SERVER 1
#define MAX_LENGTH 1024

int lscanf(void* output);

int main(int argc, char** argv) {
	SDL_Renderer* gRenderer;
	kiss_array object;
	kiss_window window;
	kiss_window_new(&window, NULL, 1, 0, 0, kiss_screen_width, kiss_screen_height);
	
	bool running = true;
	const char* host  = "127.0.0.1";
	if (argc != 1) {
		host = argv[1];
	}
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
	if (SDLNet_ResolveHost(&selfIP, host, short(71625))) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(-3);
	}
	TCPsocket selfSocket = SDLNet_TCP_Open(&selfIP);
	if (selfSocket == NULL) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(-4);
	}
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_LENGTH + 1);
	if (socketSet == NULL) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(-5);
	}
	if (!SDLNet_TCP_AddSocket(socketSet, selfSocket)) {
		printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		exit(-6);
	}
	//TCPsocket serverSocket[MAX_SERVER];
	int connectedServer = 0;
	
	char readLine[MAX_LENGTH] = "";
	void* passRead = (void**)&readLine;
	SDL_Thread* readerThread;
	readerThread = SDL_CreateThread(lscanf, "Reader thread", &passRead);
	SDL_DetachThread(readerThread);


	SDL_Event event;
	printf("Start client\n");
	while (running) {
		int serverActive = SDLNet_CheckSockets(socketSet, 0);
		if (serverActive) {
			int selfActive = SDLNet_SocketReady(selfSocket);
			if (selfActive) {
				char dataIn[MAX_LENGTH];
				int lenIn = SDLNet_TCP_Recv(selfSocket, dataIn, MAX_LENGTH);
				//printf("lenIn: %d\n", lenIn);
				//printf("dataIn: %s\n", dataIn);
				if (lenIn > 0) {
					printf("%s\n", dataIn);
				}
			}
		}

		//printf("passRead: %s\n", (char*)passRead);
		int compare = strcmp((char*)passRead, "");
		//printf("compare: %d\n", compare);
		if (compare) {
			//printf("compare good\n");
			int msgLen = (int)strlen((char*)passRead) + 1;
			//printf("msgLen: %d", msgLen);
			SDLNet_TCP_Send(selfSocket, (char*)passRead, msgLen);
			for (int i = 0; i < MAX_LENGTH; i++) {
				passRead = readLine;
			}
		}
		
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				printf("Exit\n");
				SDLNet_TCP_Close(selfSocket);
				Sleep(1000);
				break;
			default:
				break;
			}
		}
		Sleep(1000);
	}
	
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

static int lscanf(void* output){
	char** myput = (char**)output;
	int ret = 0;
	bool stop = false;
	char readed[MAX_LENGTH];
	while (1) {
		for (int i = 0; i < MAX_LENGTH && !stop; i++) {
			int val = getchar();
			//printf("val: %d\n", val);
			switch (val) {
			case EOF:
				ret = -1;
				stop = true;
				break;
			case 10:
				stop = true;
				for (int j = i; j < MAX_LENGTH; j++) {
					readed[i] = '\0';
				}
				break;
			default:
				readed[i] = char(val);
				ret++;
				break;
			}
		}
		*myput = readed;
		stop = false;

	}
	return ret;
}
