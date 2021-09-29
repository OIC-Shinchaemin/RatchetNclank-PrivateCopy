#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SAVE_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SAVE_H


#include <Mof.h>


#define	SAVECOUNT 20
//標準のアルファ変化速度
#define	ALPHA_SPEED	15


namespace ratchet::game::gamesystem::text {
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
    //当たり判定用の矩形定義
    CRectangle gReturnRec;
    

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
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SAVE_H