#ifndef RATCHET_BOMB_GLOVEL_H
#define RATCHET_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace ratchet {
class BombGlove  : public ratchet::Mechanical {
    using super = ratchet::Mechanical;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BombGlove();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGlove();
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
};
}
#endif // !RATCHET_BOMB_GLOVEL_H