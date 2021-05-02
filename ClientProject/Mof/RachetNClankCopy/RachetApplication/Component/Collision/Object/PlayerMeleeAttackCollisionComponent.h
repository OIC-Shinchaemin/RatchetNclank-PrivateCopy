#ifndef MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace my {
class PlayerMeleeAttackCollisionComponent : public my::CollisionComponent {
    using super = my::CollisionComponent;
private:
    //! 大きさ
    float _volume;
    //! アクターからの距離
    float _front_offset;
    //! プレイヤー
    std::weak_ptr<class PlayerComponent> _player_com;
    //! 攻撃
    std::weak_ptr<class PlayerMeleeAttackOneComponent> _attack_one_com;
    //! 攻撃
    std::weak_ptr<class PlayerMeleeAttackTwoComponent> _attack_two_com;
    //! 攻撃
    std::weak_ptr<class PlayerMeleeAttackThreeComponent> _attack_three_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackCollisionComponent(const PlayerMeleeAttackCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMeleeAttackCollisionComponent();
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
    virtual std::optional<Mof::CSphere> GetSphere(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<my::SightObject> GetSightObject(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;    
};
}
#endif // !MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H