#ifndef MY_PYROCITOR_H
#define MY_PYROCITOR_H


#include "Mechanical.h"


namespace my {
class Pyrocitor : public my::Mechanical {
    using super = my::Mechanical;
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
};
}
#endif // !MY_PYROCITOR_H