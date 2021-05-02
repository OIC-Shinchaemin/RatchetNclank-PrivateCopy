#include    "GameApp.h"
#include    <imgui/MofImGui.h>

#ifdef _DEBUG
//int main(int argc, char* argv[])
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
#else
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
#endif //_DEBUG
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
    Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
    Info.pApplication            = new CGameApp();
    Info.WindowCreateInfo.pProc  = new CMofImGuiProc();
    Info.WindowCreateInfo.Style  = WS_OVERLAPPEDWINDOW;
    Info.WindowCreateInfo.Width  = 1280;
    Info.WindowCreateInfo.Height =  720;

    if (pFrame->Initialize(&Info))
    {
        pFrame->Run();
    }
    MOF_SAFE_DELETE(pFrame);
    return 0;
}