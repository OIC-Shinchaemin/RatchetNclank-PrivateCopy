#ifndef MY_HP_COMPONENT_H
#define MY_HP_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/StateMachine.h"
#include "My/Core/Timer.h"


namespace my {
class HpComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    int _hp;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    HpComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    HpComponent(const HpComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~HpComponent();
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
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
#ifdef _DEBUG
    virtual bool Render(void) override;
#endif // _DEBUG
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
#endif // !MY_HP_COMPONENT_H