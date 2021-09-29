#include	"Save.h"


ratchet::game::gamesystem::text::CSave::CSave() :
    m_BackImage(),
    m_ReturnImage(),
    m_Alpha(0),
    m_bEnd(false),
    m_bSave(false),
    m_PrevScene(SCENENO_TITLE) {
    std::memset(m_Tag, 0, sizeof(FILETAG) * SAVECOUNT);
    gReturnRec = CRectangle(704, 664, 960, 704);			
}

ratchet::game::gamesystem::text::CSave::~CSave() {
}

bool ratchet::game::gamesystem::text::CSave::Load(void) {
    //テクスチャの読み込み
    if (!m_BackImage.Load("Save.png")) {
        return false;
    }
    if (!m_ReturnImage.Load("Return.png")) {
        return false;
    }
    return true;
}

bool ratchet::game::gamesystem::text::CSave::LoadTag(const char* name, int i) {
    HANDLE hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        m_Tag[i].bFile = false;
        return false;
    }
    //ファイル情報取得
    BY_HANDLE_FILE_INFORMATION fileInformation;
    GetFileInformationByHandle(hFile, &fileInformation);
    CloseHandle(hFile);
    //ファイル時間からシステム時間に変換
    FILETIME localFileTime;
    SYSTEMTIME systemTime;
    FileTimeToLocalFileTime(&fileInformation.ftLastWriteTime, &localFileTime);
    FileTimeToSystemTime(&localFileTime, &systemTime);
    //配列に情報を保存
    m_Tag[i].bFile = true;
    m_Tag[i].Year = systemTime.wYear;
    m_Tag[i].Month = systemTime.wMonth;
    m_Tag[i].Day = systemTime.wDay;
    m_Tag[i].Hour = systemTime.wHour;
    m_Tag[i].Minute = systemTime.wMinute;
    return true;
}

void ratchet::game::gamesystem::text::CSave::Initialize(void) {
    m_bEnd = false;
    m_Alpha = 0;
}

void ratchet::game::gamesystem::text::CSave::UpdateAlpha(void) {
    //終了状態ならフェードアウト
    if (m_bEnd) {
        if (m_Alpha - ALPHA_SPEED <= 0) {
            m_Alpha = 0;
            //gScene = gChangeScene;
            //gbChange = false;
        }
        else {
            m_Alpha -= ALPHA_SPEED;
        }
    }
    else {
        if (m_Alpha + ALPHA_SPEED >= 255) {
            m_Alpha = 255;
        }
        else {
            m_Alpha += ALPHA_SPEED;
        }
    }
}

void ratchet::game::gamesystem::text::CSave::Update(void) {
    //アルファ値の更新
    UpdateAlpha();

    //遷移中はこれ以降の処理はしない
    //if (m_bEnd || gScene != gChangeScene) {
        //return;
    //}

    //マウスクリックで遷移判定
    if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        //マウス座標の取得
        float px, py;
        g_pInput->GetMousePos(px, py);
        //「もどる」ボタン接触判定
        if (gReturnRec.CollisionPoint(px, py)) {
            //前のシーンに戻る
            m_bEnd = true;
            //gChangeScene = m_PrevScene;
        }
    }
}

void ratchet::game::gamesystem::text::CSave::Render(void) {
    m_BackImage.Render(0, 0, MOF_ARGB(m_Alpha, 255, 255, 255));
    CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(m_Alpha, 255, 255, 255), ((m_bSave) ? "保存" : "読み込み"));

    //マウス位置取得
    float px, py;
    g_pInput->GetMousePos(px, py);

    //「もどる」ボタン接触判定
    if (gReturnRec.CollisionPoint(px, py)) {
        m_ReturnImage.Render(704, 664, MOF_ARGB(m_Alpha, 255, 255, 255));
    }
}

void ratchet::game::gamesystem::text::CSave::RenderDebug(void) {
}

void ratchet::game::gamesystem::text::CSave::Release(void) {
    m_BackImage.Release();
    m_ReturnImage.Release();
}