#ifndef MY_BulletItem_ACTION_COMPONENT_H
#define MY_BulletItem_ACTION_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"
#include "BulletItemActionStateComponent.h"
#include "../../../State/BulletItemActionStateDefine.h"


namespace my {
class BulletItemActionComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 速度
    std::weak_ptr<my::VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<my::BulletItemActionStateComponent> _state_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BulletItemActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BulletItemActionComponent(const BulletItemActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItemActionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_BulletItem_ACTION_COMPONENT_H