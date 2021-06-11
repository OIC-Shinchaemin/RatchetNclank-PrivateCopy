#ifndef RACHET_PYROCITOR_H
#define RACHET_PYROCITOR_H


#include "Mechanical.h"


namespace rachet {
class Pyrocitor : public rachet::Mechanical {
    using super = rachet::Mechanical;
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
#endif // !RACHET_PYROCITOR_H