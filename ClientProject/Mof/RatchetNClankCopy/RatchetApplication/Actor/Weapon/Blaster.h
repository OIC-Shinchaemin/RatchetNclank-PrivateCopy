#ifndef RATCHET_BLASTER_H
#define RATCHET_BLASTER_H


#include "Mechanical.h"


namespace ratchet {
class Blaster : public ratchet::Mechanical {
    using super = ratchet::Mechanical;
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
#endif // !RATCHET_BLASTER_H