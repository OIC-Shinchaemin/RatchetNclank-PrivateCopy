#ifndef RATCHET_FACTORY_COMPONENT_CREATOR_H
#define RATCHET_FACTORY_COMPONENT_CREATOR_H


#include <memory>

#include "rapidjson/document.h"

#include "../Component/Component.h"


namespace ratchet::factory {
class ComponentCreator {
private:
    //! コピー元
    std::unique_ptr<ratchet::component::Component> _origin;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ComponentCreator();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ComponentCreator();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetComponentType(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    template<typename T>
    void AddOrigin(void) {
        _origin = std::make_unique<T>(0);
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::component::Component> Create(const rapidjson::Value& param) const;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !RATCHET_FACTORY_COMPONENT_CREATOR_H