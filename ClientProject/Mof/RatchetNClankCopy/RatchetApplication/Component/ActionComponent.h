#ifndef RATCHET_COMPONENT_ACTION_COMPONENT_H
#define RATCHET_COMPONENT_ACTION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>


namespace ratchet {
namespace component {
class ActionComponent : public ::ratchet::component::UpdateComponent {
    using super = ::ratchet::component::UpdateComponent;
private:
    //! 現在のアクション
    std::shared_ptr<::ratchet::component::ActionComponent> _current_action;
    //! アクション
    std::unordered_map<std::string, std::shared_ptr<::ratchet::component::ActionComponent>> _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ActionComponent(const ActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetOwner(const std::shared_ptr<::ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string_view GetStateType(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    std::shared_ptr<T>GetComponent(void) const {
        for (auto& child : _children) {
            auto ret = std::dynamic_pointer_cast<T>(child.second);
            if (ret) {
                return ret;
            } // if
        } // for
        return nullptr;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::unordered_map<std::string, std::shared_ptr<::ratchet::component::ActionComponent>>& GetChildren(void);
    /// <summary>
    /// 入力判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsInput(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void);
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool End(void);
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeAction(std::string_view name);
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
}
#endif // !RATCHET_COMPONENT_ACTION_COMPONENT_H