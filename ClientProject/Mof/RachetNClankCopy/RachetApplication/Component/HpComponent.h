#ifndef MY_HP_COMPONENT_H
#define MY_HP_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/Observable.h"
#include "My/Core/StateMachine.h"
#include "My/Core/Timer.h"


namespace my {
class HpComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 最大値
    int _hp_max;
    //! Hp
    int _hp;
    //! Hp
    my::Observable<int> _observable;
    //! UI表示
    bool _ui_remove;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetHp(void) const;
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
    /// <summary>
    /// 回復
    /// </summary>
    /// <param name="value"></param>
    void Heal(int value);
    /// <summary>
    /// ダメージ
    /// </summary>
    /// <param name="value"></param>
    void Damage(int value);
};
}
#endif // !MY_HP_COMPONENT_H