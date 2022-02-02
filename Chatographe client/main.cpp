#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <xthreads.h>
#include <Windows.h>
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_syswm.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>

#define MAX_SERVER 1
#define MAX_MSG_LENGTH 1004
#define MAX_NME_LENGTH 20
#define MAX_RCV_LENGTH MAX_MSG_LENGTH + MAX_NME_LENGTH
#define MAX_DSP_MESSAGE 100

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

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

//int lscanf(void* output);
char** strcut(char* strin);
int strjoin(char** dst, char* src);
char* strfill(char* strin, int len);

int RcvMsg = 0;
char** nmsgs[MAX_DSP_MESSAGE] = {};
char msgs[5][2][MAX_MSG_LENGTH] = {{"Bastien-PC", "Hello wolrd!"},
	{"Kildef", "0123456789"},
	{"Bastien-PC", "()[]{}§+@#*%&//=?!áéíóúàèìòùâêîôû"},
	{"Bastien-PC", "abcdefghijklmnopqrstuvwxyz"},
	{"Kildef", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"}};

int main(int argc, char** argv) {
	//Get console info
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	const char* host  = "127.0.0.1";
	if (argc != 1) host = argv[1];

	//Init graphic system
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("SDL_Init: %s\n", SDL_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-1);
	}
	if (SDLNet_Init()) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-2);
	}
	SDL_Window* window = SDL_CreateWindow("Chatographe v2.0.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	HWND hwnd = (HWND)wmInfo.info.win.window;
	CreateDeviceD3D(hwnd);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsClassic();
	ImGui_ImplSDL2_InitForD3D(window);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	ImVec4 clear_color = { 0.15f, 0.15f, 0.15f, 1.f };

	//Init network system
	IPaddress selfIP;
	if (SDLNet_ResolveHost(&selfIP, host, short(71625))) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-3);
	}
	TCPsocket selfSocket = SDLNet_TCP_Open(&selfIP);
	if (selfSocket == NULL) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("DLNet_TCP_Open: %s\n", SDLNet_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-4);
	}
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAX_MSG_LENGTH + 1);
	if (socketSet == NULL) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-5);
	}
	if (!SDLNet_TCP_AddSocket(socketSet, selfSocket)) {
		SetConsoleTextAttribute(hConsole, CMDerror);
		printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
		SetConsoleTextAttribute(hConsole, CMDnormal);
		exit(-6);
	}
	char* selfName = (char*)SDLNet_ResolveIP(SDLNet_TCP_GetPeerAddress(selfSocket));
	//TCPsocket serverSocket[MAX_SERVER];
	int connectedServer = 0;

	//Init thread system
	/*char readLine[MAX_MSG_LENGTH] = "";
	void* passRead = (void**)&readLine;
	SDL_Thread* readerThread;
	readerThread = SDL_CreateThread(lscanf, "Reader thread", &passRead);
	SDL_DetachThread(readerThread);*/


	SDL_Event event;
	bool running = true;
	bool sending = false;
	char message[MAX_MSG_LENGTH] = {};
	printf("Start client\n");
	while (running) {

		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				printf("Exit\n");
				SDLNet_TCP_Close(selfSocket);
				break;
			case SDL_KEYUP:
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
					sending = true;
				}
			default:
				break;
			}
			CleanupRenderTarget;
			g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		ImVec4 color = { 14. / 255., 94. / 255., 14. / 255., 255. / 255. };
		ImVec4 color2 = { 138. / 255., 45. / 255., 75. / 255., 255. / 255. };
		{
			static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
			static float f = 0.0f;
			static int counter = 0;
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);

			ImGui::Begin("Settings", &running, flags);
			ImGui::BeginChild("Messages", ImVec2(viewport->Size.x - 20, -20), true, ImGuiWindowFlags_None);
			for (int i = 0; i < RcvMsg; i++) {
				if (!strcmp(*(*(nmsgs + i)), selfName)) {
					ImGui::TextColored(color, *(*(nmsgs + i)));
					ImGui::TextWrapped(*(*(nmsgs + i) + 1));
				}
				else {
					ImGui::Indent(100.f);
					ImGui::TextColored(color2, *(*(nmsgs + i)));
					ImGui::TextWrapped(*(*(nmsgs + i) + 1));
					ImGui::Unindent(100.f);
				}
				ImGui::Spacing();
			}
			ImGui::EndChild();
			ImGui::InputTextWithHint("##", "Write your message here", message, MAX_MSG_LENGTH);
			ImGui::SameLine();
			sending |= ImGui::Button("Send");

			ImGui::End();
		}

		ImGui::Render();
		const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		g_pSwapChain->Present(1, 0); // Present with vsync
		//g_pSwapChain->Present(0, 0); // Present without vsync

		int serverActive = SDLNet_CheckSockets(socketSet, 0);
		if (serverActive) {
			int selfActive = SDLNet_SocketReady(selfSocket);
			if (selfActive) {
				char dataIn[MAX_RCV_LENGTH];
				int lenIn = SDLNet_TCP_Recv(selfSocket, dataIn, MAX_RCV_LENGTH);
				//printf("lenIn: %d\n", lenIn);
				//printf("dataIn: %s\n", dataIn);
				if (lenIn > 0) {
					printf("%s\n", dataIn);
					nmsgs[RcvMsg] = strcut(dataIn);
					RcvMsg++;
					//Process message
				}
			}
		}

		/*//printf("passRead: %s\n", (char*)passRead);
		int compare = strcmp((char*)passRead, "");
		//printf("compare: %d\n", compare);
		if (compare) {
			//printf("compare good\n");
			int msgLen = (int)strlen((char*)passRead) + 1;
			//printf("msgLen: %d", msgLen);
			SDLNet_TCP_Send(selfSocket, (char*)passRead, msgLen);
			for (int i = 0; i < MAX_MSG_LENGTH; i++) {
				passRead = readLine;
			}
		}*/	
		
	
		if (sending && strcmp(message, "")) {
			int msgLen = (int)strlen((char*)message) + 1;
			//printf("msgLen: %d", msgLen);
			if (SDLNet_TCP_Send(selfSocket, (char*)message, msgLen)) {
				printf("Successfull sending\n");
				char* fillName = strfill(selfName, MAX_NME_LENGTH);
				char* fillmsg = strfill(message, MAX_MSG_LENGTH);
				strjoin(&fillName, fillmsg);
				nmsgs[RcvMsg] = strcut(fillName);
				RcvMsg++;
				for (int i = 0; i < MAX_MSG_LENGTH; i++) {
					message[i] = '\0';
				}
			}

			//Write to conv file
		}
		sending = false;

	}

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	SDL_DestroyWindow(window);
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}

/*static int lscanf(void* output) {
	char** myput = (char**)output;
	int ret = 0;
	bool stop = false;
	char readed[MAX_MSG_LENGTH];
	while (1) {
		for (int i = 0; i < MAX_MSG_LENGTH && !stop; i++) {
			int val = getchar();
			//printf("val: %d\n", val);
			switch (val) {
			case EOF:
				ret = -1;
				stop = true;
				break;
			case 10:
				stop = true;
				for (int j = i; j < MAX_MSG_LENGTH; j++) {
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
}*/

char** strcut(char* strin) {
	char** text = (char**)malloc(2 * sizeof(char*));
	*(text) = (char*)malloc(MAX_NME_LENGTH * sizeof(char));
	*(text+1) = (char*)malloc(MAX_MSG_LENGTH * sizeof(char));
	for (int i = 0; i < MAX_NME_LENGTH; i++) {
		*(*(text)+i) = *(strin + i);
	}
	for (int i = 0; i < MAX_MSG_LENGTH; i++) {
		*(*(text+1)+i) = *(strin + i+MAX_NME_LENGTH);
	}
	return text;
}

char* strfill(char* strin, int len) {
	char* text = (char*)malloc(len * sizeof(char));
	int leng = strlen(strin);
	for (int i = 0; i < leng; i++)
		*(text + i) = *(strin + i);
	for (int i = leng; i < len; i++)
		*(text + i) = '\0';
	return text;
}

int strjoin(char** dst, char* src) {
	char* join = (char*)malloc(MAX_RCV_LENGTH);
	char* tmp = *dst;
	for (int i = 0; i < MAX_NME_LENGTH; i++)
		*(join + i) = *(tmp + i);
	for (int i = 0; i < MAX_MSG_LENGTH; i++)
		*(join + i + MAX_NME_LENGTH) = src[i];
	*dst = join;
	return MAX_RCV_LENGTH;
}

bool CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}