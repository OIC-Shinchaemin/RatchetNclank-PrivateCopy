#ifndef RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Actor.h"
#include "../../Actor/Character/Character.h"
#include "Base/Core/Observable.h"

#include "../TransformComponent.h"
#include "../VelocityComponent.h"
#include "../CameraComponent.h"


namespace ratchet::actor::character {
class Player;
}
namespace ratchet::component::collision {
class PlayerCollisionComponent;
}
namespace ratchet::component::player {
class PlayerComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
    //! 標的
    std::weak_ptr<::ratchet::actor::Actor> _target;
    //! カーソル位置
    base::core::Observable<std::optional<Mof::CVector3>> _observable;
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! カメラ
    std::weak_ptr<ratchet::component::CameraComponent> _camera_com;
    //! カメラ
    std::weak_ptr<ratchet::component::collision::PlayerCollisionComponent> _coll_volume_com;
    //! 地点
    std::string _next_terrain;
    //! 接触モード 有効であれば武器ボタンがアクションボタンになる
    bool _contact_mode;
    //! 話し相手
    std::weak_ptr<ratchet::actor::character::Character> _talk_target;

    void CacheComponent(void);
    void CollisionFunctionBarrack(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionBarricade(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionKing(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionQueen(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionScarecrow(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionShop(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionShip(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionWall(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
    void CollisionFunctionWaterFlow(std::shared_ptr<ratchet::component::collision::PlayerCollisionComponent>& com);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerComponent(const PlayerComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<::ratchet::actor::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetNextTerrain(const std::string& terrain);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    std::shared_ptr<ratchet::actor::character::Player> GetOwnerCastd(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::weak_ptr<::ratchet::actor::Actor> GetTarget(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetNextTerrain(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsContactMode(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTalkTarget(void) const;
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
    /// <summary>
    /// 会話
    /// </summary>
    /// <param name=""></param>
    void TalkToTarget(void);
};
}
#endif // !RATCHET_COMPONENT_PLAYER_PLAYER_COMPONENT_H