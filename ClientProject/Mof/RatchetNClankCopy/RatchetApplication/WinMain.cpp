#include "GameApp.h"


#ifdef _CONSOLE
int main(int argc, char* argv[]) {
#elif _NCONSOLE
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
#endif // CONSOLE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);
	//_CrtMemState state;
	//_CrtMemCheckpoint(&state);
	//_CrtMemDumpStatistics(&state);


	Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.WindowCreateInfo.px = 400.0f;
	Info.WindowCreateInfo.py = 20.0f;
	Info.pApplication = new CGameApp();
	if (pFrame->Initialize(&Info)) {
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	//_CrtDumpMemoryLeaks();
	return 0;
}