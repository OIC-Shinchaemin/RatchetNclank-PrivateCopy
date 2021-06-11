#ifndef RACHET_FACTORY_H
#define RACHET_FACTORY_H


#include <memory>
#include <string>
#include<unordered_map>

#include "Creator.h"


namespace rachet {
template <typename T>
class Factory {
private:
    std::unordered_map<std::string, std::unique_ptr<rachet::ICreator<T>>> _products;
public:
    template<typename Derived>
    void Register(const std::string& key) {
        _products[key] = std::make_unique<rachet::Creator<T, Derived>>();
    }
    /// <summary>
    /// çÏê¨
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::shared_ptr<T> Create(const std::string& key) const {
        return _products.at(key)->Create();
    }
};
}
#endif // !RACHET_FACTORY_H