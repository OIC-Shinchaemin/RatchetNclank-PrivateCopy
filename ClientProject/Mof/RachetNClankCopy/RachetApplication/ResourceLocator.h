#ifndef MY_RESOURCE_LOCATOR_H
#define MY_RESOURCE_LOCATOR_H


#include "My/Core/ServiceLocator.h"

#include <memory>

#include "ResourceManager.h"
#include "GameDefine.h"


namespace my {
class ResourceLocator: public ServiceLocator<my::ResourceMgr> {
public:
    using super = my::ServiceLocator<my::ResourceMgr>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResourceLocator();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ResourceLocator();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ResourceMgr> GetService(void) const = delete;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="key"></param>
    /// <returns></returns>
    template<class T>
    std::shared_ptr<T> GetResource(const char* key) {
        if (auto ptr = super::GetService(); ptr) {
            return ptr->Get<std::shared_ptr<T>>(key);
        } // if
        return nullptr;
    }
};
}
#endif // !MY_RESOURCE_LOCATOR_H