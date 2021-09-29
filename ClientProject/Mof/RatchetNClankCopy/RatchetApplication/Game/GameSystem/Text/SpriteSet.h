#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H


#include <Mof.h>


namespace ratchet::game::gamesystem::text {
class CSpriteSet : public CSprite2D {
public:
    char* Trim(char* s) {
            //�����̕����񂪂Ȃ�
        if (!s) {
            return NULL;
        }
        //������̌�납��󔒈ȊO�����������̈ʒu��\0�i�I�[�j��ݒ肷��
        int l = strlen(s);
        while (--l >= 0) {
            if (s[l] != '\t' && s[l] != '\r' && s[l] != '\n' && s[l] != ' ') {
                break;
            }
        }
        s[l + 1] = '\0';
        //�擪����󔒈ȊO���������ʒu�̃|�C���^��Ԃ�
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
    //�e����̌p���֐�
    virtual MofBool Update();
    virtual MofBool Release(LPMofVoid pData = NULL);

    //�ǉ��֐�
    bool Load(const char* pName);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SCRIPT_SET_H