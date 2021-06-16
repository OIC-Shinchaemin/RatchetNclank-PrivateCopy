#ifndef RATCHET_FACTORY_FACTORY_H
#define RATCHET_FACTORY_FACTORY_H


#include <memory>
#include <string>
#include<unordered_map>

#include "Creator.h"


namespace ratchet {
namespace factory {
template <typename T>
class Factory {
private:
    std::unordered_map<std::string, std::unique_ptr<ratchet::factory::ICreator<T>>> _products;
public:
    template<typename Derived>
    void Register(const std::string& key) {
        _products[key] = std::make_unique<ratchet::factory::Creator<T, Derived>>();
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
}
#endif // !RATCHET_FACTORY_FACTORY_H