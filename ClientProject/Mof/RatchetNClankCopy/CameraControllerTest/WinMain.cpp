#include "../CameraControllerTest/TestApp.h"


#ifdef _CONSOLE
int main(int argc, char* argv[]) {
#elif _NCONSOLE
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
#endif // CONSOLE
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Mof::LPFramework pFrame = new Mof::CDX11GameFramework();
    Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
    Info.pApplication = new  test::CGameApp();
    Info.Flag = MOF_FRAMEWORK_GRAPHICSINITIALIZE | MOF_FRAMEWORK_INPUTINITIALIZE | MOF_FRAMEWORK_APPLICATIONINITIALIZE;
    if (pFrame->Initialize(&Info)) {
        pFrame->Run();
    }
    MOF_SAFE_DELETE(pFrame);
    return 0;
}