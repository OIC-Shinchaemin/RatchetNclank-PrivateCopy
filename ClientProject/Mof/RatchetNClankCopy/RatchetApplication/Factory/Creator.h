#ifndef RATCHET_FACTORY_CREATOR_H
#define RATCHET_FACTORY_CREATOR_H


#include <memory>

#include "Base/Core/Utility.h"


namespace ratchet::factory {
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
class Creator : public ratchet::factory::ICreator<Base> {
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
#endif // !RATCHET_FACTORY_CREATOR_H