#ifdef _DEBUG
#pragma comment(lib, "MofImGui_d.lib")
#elif NDEBUG
#pragma comment(lib, "MofImGui.lib")
#endif // !_DEBUG


#include "GameApp.h"
#include "imgui/MofImGui.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
//int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
    Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
    Info.pApplication = new CGameApp();
	//IMGUIPROC‚ÌÝ’è
	Info.WindowCreateInfo.pProc = new CMofImGuiProc();
    Info.GraphicsCreateInfo.bMSAA = FALSE;
    Info.Flag = MOF_FRAMEWORK_GRAPHICSINITIALIZE | MOF_FRAMEWORK_INPUTINITIALIZE | MOF_FRAMEWORK_APPLICATIONINITIALIZE;
    if (pFrame->Initialize(&Info)) {
        pFrame->Run();
    }
    MOF_SAFE_DELETE(pFrame);
    return 0;
}