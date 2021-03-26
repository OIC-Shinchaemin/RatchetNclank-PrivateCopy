#ifndef MY_QUICK_CHANGE_SYSTEM_H
#define MY_QUICK_CHANGE_SYSTEM_H


#include <Mof.h>

#include "ResourceLocator.h"


namespace my {
class QuickChangeItem {
};
class QuickChangeSystem : public my::ResourceLocator {
    enum class State {
        Enter,
        Exit
    };
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
    State _state;
    //! �A���t�@
    float _alpha;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    QuickChangeSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~QuickChangeSystem();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    bool Render(void);
};
}
#endif // !MY_QUICK_CHANGE_SYSTEM_H