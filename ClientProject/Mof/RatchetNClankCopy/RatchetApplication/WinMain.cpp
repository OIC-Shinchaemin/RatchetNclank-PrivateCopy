#include "GameApp.h"


#ifdef _CONSOLE
int main(int argc, char* argv[]) {
#elif _NCONSOLE
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
#endif // CONSOLE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(xxxxxx);
	//_CrtMemState state;
	//_CrtMemCheckpoint(&state);
	//_CrtMemDumpStatistics(&state);

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
//	Info.WindowCreateInfo.

	//Info.WindowCreateInfo.px = 400.0f;
	//Info.WindowCreateInfo.py = 20.0f;
//<<<<<<< Ex185_BulletActionFix
	Info.WindowCreateInfo.Width = ratchet::kWindowWidth;
	Info.WindowCreateInfo.Height = ratchet::kWindowHeihgt;
	//Info.GraphicsCreateInfo.bWindowed = FALSE;
	Info.GraphicsCreateInfo.bWindowed = TRUE;
//=======
	//Info.WindowCreateInfo.Width = 1920;
	//Info.WindowCreateInfo.Height = 1080;
	//Info.GraphicsCreateInfo.bWindowed = FALSE;
	Info.GraphicsCreateInfo.bWindowed = TRUE;
//>>>>>>> MofLib

	//Info.Flag = MOF_FRAMEWORK_GRAPHICSINITIALIZE | MOF_FRAMEWORK_INPUTINITIALIZE | MOF_FRAMEWORK_APPLICATIONINITIALIZE;
	Info.pApplication = new CGameApp();
	if (pFrame->Initialize(&Info)) {
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	//_CrtDumpMemoryLeaks();
	return 0;
}