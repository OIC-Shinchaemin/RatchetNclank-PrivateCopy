#ifndef RACHET_CREATOR_H
#define RACHET_CREATOR_H


#include <memory>

#include "Base/Core/Utility.h"


namespace rachet {
template <typename T>
class ICreator {
public:
    /// <summary>
    /// çÏê¨
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<T> Create(void) const = 0;
};
template <typename Base, typename Derived>
class Creator : public rachet::ICreator<Base> {
public:
    /// <summary>
    /// çÏê¨
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<Base> Create(void) const override {
        if constexpr (ty::has_func_release<Base>::value) {
            return ut::MakeSharedWithRelease<Derived>();
        } // if
        return std::make_shared<Derived>();
    }
};
}
#endif // !RACHET_CREATOR_H