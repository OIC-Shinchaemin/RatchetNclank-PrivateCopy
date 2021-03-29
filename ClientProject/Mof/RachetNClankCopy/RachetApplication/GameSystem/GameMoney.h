#ifndef MY_GAME_MONEY_H
#define MY_GAME_MONEY_H


#include <memory>
#include <string>

#include <Mof.h>

#include "../ResourceLocator.h"


namespace my {
class GameMoney : public my::ResourceLocator {
private:
//! ���O
    std::string _name;
    //! �w�i
    std::weak_ptr<Mof::CTexture> _texture;
    //! �ʒu
    Mof::CVector2 _position;
    //! �F
    Mof::CVector4 _color;
    //! ���
    //State _state;
    //! �A���t�@
    //float _alpha;
    
    uint32_t _value;
    //! �t�H���g
    Mof::CFont _font;
    //! �t�H���g
    std::size_t _font_size;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameMoney();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameMoney();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::uint32_t GetValue(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    bool Initialize(uint32_t value);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    bool Render(void);
};
}
#endif // !MY_GAME_MONEY_H