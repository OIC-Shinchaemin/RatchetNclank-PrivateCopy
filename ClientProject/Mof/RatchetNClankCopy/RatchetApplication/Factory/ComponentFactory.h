#ifndef RATCHET_FACTORY_COMPONENT_FACTORY_H
#define RATCHET_FACTORY_COMPONENT_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "Base/Core/Define.h"
#include "ComponentCreator.h"


namespace ratchet {
namespace factory {
class ComponentFactory {
    using ComponentMap = std::unordered_map<std::string, std::shared_ptr<factory::ComponentCreator>>;
private:
    //! 所有
    ComponentMap _component_creators;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ComponentFactory();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ComponentFactory();
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    bool Release(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    bool AddComponentCreator(void) {
        // 指定のコンポーネントを登録する
        auto creator = std::make_shared<ratchet::factory::ComponentCreator>();
        creator->AddOrigin<T>();

        // 既にあるなら追加しない
        auto key = creator->GetComponentType();
        auto it = _component_creators.find(key);
        if (it != _component_creators.end()) {
            return false;
        } // if
        _component_creators.emplace(key, creator);
        return true;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<component::Component> Create(const std::string& key, const rapidjson::Value& param) const;
};
}
}
#endif // !RATCHET_FACTORY_COMPONENT_FACTORY_H