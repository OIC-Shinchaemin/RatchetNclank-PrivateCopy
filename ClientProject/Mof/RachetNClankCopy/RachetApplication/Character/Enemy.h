#ifndef MY_ENEMY_H
#define MY_ENEMY_H
 

#include "Character.h"

#include "../SightRecognition.h"
#include "../Behaviour/Executor/INodeExecutor.h"


namespace my {
enum class AIState {
    Patrol,
    Combat
};
class Enemy : public my::Character {
    using super = my::Character;
    using EnemyPtr = std::shared_ptr<my::Enemy>;
private:
    //! 初期位置
    Mof::CVector3 _init_position;
    //! 標的
    std::weak_ptr<my::Character>_target;
    //! 視覚
    my::SightRecognition _sight;
    //! 状態
    my::AIState _state;
    //! ビヘイビア実行
    behaviour::NodeExecutorPtr< EnemyPtr > _patrol_behaviour_executor;
    //! ビヘイビア実行
    behaviour::NodeExecutorPtr< EnemyPtr > _combat_behaviour_executor;
    
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr< EnemyPtr >  CreatePatrolBehaviour(void);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr< EnemyPtr >  CreateCombatBehaviour(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTarget(void) const;
    /// <summary>
    /// 見渡す
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
    /// 追いかける
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Chase(void);
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
    /// <summary>
    /// 初期位置に戻る
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ENEMY_H