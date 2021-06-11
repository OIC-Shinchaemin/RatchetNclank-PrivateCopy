#ifndef STATE_AI_STATE_H
#define STATE_AI_STATE_H


#include "Base/Core/State.h"

#include <memory>
#include <string>

#include "../../Actor.h"
#include "../../Behaviour/Executor/INodeExecutor.h"


namespace state {
class AIState : public base::core::State {
    using super = state::AIState;
protected:
    //! 通知
    std::weak_ptr<ratchet::Actor> _actor;
    //! ビヘイビア実行
    behaviour::NodeExecutorPtr _behaviour_executor;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> GetActor(void) const;
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
    virtual void SetActor(const std::shared_ptr<ratchet::Actor>& ptr);
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
#endif // !STATE_AI_STATE_H