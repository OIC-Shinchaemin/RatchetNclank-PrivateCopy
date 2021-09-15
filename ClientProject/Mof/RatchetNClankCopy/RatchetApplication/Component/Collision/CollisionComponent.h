#ifndef RATCHET_COMPONENT_COLLISION_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_COLLISION_COMPONENT_H


#include "../Component.h"

#include <optional>
#include <any>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "../../Stage/StageObject.h"
#include "../../Stage/Gimmick/GimmickBase.h"
#include "../VelocityComponent.h"


namespace ratchet::component::collision {
struct SightObject {
    //! 視点
    Mof::CVector3 position;
    //! 向き
    Mof::CVector3 rotate;
    SightObject() :
        position(), rotate() {
    }
    SightObject(Mof::CVector3 pos, Mof::CVector3 rot) :
        position(pos), rotate(rot) {
    }
};
struct PlaneObject {
    //! 視点
    Mof::CVector3 position;
    //! 向き
    Mof::CVector3 normal;
    PlaneObject() :
        position(), normal() {
    }
    PlaneObject(Mof::CVector3 pos, Mof::CVector3 norm) :
        position(pos), normal(norm) {
    }
};
struct CollisionInfo {
    //! 埋まり値
    float distance = 0.0f;
    //! 角度
    Mof::CVector3 angle;
    //! 速さ
    float speed = 0.0f;
    //! 衝突対象
    std::weak_ptr<actor::Actor> target;

    CollisionInfo() : distance(0.0f), angle(), speed(0.0f), target() {}
    CollisionInfo(const Mof::COLLISIONOUTGEOMETRY& c) : distance(c.d), angle(), speed(0.0f), target() {}
};
class CollisionComponent : public component::Component {
public:
    enum class CollisionFuncType {
        Enter,
        Stay,
        Exit,
    };
    class CollisionFunc {
        using Func = std::function<bool(const component::collision::CollisionInfo&)>;
    private:
        //! 実行関数
        Func _func;
    public:
        CollisionFunc() :_func() {}
        CollisionFunc(Func func) :_func(func) {}
        void AddFunction(Func lambda) {
            this->_func = lambda;
        }
        bool Execute(const component::collision::CollisionInfo& info) const {
            return _func(info);
        }
    };

    using super = ::ratchet::component::Component;
    using FuncArray = std::vector<CollisionFunc>;
private:
    //! 衝突したオブジェクト
    std::vector<std::weak_ptr<::ratchet::component::collision::CollisionComponent>> _collisioned;
    //! 実行関数
    std::unordered_map<std::string, FuncArray> _on_enter;
    //! 実行関数
    std::unordered_map<std::string, FuncArray> _on_stay;
    //! 実行関数
    std::unordered_map<std::string, FuncArray> _on_exit;
    //! 速度
    std::weak_ptr<component::VelocityComponent> _velocity_com;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="target"></param>
    /// <param name="obj"></param>
    /// <param name="out"></param>
    void AddCollisionFunc(const std::string& target, const CollisionFunc& obj, std::unordered_map<std::string, FuncArray>& out);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <param name="in"></param>
    /// <returns></returns>
    bool ExecuteFunction(const std::string& key, const component::collision::CollisionInfo& info, const std::unordered_map<std::string, FuncArray>& in);
protected:
    /// <summary>
    /// 衝突判定
    /// </summary>
    /// <param name="sphere"></param>
    /// <param name="box"></param>
    /// <returns></returns>
    bool CollisionShpereAABB(const Mof::CSphere& sphere, const Mof::CBoxAABB& box);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    CollisionComponent(int priority);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CollisionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetNextRay(void) {
        return std::optional<Mof::CRay3D>();
    };
  /// <summary>
  /// ゲッター
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<::ratchet::component::collision::PlaneObject> GetPlaneObject(void) {
        return std::optional<::ratchet::component::collision::PlaneObject>();
    };
      /// <summary>
      /// ゲッター
      /// </summary>
      /// <param name=""></param>
      /// <returns></returns>
    virtual std::optional<::ratchet::component::collision::SightObject> GetSightObject(void) = 0;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsSleep(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddCollisionedObject(const std::shared_ptr<ratchet::component::collision::CollisionComponent>& ptr);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveCollisionedObject(const std::shared_ptr<ratchet::component::collision::CollisionComponent>& ptr);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool ExistCollisionedObject(const std::shared_ptr<ratchet::component::collision::CollisionComponent>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="type"></param>
    /// <param name="target"></param>
    /// <param name="obj"></param>
    void AddCollisionFunc(CollisionFuncType type, const std::string& target, const CollisionFunc& obj);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteEnterFunction(const std::string& key, const component::collision::CollisionInfo& info);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteStayFunction(const std::string& key, const component::collision::CollisionInfo& info);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteExitFunction(const std::string& key, const component::collision::CollisionInfo& info);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="obj"></param>
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick);
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
#endif // !RATCHET_COMPONENT_COLLISION_COLLISION_COMPONENT_H