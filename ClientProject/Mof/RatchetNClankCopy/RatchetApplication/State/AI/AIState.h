#ifndef RATCHET_STATE_AI_AI_STATE_H
#define RATCHET_STATE_AI_AI_STATE_H


#include "Base/Core/State.h"

#include <memory>
#include <string>

#include "../../Actor/Actor.h"
#include "../../Behaviour/Executor/INodeExecutor.h"


namespace ratchet {
namespace state {
namespace ai {
class AIState : public base::core::State {
    using super = base::core::State;
protected:
    //! 通知
    std::weak_ptr<ratchet::actor::Actor> _actor;
    //! ビヘイビア実行
    ratchet::behaviour::NodeExecutorPtr _behaviour_executor;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::Actor> GetActor(void) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AIState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AIState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="path"></param>
    void GenerateBehaviourExecutor(const std::string& path);
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
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
#endif // _DEBUG
};
}
}
}
#endif // !RATCHET_STATE_AI_AI_STATE_H