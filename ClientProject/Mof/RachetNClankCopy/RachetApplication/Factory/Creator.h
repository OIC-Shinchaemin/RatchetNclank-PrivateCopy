#ifndef MY_CREATOR_H
#define MY_CREATOR_H


#include <memory>

#include "My/Core/Utility.h"


namespace my {
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
class Creator : public my::ICreator<Base> {
public:
    /// <summary>
    /// çÏê¨
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<Base> Create(void) const override {
        return ut::MakeSharedWithRelease<Derived>();
    }
};
}
#endif // !MY_CREATOR_H