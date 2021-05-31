#ifndef MY_BOLT_COMPONENT_H
#define MY_BOLT_COMPONENT_H


#include "../UpdateComponent.h"

#include "../../Actor/Item/Bolt.h"

namespace my {
class BoltComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! アクターパラメータ
    my::Bolt::Param _param;
    //! 移動先
    std::weak_ptr<my::Actor> _player;
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
    void SetActorParam(const my::Bolt::Param& param);
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
    const my::Bolt::Param& GetActorParam(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor> GetPlayer(void) const;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_BOLT_COMPONENT_H