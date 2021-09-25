#ifndef RATCHET_COMPONENT_QUEEN_QUEEN_COMPONENT_H
#define RATCHET_COMPONENT_QUEEN_QUEEN_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Character/Queen.h"


namespace ratchet::component::queen {
class QueenComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    QueenComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    QueenComponent(const QueenComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~QueenComponent();
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !RATCHET_COMPONENT_QUEEN_QUEEN_COMPONENT_H