#ifndef RATCHET_STATE_MOTION_STATE_H
#define RATCHET_STATE_MOTION_STATE_H


#include "Base/Core/State.h"

#include <memory>
#include <string>

#include "../Component/MotionComponent.h"


namespace ratchet {
namespace state {
class MotionState : public base::core::State {
public:
    struct Param {
        //! 名前
        const char* state_name;
        //! 名前
        const char* motion_name;
        //! タイプ
        int motion_type;
        //! アニメーション速度
        float motion_speed;
        //! アニメーションループ
        bool motion_loop;
        //! アニメーションフラグ
        bool motion_same;
        Param() :
            state_name(),
            motion_name(),
            motion_type(),
            motion_speed(),
            motion_loop(),
            motion_same() {
        }
        template<typename Enum>
        Param(const std::string& state, const std::string& name, Enum type, float speed = 1.0f, bool loop = true, bool same = true) :
            state_name(state.c_str()),
            motion_name(name.c_str()),
            motion_type(static_cast<int>(type)),
            motion_speed(speed),
            motion_loop(loop),
            motion_same(same) {
        }
    };
private:
    //! パラメータ
    Param _param;
    //! モーション
    std::weak_ptr<ratchet::MotionComponent> _motion_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MotionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MotionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    void SetParam(const state::MotionState::Param& param);
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
}
#endif // !RATCHET_STATE_PLAYER_MOTION_STATE_H