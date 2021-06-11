#ifndef RATCHET_BOLT_COMPONENT_H
#define RATCHET_BOLT_COMPONENT_H


#include "../UpdateComponent.h"

#include "../../Actor/Item/Bolt.h"

namespace ratchet {
class BoltComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! アクターパラメータ
    ratchet::Bolt::Param _param;
    //! 移動先
    std::weak_ptr<ratchet::Actor> _player;
    //! 状態
    std::weak_ptr<class BoltActionStateComponent> _state_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BoltComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BoltComponent(const BoltComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BoltComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetActorParam(const ratchet::Bolt::Param& param);
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
    const ratchet::Bolt::Param& GetActorParam(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> GetPlayer(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_BOLT_COMPONENT_H