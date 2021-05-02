#ifndef MY_FACTORY_H
#define MY_FACTORY_H


#include <memory>
#include <string>
#include<unordered_map>

#include "Creator.h"


namespace my {
template <typename T>
class Factory {
private:
    std::unordered_map<std::string, std::unique_ptr<my::ICreator<T>>> _products;
public:
    template<typename Derived>
    void Register(const std::string& key) {
        _products[key] = std::make_unique<my::Creator<T, Derived>>();
    }
    /// <summary>
    /// çÏê¨
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::shared_ptr<T> Create(const std::string& key){
        return _products[key]->Create();
    }
};
}
#endif // !MY_FACTORY_H