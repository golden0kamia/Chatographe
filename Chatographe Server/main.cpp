#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include <SDL.h>
#include <SDL_net.h>

#define MAX_CLIENT 100
#define MAX_MSG_LENGTH 1004
#define MAX_NME_LENGTH 20
#define MAX_SND_LENGTH MAX_MSG_LENGTH + MAX_NME_LENGTH
#define MAX_RCV_LENGTH MAX_SND_LENGTH
#define MAX_DSP_MESSAGE 100
#define CMDSetColor SetConsoleTextAttribute
#define PINGTIMEOUT 15
#define PONGTIMEOUT 30

enum CMDColors {
	bgdbkfgdbk = 0,
	bgdbkfgdbl = 1,
	bgdbkfgdgr = 2,
	bgdbkfgdcy = 3,
	bgdbkfgdrd = 4,
	bgdbkfgdpk = 5,
	bgdbkfgdyw = 6,
	bgdbkfgdwh = 7,
	bgdbkfglbk = 8,
	bgdbkfglbl = 9,
	bgdbkfglgr = 10,
	bgdbkfglcy = 11,
	bgdbkfglrd = 12,
	bgdbkfglpk = 13,
	bgdbkfglyw = 14,
	bgdbkfglwh = 15,
	bgdblfgdbk = 16,
	bgdblfgdbl = 17,
	bgdblfgdgr = 18,
	bgdblfgdcy = 19,
	bgdblfgdrd = 20,
	bgdblfgdpk = 21,
	bgdblfgdyw = 22,
	bgdblfgdwh = 23,
	bgdblfglbk = 24,
	bgdblfglbl = 25,
	bgdblfglgr = 26,
	bgdblfglcy = 27,
	bgdblfglrd = 28,
	bgdblfglpk = 29,
	bgdblfglyw = 30,
	bgdblfglwh = 31,
	bgdgrfgdbk = 32,
	bgdgrfgdbl = 33,
	bgdgrfgdgr = 34,
	bgdgrfgdcy = 35,
	bgdgrfgdrd = 36,
	bgdgrfgdpk = 37,
	bgdgrfgdyw = 38,
	bgdgrfgdwh = 39,
	bgdgrfglbk = 40,
	bgdgrfglbl = 41,
	bgdgrfglgr = 42,
	bgdgrfglcy = 43,
	bgdgrfglrd = 44,
	bgdgrfglpk = 45,
	bgdgrfglyw = 46,
	bgdgrfglwh = 47,
	bgdcyfgdbk = 48,
	bgdcyfgdbl = 49,
	bgdcyfgdgr = 50,
	bgdcyfgdcy = 51,
	bgdcyfgdrd = 52,
	bgdcyfgdpk = 53,
	bgdcyfgdyw = 54,
	bgdcyfgdwh = 55,
	bgdcyfglbk = 56,
	bgdcyfglbl = 57,
	bgdcyfglgr = 58,
	bgdcyfglcy = 59,
	bgdcyfglrd = 60,
	bgdcyfglpk = 61,
	bgdcyfglyw = 62,
	bgdcyfglwh = 63,
	bgdrdfgdbk = 64,
	bgdrdfgdbl = 65,
	bgdrdfgdgr = 66,
	bgdrdfgdcy = 67,
	bgdrdfgdrd = 68,
	bgdrdfgdpk = 69,
	bgdrdfgdyw = 70,
	bgdrdfgdwh = 71,
	bgdrdfglbk = 72,
	bgdrdfglbl = 73,
	bgdrdfglgr = 74,
	bgdrdfglcy = 75,
	bgdrdfglrd = 76,
	bgdrdfglpk = 77,
	bgdrdfglyw = 78,
	bgdrdfglwh = 79,
	bgdpkfgdbk = 80,
	bgdpkfgdbl = 81,
	bgdpkfgdgr = 82,
	bgdpkfgdcy = 83,
	bgdpkfgdrd = 84,
	bgdpkfgdpk = 85,
	bgdpkfgdyw = 86,
	bgdpkfgdwh = 87,
	bgdpkfglbk = 88,
	bgdpkfglbl = 89,
	bgdpkfglgr = 90,
	bgdpkfglcy = 91,
	bgdpkfglrd = 92,
	bgdpkfglpk = 93,
	bgdpkfglyw = 94,
	bgdpkfglwh = 95,
	bgdywfgdbk = 96,
	bgdywfgdbl = 97,
	bgdywfgdgr = 98,
	bgdywfgdcy = 99,
	bgdywfgdrd = 100,
	bgdywfgdpk = 101,
	bgdywfgdyw = 102,
	bgdywfgdwh = 103,
	bgdywfglbk = 104,
	bgdywfglbl = 105,
	bgdywfglgr = 106,
	bgdywfglcy = 107,
	bgdywfglrd = 108,
	bgdywfglpk = 109,
	bgdywfglyw = 110,
	bgdywfglwh = 111,
	bgdwhfgdbk = 112,
	bgdwhfgdbl = 113,
	bgdwhfgdgr = 114,
	bgdwhfgdcy = 115,
	bgdwhfgdrd = 116,
	bgdwhfgdpk = 117,
	bgdwhfgdyw = 118,
	bgdwhfgdwh = 119,
	bgdwhfglbk = 120,
	bgdwhfglbl = 121,
	bgdwhfglgr = 122,
	bgdwhfglcy = 123,
	bgdwhfglrd = 124,
	bgdwhfglpk = 125,
	bgdwhfglyw = 126,
	bgdwhfglwh = 127,
	bglbkfgdbk = 128,
	bglbkfgdbl = 129,
	bglbkfgdgr = 130,
	bglbkfgdcy = 131,
	bglbkfgdrd = 132,
	bglbkfgdpk = 133,
	bglbkfgdyw = 134,
	bglbkfgdwh = 135,
	bglbkfglbk = 136,
	bglbkfglbl = 137,
	bglbkfglgr = 138,
	bglbkfglcy = 139,
	bglbkfglrd = 140,
	bglbkfglpk = 141,
	bglbkfglyw = 142,
	bglbkfglwh = 143,
	bglblfgdbk = 144,
	bglblfgdbl = 145,
	bglblfgdgr = 146,
	bglblfgdcy = 147,
	bglblfgdrd = 148,
	bglblfgdpk = 149,
	bglblfgdyw = 150,
	bglblfgdwh = 151,
	bglblfglbk = 152,
	bglblfglbl = 153,
	bglblfglgr = 154,
	bglblfglcy = 155,
	bglblfglrd = 156,
	bglblfglpk = 157,
	bglblfglyw = 158,
	bglblfglwh = 159,
	bglgrfgdbk = 160,
	bglgrfgdbl = 161,
	bglgrfgdgr = 162,
	bglgrfgdcy = 163,
	bglgrfgdrd = 164,
	bglgrfgdpk = 165,
	bglgrfgdyw = 166,
	bglgrfgdwh = 167,
	bglgrfglbk = 168,
	bglgrfglbl = 169,
	bglgrfglgr = 170,
	bglgrfglcy = 171,
	bglgrfglrd = 172,
	bglgrfglpk = 173,
	bglgrfglyw = 174,
	bglgrfglwh = 175,
	bglcyfgdbk = 176,
	bglcyfgdbl = 177,
	bglcyfgdgr = 178,
	bglcyfgdcy = 179,
	bglcyfgdrd = 180,
	bglcyfgdpk = 181,
	bglcyfgdyw = 182,
	bglcyfgdwh = 183,
	bglcyfglbk = 184,
	bglcyfglbl = 185,
	bglcyfglgr = 186,
	bglcyfglcy = 187,
	bglcyfglrd = 188,
	bglcyfglpk = 189,
	bglcyfglyw = 190,
	bglcyfglwh = 191,
	bglrdfgdbk = 192,
	bglrdfgdbl = 193,
	bglrdfgdgr = 194,
	bglrdfgdcy = 195,
	bglrdfgdrd = 196,
	bglrdfgdpk = 197,
	bglrdfgdyw = 198,
	bglrdfgdwh = 199,
	bglrdfglbk = 200,
	bglrdfglbl = 201,
	bglrdfglgr = 202,
	bglrdfglcy = 203,
	bglrdfglrd = 204,
	bglrdfglpk = 205,
	bglrdfglyw = 206,
	bglrdfglwh = 207,
	bglpkfgdbk = 208,
	bglpkfgdbl = 209,
	bglpkfgdgr = 210,
	bglpkfgdcy = 211,
	bglpkfgdrd = 212,
	bglpkfgdpk = 213,
	bglpkfgdyw = 214,
	bglpkfgdwh = 215,
	bglpkfglbk = 216,
	bglpkfglbl = 217,
	bglpkfglgr = 218,
	bglpkfglcy = 219,
	bglpkfglrd = 220,
	bglpkfglpk = 221,
	bglpkfglyw = 222,
	bglpkfglwh = 223,
	bglywfgdbk = 224,
	bglywfgdbl = 225,
	bglywfgdgr = 226,
	bglywfgdcy = 227,
	bglywfgdrd = 228,
	bglywfgdpk = 229,
	bglywfgdyw = 230,
	bglywfgdwh = 231,
	bglywfglbk = 232,
	bglywfglbl = 233,
	bglywfglgr = 234,
	bglywfglcy = 235,
	bglywfglrd = 236,
	bglywfglpk = 237,
	bglywfglyw = 238,
	bglywfglwh = 239,
	bglwhfgdbk = 240,
	bglwhfgdbl = 241,
	bglwhfgdgr = 242,
	bglwhfgdcy = 243,
	bglwhfgdrd = 244,
	bglwhfgdpk = 245,
	bglwhfgdyw = 246,
	bglwhfgdwh = 247,
	bglwhfglbk = 248,
	bglwhfglbl = 249,
	bglwhfglgr = 250,
	bglwhfglcy = 251,
	bglwhfglrd = 252,
	bglwhfglpk = 253,
	bglwhfglyw = 254,
	bglwhfglwh = 255,

	CMDnormal = 7,
	CMDblue = 9,
	CMDgood, CMDgreen = 10,
	CMDcyan = 11,
	CMDerror, CMDred = 12,
	CMDpink = 13,
	CMDwarning, CMDyellow = 14,
	CMDwhite = 15
};

typedef struct client {
	char* pseudo;
	TCPsocket socket;
	double timeout;
	bool awaitTime;
} client;

char** strcut(char* strin);
int strjoin(char** dst, char* src);
char* strjoin(char* dst, char* src);
char* strfill(char* strin, int len);
/// <summary>
/// Create a structured String to send.
/// </summary>
/// <param name="name">Name of the client or data info</param>
/// <param name="msg">Message to send</param>
/// <returns></returns>
char* makeMsg(char* name, char* msg);
void pushList(client* list);

int main(int argc, char** argv) {
	double SDLfrequency = (double)SDL_GetPerformanceFrequency();
	//Get console info
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool running = true;
	if (SDL_Init(SDL_INIT_EVENTS)) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDL_Init: %s\n", SDL_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-1);
	}
	if (SDLNet_Init()) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-2);
		running = false;
	}

	IPaddress selfIP;
	if (SDLNet_ResolveHost(&selfIP, NULL, short(16257))) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-3);
	}
	TCPsocket selfSocket = SDLNet_TCP_Open(&selfIP);
	if (selfSocket == NULL) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-4);
	}
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_CLIENT + 1);
	if (socketSet == NULL) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-5);
	}
	if (!SDLNet_TCP_AddSocket(socketSet, selfSocket)) {
		CMDSetColor(hConsole, CMDerror);
		printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		CMDSetColor(hConsole, CMDnormal);
		return(-6);
	}
	client clientsSocket[MAX_CLIENT] = {};
	int connectedClient = 0;
	//--Setup clients list--
	for (int i = 0; i < MAX_CLIENT; i++) {
		clientsSocket[i] = { (char*)"", NULL, 0, false };
	}

	SDL_Event event;
	CMDSetColor(hConsole, CMDcyan);
	printf("Start Server\n");
	CMDSetColor(hConsole, CMDnormal);
	while (running)
	{
		//--Testing client connection--
		SDLfrequency = (double)SDL_GetPerformanceFrequency();
		for (int i = 0; i < connectedClient; i++) {
			double localcounter = (SDL_GetPerformanceCounter() - clientsSocket[i].timeout) / SDLfrequency;
			if (localcounter >= PINGTIMEOUT && localcounter < PONGTIMEOUT && !clientsSocket[i].awaitTime) {
				//printf("list: %p\n", (clientsSocket + i));
				char* msgSend = makeMsg((char*)"/Server test\\", (char*)"ping");
				SDLNet_TCP_Send(clientsSocket[i].socket, msgSend, MAX_SND_LENGTH);
				CMDSetColor(hConsole, CMDcyan);
				//printf("Send ping to client %s\n", clientsSocket[i].pseudo);
				CMDSetColor(hConsole, CMDnormal);
				clientsSocket[i].awaitTime = true;
			}
			else if (localcounter >= PONGTIMEOUT) {
				CMDSetColor(hConsole, CMDerror);
				printf("Error client %s timeout, disconnecting\n", clientsSocket[i].pseudo);
				CMDSetColor(hConsole, CMDcyan);
				printf("%s Disconnected\n", clientsSocket[i].pseudo);
				CMDSetColor(hConsole, CMDnormal);
				//printf("SDLNet_TCP_Recv: %s\n", SDL_GetError());
				SDLNet_TCP_DelSocket(socketSet, clientsSocket[i].socket);
				SDLNet_TCP_Close(clientsSocket[i].socket);
				connectedClient--;
				pushList(clientsSocket);
			}
		}

		int clientActive = SDLNet_CheckSockets(socketSet, 0);
		//printf("SDLNet_CheckSockets: %d\n", clientActive);
		if (clientActive) {
			int active = SDLNet_SocketReady(selfSocket);
			//printf("SDLNet_SocketReady: selfSocket: %d\n", active);
			//--Connecting client--
			if (active && connectedClient < MAX_CLIENT) {
				clientsSocket[connectedClient].socket = SDLNet_TCP_Accept(selfSocket);
				clientsSocket[connectedClient].timeout = (double)SDL_GetPerformanceCounter();
				clientsSocket[connectedClient].pseudo = (char*)SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(clientsSocket[connectedClient].socket));
				clientsSocket[connectedClient].awaitTime = false;
				if (clientsSocket[connectedClient].socket != NULL) {
					int added = SDLNet_TCP_AddSocket(socketSet, clientsSocket[connectedClient].socket);
					//printf("SDLNet_TCP_AddSocket: %d\n", added);
					if (added) {
						char* msgSend = makeMsg((char*)"/Info Server\\", (char*)"Welcome to Zerock Server");
						int send = SDLNet_TCP_Send(clientsSocket[connectedClient].socket, msgSend, MAX_SND_LENGTH);
						//printf("Send welcome: %d\n", send);
						if (send >= MAX_SND_LENGTH) {
							//printf("Successfull welcome\n");
						}
						CMDSetColor(hConsole, CMDcyan);
						printf("%s connected\n", clientsSocket[connectedClient].pseudo);
						CMDSetColor(hConsole, CMDnormal);
						connectedClient++;
					}
					else {
						//printf("SDLNet_TCP_Accept: %s\n", SDLNet_GetError());
						SDLNet_TCP_Close(clientsSocket[connectedClient].socket);
					}
				}
				clientActive--;
				active = 0;
			}
			//--Client activity--
			for (int i = 0; i < connectedClient && clientActive; i++) {
				//printf("Client active: %d\n", clientActive);
				int ready = SDLNet_SocketReady(clientsSocket[i].socket);
				//printf("SDLNet_SocketReady: client[%d]: %d\n", i, ready);
				if (ready) {
					char dataIn[MAX_SND_LENGTH];
					int recieve = SDLNet_TCP_Recv(clientsSocket[i].socket, dataIn, MAX_SND_LENGTH);
					//printf("SDLNet_TCP_Recv: %d\n", recieve);
					if (recieve > 0) {
						clientsSocket[i].timeout = (double)SDL_GetPerformanceCounter();
						char** msgIn = strcut(dataIn);
						char* from = clientsSocket[i].pseudo;
						printf("%s>> %s: %s\n", from, *(msgIn), *(msgIn + 1));

						if (!strcmp(*(msgIn), "/Client pseudo\\")) {
							//printf("pseudo enter\n");
							clientsSocket[i].pseudo = *(msgIn + 1);
							SDLNet_TCP_Send(clientsSocket[i].socket, makeMsg(*(msgIn), *(msgIn + 1)), MAX_SND_LENGTH);
						}
						if (!strcmp(*(msgIn), "/Server test\\")) {
							//printf("testing server\n");
							if (!strcmp(*(msgIn + 1), "pong")) clientsSocket[i].awaitTime = false;
						}
						if (!strcmp(*(msgIn), "/Close session\\")) {
							//printf("Closing session\n");
							CMDSetColor(hConsole, CMDcyan);
							printf("%s Disconnected\n", from);
							CMDSetColor(hConsole, CMDnormal);
							//printf("SDLNet_TCP_Recv: %s\n", SDL_GetError());
							SDLNet_TCP_DelSocket(socketSet, clientsSocket[i].socket);
							SDLNet_TCP_Close(clientsSocket[i].socket);
							clientsSocket[i] = {};
							connectedClient--;
							pushList(clientsSocket);
						}
						if (!strcmp(*(msgIn), "/Text message\\")) {
							//printf("Message\n");
							char* sendMsg = makeMsg(from, *(msgIn + 1));
							for (int j = 0; j < connectedClient; j++)
								if (j != i) SDLNet_TCP_Send(clientsSocket[j].socket, sendMsg, MAX_SND_LENGTH);
						}
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

char** strcut(char* strin) {
	char** text = (char**)calloc(sizeof(char*), 2);
	*(text) = (char*)calloc(sizeof(char), MAX_NME_LENGTH);
	*(text + 1) = (char*)calloc(sizeof(char), MAX_MSG_LENGTH);
	for (int i = 0; i < MAX_NME_LENGTH; i++) {
		*(*(text)+i) = *(strin + i);
	}
	for (int i = 0; i < MAX_MSG_LENGTH; i++) {
		*(*(text + 1) + i) = *(strin + i + MAX_NME_LENGTH);
	}
	return text;
}

char* strfill(char* strin, int len) {
	char* text = (char*)calloc(sizeof(char), len);
	int leng = strlen(strin);
	for (int i = 0; i < leng; i++)
		*(text + i) = *(strin + i);
	for (int i = leng; i < len; i++)
		*(text + i) = '\0';
	return text;
}

int strjoin(char** dst, char* src) {
	int dstLen = sizeof(*dst) / sizeof(**dst);
	int srcLen = sizeof(src) / sizeof(*src);
	char* join = (char*)calloc(sizeof(char), (dstLen + srcLen));
	char* tmp = *dst;
	for (int i = 0; i < dstLen; i++)
		*(join + i) = *(tmp + i);
	for (int i = 0; i < srcLen; i++)
		*(join + i + dstLen) = src[i];
	*dst = join;
	return dstLen + srcLen;
}

char* strjoin(char* dst, char* src) {
	char* join = (char*)calloc(sizeof(char), MAX_SND_LENGTH);
	for (int i = 0; i < MAX_NME_LENGTH; i++)
		*(join + i) = *(dst + i);
	for (int i = 0; i < MAX_MSG_LENGTH; i++)
		*(join + i + MAX_NME_LENGTH) = src[i];
	return join;
}

char* makeMsg(char* name, char* msg) {
	name = strfill(name, MAX_NME_LENGTH);
	msg = strfill(msg, MAX_MSG_LENGTH);
	char* sndMsg = NULL;
	sndMsg = strjoin(name, msg);
	return sndMsg;
}

void pushList(client* list) {
	for (int i = 0; i < (MAX_CLIENT - 1); i++) {
		//printf("list socket: %d\n", list[i].socket);
		if (list[i].socket == NULL) {
			list[i].awaitTime = list[i + 1].awaitTime;
			list[i].pseudo = list[i + 1].pseudo;
			list[i].socket = list[i + 1].socket;
			list[i].timeout = list[i + 1].timeout;
		}
	}
}
