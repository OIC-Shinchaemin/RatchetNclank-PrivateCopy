#ifndef RACHET_BLASTER_H
#define RACHET_BLASTER_H


#include "Mechanical.h"


namespace rachet {
class Blaster : public rachet::Mechanical {
    using super = rachet::Mechanical;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Blaster();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Blaster();
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
#endif // !RACHET_BLASTER_H