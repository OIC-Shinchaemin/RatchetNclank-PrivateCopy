#include	"Menu.h"


CMenu::CMenu() :
    m_cx(0.0f),
    m_cy(0.0f),
    m_HSpace(12),
    m_VSpace(8),
    m_Count(0),
    m_pTitle(NULL),
    m_pItem(NULL),
    m_Select(0),
    m_bShow(false),
    m_bEnter(false),
    m_Rect(),
    m_HeaderRect(),
    m_bDrag(false) {
}

CMenu::~CMenu() {
    Release();
}

void CMenu::Create(char* pTitle, char** pItem, int cnt) {
    //�Â��f�[�^�̉��
    Release();
    //�����̕������ۑ�
    m_Count = cnt;
    m_pTitle = (char*)malloc(strlen(pTitle) + 1);
    strcpy(m_pTitle, pTitle);
    m_pItem = (char**)malloc(sizeof(char*) * cnt);
    for (int i = 0; i < m_Count; i++) 	{
        m_pItem[i] = (char*)malloc(strlen(pItem[i]) + 1);
        strcpy(m_pItem[i], pItem[i]);
    }
    //���j���[�̕�����̍ő�A�ŏ���`�����߂�
    CRectangle trec;
    CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
    m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
    m_Rect.Bottom += trec.Bottom + m_VSpace * 2;
    m_HeaderRect = m_Rect;
    for (int i = 0; i < m_Count; i++) 	{
        CGraphicsUtilities::CalculateStringRect(0, 0, m_pItem[i], trec);
        m_HeaderRect.Right = m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
        m_Rect.Bottom += trec.Bottom + m_VSpace;
    }
    m_Rect.Bottom += m_VSpace;
}

void CMenu::Release(void) {
    if (m_pTitle) 	{
        free(m_pTitle);
        m_pTitle = NULL;
    }
    if (m_pItem) 	{
        for (int i = 0; i < m_Count; i++) 		{
            free(m_pItem[i]);
        }
        free(m_pItem);
        m_pItem = NULL;
        m_Count = 0;
    }
    m_Rect = CRectangle(0, 0, 0, 0);
}

void CMenu::Show(float cx, float cy) {
    m_cx = cx;
    m_cy = cy;
    m_bShow = true;
    m_bEnter = false;
    m_bDrag = false;
    m_Select = 0;
    float w = m_Rect.GetWidth();
    float h = m_Rect.GetHeight();
    m_Rect.Top = m_cy - h * 0.5f;
    m_Rect.Bottom = m_Rect.Top + h;
    m_Rect.Left = m_cx - w * 0.5f;
    m_Rect.Right = m_Rect.Left + w;
    m_HeaderRect.Bottom = m_Rect.Top + m_HeaderRect.GetHeight();
    m_HeaderRect.Top = m_Rect.Top;
    m_HeaderRect.Right = m_Rect.Left + m_HeaderRect.GetWidth();
    m_HeaderRect.Left = m_Rect.Left;
}

void CMenu::Update(void) {
    if (!m_bShow) 	{
        return;
    }
    //�}�E�X�ʒu�őI��
    float px, py;
    g_pInput->GetMousePos(px, py);
    CRectangle trec;
    CRectangle hrec = m_HeaderRect;
    m_Select = -1;
    for (int i = 0; i < m_Count; i++) 	{
        CGraphicsUtilities::CalculateStringRect(0, 0, m_pItem[i], trec);
        hrec.Top = hrec.Bottom;
        hrec.Bottom += trec.Bottom + m_VSpace * 2;
        if (hrec.CollisionPoint(px, py)) 		{
            m_Select = i;
        }
    }
    //���N���b�N�Ō���
    if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) 	{
        //�w�b�_�[�̃h���b�O�ňړ�������
        if (m_HeaderRect.CollisionPoint(px, py)) 		{
            m_bDrag = true;
        }
        else if (m_Select >= 0 && m_Select < m_Count) 		{
            m_bEnter = true;
        }
    }
    //�h���b�O�ړ�
    if (m_bDrag && g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON)) 	{
        float mx, my;
        g_pInput->GetMouseMove(mx, my);
        char str[128];
        sprintf(str, "%f / %f\n", mx, my);
        OutputDebugString(str);
        m_cx += mx;
        m_cy += my;
        m_Rect.Left += mx;
        m_Rect.Right += mx;
        m_Rect.Top += my;
        m_Rect.Bottom += my;
        m_HeaderRect.Left += mx;
        m_HeaderRect.Right += mx;
        m_HeaderRect.Top += my;
        m_HeaderRect.Bottom += my;
    }
    else 	{
        m_bDrag = false;
    }
}

void CMenu::Render(void) {
    if (!m_bShow) 	{
        return;
    }
    //���j���[�̔w�i�`��
    CGraphicsUtilities::RenderFillRect(m_Rect, MOF_ARGB(200, 0, 0, 0));
    CGraphicsUtilities::RenderFillRect(m_HeaderRect, MOF_ARGB(200, 64, 64, 64));
    //���ڂ̕�����`�悷��
    CRectangle trec;
    float py = m_Rect.Top + m_VSpace;
    CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
    CGraphicsUtilities::RenderString(m_cx - trec.GetWidth() * 0.5f, py, MOF_COLOR_WHITE, m_pTitle);
    py += trec.Bottom + m_VSpace;
    for (int i = 0; i < m_Count; i++) 	{
        CGraphicsUtilities::CalculateStringRect(0, 0, m_pItem[i], trec);
        CGraphicsUtilities::RenderString(m_cx - trec.GetWidth() * 0.5f, py + m_VSpace, ((m_Select == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_pItem[i]);
        py += trec.Bottom + m_VSpace;
    }
}