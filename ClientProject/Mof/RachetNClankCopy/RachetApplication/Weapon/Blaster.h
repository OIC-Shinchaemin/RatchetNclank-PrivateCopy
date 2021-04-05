#ifndef MY_BLASTER_H
#define MY_BLASTER_H


#include "Mechanical.h"


namespace my {
class Blaster : public my::Mechanical {
    using super = my::Mechanical;
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
#endif // !MY_BLASTER_H