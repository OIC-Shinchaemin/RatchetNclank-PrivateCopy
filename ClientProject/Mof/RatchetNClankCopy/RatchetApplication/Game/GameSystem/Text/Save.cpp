#include	"Save.h"




//���݂̃V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gScene;
//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;
//�ύX�t���O(�O���Q�ƁA���̂�GameApp.cpp)
//extern bool						gbChange;


//�����蔻��p�̋�`��`
CRectangle						gReturnRec(704, 664, 960, 704);			//���ǂ�


/**
 * �R���X�g���N�^
 *
 */
CSave::CSave() :
    m_BackImage(),
    m_ReturnImage(),
    m_Alpha(0),
    m_bEnd(false),
    m_bSave(false),
    m_PrevScene(SCENENO_TITLE) {
    memset(m_Tag, 0, sizeof(FILETAG) * SAVECOUNT);
}

/**
 * �f�X�g���N�^
 *
 */
CSave::~CSave() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CSave::Load(void) {
    //�e�N�X�`���̓ǂݍ���
    if (!m_BackImage.Load("Save.png")) {
        return false;
    }
    if (!m_ReturnImage.Load("Return.png")) {
        return false;
    }
    return true;
}

/**
 * �t�@�C���^�O�̓ǂݍ���
 *
 * ����
 * [in]			name			�ǂݍ��݃t�@�C����
 * [in]			i				�ǂݍ��ݔԍ�
 */
bool CSave::LoadTag(const char* name, int i) {
    HANDLE hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        m_Tag[i].bFile = false;
        return false;
    }
    //�t�@�C�����擾
    BY_HANDLE_FILE_INFORMATION fileInformation;
    GetFileInformationByHandle(hFile, &fileInformation);
    CloseHandle(hFile);
    //�t�@�C�����Ԃ���V�X�e�����Ԃɕϊ�
    FILETIME localFileTime;
    SYSTEMTIME systemTime;
    FileTimeToLocalFileTime(&fileInformation.ftLastWriteTime, &localFileTime);
    FileTimeToSystemTime(&localFileTime, &systemTime);
    //�z��ɏ���ۑ�
    m_Tag[i].bFile = true;
    m_Tag[i].Year = systemTime.wYear;
    m_Tag[i].Month = systemTime.wMonth;
    m_Tag[i].Day = systemTime.wDay;
    m_Tag[i].Hour = systemTime.wHour;
    m_Tag[i].Minute = systemTime.wMinute;
    return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CSave::Initialize(void) {
    m_bEnd = false;
    m_Alpha = 0;
}

/**
 * �A���t�@�l�̍X�V
 *
 */
void CSave::UpdateAlpha(void) {
    //�I����ԂȂ�t�F�[�h�A�E�g
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

/**
 * �X�V
 *
 */
void CSave::Update(void) {
    //�A���t�@�l�̍X�V
    UpdateAlpha();

    //�J�ڒ��͂���ȍ~�̏����͂��Ȃ�
    //if (m_bEnd || gScene != gChangeScene) {
        //return;
    //}

    //�}�E�X�N���b�N�őJ�ڔ���
    if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
        //�}�E�X���W�̎擾
        float px, py;
        g_pInput->GetMousePos(px, py);
        //�u���ǂ�v�{�^���ڐG����
        if (gReturnRec.CollisionPoint(px, py)) {
            //�O�̃V�[���ɖ߂�
            m_bEnd = true;
            //gChangeScene = m_PrevScene;
        }
    }
}

/**
 * �`��
 *
 */
void CSave::Render(void) {
    m_BackImage.Render(0, 0, MOF_ARGB(m_Alpha, 255, 255, 255));
    CGraphicsUtilities::RenderString(10, 10, MOF_ARGB(m_Alpha, 255, 255, 255), ((m_bSave) ? "�ۑ�" : "�ǂݍ���"));

    //�}�E�X�ʒu�擾
    float px, py;
    g_pInput->GetMousePos(px, py);

    //�u���ǂ�v�{�^���ڐG����
    if (gReturnRec.CollisionPoint(px, py)) {
        m_ReturnImage.Render(704, 664, MOF_ARGB(m_Alpha, 255, 255, 255));
    }
}

/**
 * �f�o�b�O�`��
 *
 */
void CSave::RenderDebug(void) {
}

/**
 * ���
 *
 */
void CSave::Release(void) {
    m_BackImage.Release();
    m_ReturnImage.Release();
}