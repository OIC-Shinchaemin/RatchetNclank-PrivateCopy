#ifndef MY_BulletItem_ACTION_STATE_COMPONENT_H
#define MY_BulletItem_ACTION_STATE_COMPONENT_H


#include "../../ActionStateComponent.h"

#include "../../../State/BulletItemActionStateDefine.h"


namespace my {
class BulletItemActionStateComponent : public my::ActionStateComponent {
    using super = my::ActionStateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BulletItemActionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BulletItemActionStateComponent(const BulletItemActionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItemActionStateComponent();
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
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(const std::string& next);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !MY_BulletItem_ACTION_STATE_COMPONENT_H