#ifndef RATCHET_NanotechItem_MOVED_COMPONENT_H
#define RATCHET_NanotechItem_MOVED_COMPONENT_H


#include "NanotechItemActionComponent.h"

#include <memory>


namespace ratchet {
class NanotechItemMovedComponent : public ratchet::NanotechItemActionComponent {
    using super = ratchet::NanotechItemActionComponent;
private:
    //! 速度
    Mof::CVector3 _speed;
    //! 角度
    Mof::CVector3 _angle;
    //! 減衰
    float _decrase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemMovedComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemMovedComponent(const NanotechItemMovedComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItemMovedComponent();
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
    virtual std::string_view GetStateType(void) const override;
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
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_NanotechItem_MOVED_COMPONENT_H