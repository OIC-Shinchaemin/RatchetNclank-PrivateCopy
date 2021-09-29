#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H


#include <Mof.h>


namespace ratchet::game::gamesystem::text {
class CSpriteSet : public CSprite2D {
public:
    char* Trim(char* s) {
            //引数の文字列がない
        if (!s) {
            return NULL;
        }
        //文字列の後ろから空白以外を見つけた次の位置に\0（終端）を設定する
        int l = strlen(s);
        while (--l >= 0) {
            if (s[l] != '\t' && s[l] != '\r' && s[l] != '\n' && s[l] != ' ') {
                break;
            }
        }
        s[l + 1] = '\0';
        //先頭から空白以外を見つけた位置のポインタを返す
        int p = 0;
        while (p < l) {
            if (s[p] != '\t' && s[p] != '\r' && s[p] != '\n' && s[p] != ' ') {
                return &s[p];
            }
            p++;
        }
        return s;
    }


    char m_FileName[MAX_PATH];
    CSpriteMotionController	m_Motion;
    CSpriteSet();
    virtual ~CSpriteSet();
    //親からの継承関数
    virtual MofBool Update();
    virtual MofBool Release(LPMofVoid pData = NULL);

    //追加関数
    bool Load(const char* pName);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H