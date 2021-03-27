#ifndef MY_CREATOR_H
#define MY_CREATOR_H


#include <memory>


namespace my {
template <typename T>
class ICreator {
public:
    /// <summary>
    /// ì¬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual  std::shared_ptr<T> Create(void) const {
        return std::make_shared<T>();
    }
};
template <typename Base, typename Derived>
class Creator : public my::ICreator<Base> {
public:
    /// <summary>
    /// ì¬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<Base> Create(void) const {
        return std::make_shared<Derived>();
    }
};
}
#endif // !MY_CREATOR_H