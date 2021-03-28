#ifndef MY_PYROCITOR_H
#define MY_PYROCITOR_H


#include "Mechanical.h"


namespace my {
class Pyrocitor : public my::Mechanical {
    using super = my::Mechanical;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Pyrocitor();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Pyrocitor();
};
}
#endif // !MY_PYROCITOR_H