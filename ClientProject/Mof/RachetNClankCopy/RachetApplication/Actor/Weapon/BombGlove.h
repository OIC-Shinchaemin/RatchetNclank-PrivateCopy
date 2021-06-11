#ifndef RACHET_BOMB_GLOVEL_H
#define RACHET_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace rachet {
class BombGlove  : public rachet::Mechanical {
    using super = rachet::Mechanical;
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
#endif // !RACHET_BOMB_GLOVEL_H