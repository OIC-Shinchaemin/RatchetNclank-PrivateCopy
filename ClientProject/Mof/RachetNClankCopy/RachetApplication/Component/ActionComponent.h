#ifndef MY_ACTION_COMPONENT_H
#define MY_ACTION_COMPONENT_H


#include "UpdateComponent.h"

#include <string_view>


namespace my {
class ActionComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    //void ChageState(const std::string& name);
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
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    //virtual bool Start(void) override;
};
}
#endif // !MY_ACTION_COMPONENT_H