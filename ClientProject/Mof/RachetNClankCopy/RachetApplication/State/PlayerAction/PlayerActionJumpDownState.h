#ifndef STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H
#define STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H


#include "PlayerActionState.h"

#include "../../Component/Player/PlayerJumpDownComponent.h"


namespace state {
class PlayerActionJumpDownState : public state::PlayerActionState {
    using super = state::PlayerActionState;
private:
    //! ジャンプ
    std::weak_ptr<my::PlayerJumpDownComponent> _jump_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerActionJumpDownState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerActionJumpDownState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) override;
};
}
#endif // !STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H