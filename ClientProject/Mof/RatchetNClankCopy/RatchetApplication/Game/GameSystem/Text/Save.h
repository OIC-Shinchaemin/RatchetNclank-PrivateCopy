#pragma once

#define		SAVECOUNT				20

#include <Mof.h>

//標準のアルファ変化速度
#define		ALPHA_SPEED				15

//存在するシーンの列挙
enum tag_SCENENO {
    SCENENO_TITLE,
    SCENENO_GAME,
    SCENENO_SAVE,
};

class CSave {
private:
    CTexture				m_BackImage;
    CTexture				m_ReturnImage;
    BYTE					m_Alpha;
    bool					m_bEnd;
    bool					m_bSave;
    int						m_PrevScene;

    typedef struct tag_FILETAG {
        bool				bFile;
        int					Year;
        int					Month;
        int					Day;
        int					Hour;
        int					Minute;
    }FILETAG;
    FILETAG					m_Tag[SAVECOUNT];
public:
    CSave();
    ~CSave();
    bool Load(void);
    bool LoadTag(const char* name, int i);
    void Initialize(void);
    void UpdateAlpha(void);
    void Update(void);
    void Render(void);
    void RenderDebug(void);
    void Release(void);
    void SetState(int ps, bool s) { m_PrevScene = ps; m_bSave = s; }
};