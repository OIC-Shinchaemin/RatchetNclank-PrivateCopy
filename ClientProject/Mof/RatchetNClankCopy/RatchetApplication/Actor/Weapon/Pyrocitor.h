#ifndef RATCHET_PYROCITOR_H
#define RATCHET_PYROCITOR_H


#include "Mechanical.h"


namespace ratchet {
class Pyrocitor : public ratchet::Mechanical {
    using super = ratchet::Mechanical;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Pyrocitor();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Pyrocitor();
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
#endif // !RATCHET_PYROCITOR_H