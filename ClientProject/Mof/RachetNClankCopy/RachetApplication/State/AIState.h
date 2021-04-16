#ifndef STATE_AI_STATE_H
#define STATE_AI_STATE_H


#include "My/Core/State.h"

#include <memory>
#include <string>

#include "../Actor.h"
#include "../Actor/Character/Enemy.h"
#include "../Behaviour/Executor/INodeExecutor.h"
#include "../Factory/BehaviourExecutorFactory.h"


namespace state {
class AIState : public my::State {
    using super = state::AIState;
protected:
    //! 通知
    std::weak_ptr<my::Enemy> _enemy;
    //! ビヘイビア実行
    behaviour::NodeExecutorPtr _behaviour_executor;
    //! パス
    std::string _behaviour_path;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Enemy> GetEnemy(void) const;
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
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void GenerateBehaviourExecutor(void);
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
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
};
}
#endif // !STATE_AI_STATE_H