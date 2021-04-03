#ifndef MY_ACTOR_H
#define MY_ACTOR_H


#include <memory>
#include <string>

#include <Mof.h>

#include "My/Core/Define.h"
#include "My/Core/Observable.h"
#include "Collision/CollisionObject.h"


namespace my {
enum class ActorState {
    Active,
    End
};
class Actor : public std::enable_shared_from_this<my::Actor>, public my::Observable<const char*, const std::shared_ptr<my::Actor>&> {
    using Observable = my::Observable<const char*, const std::shared_ptr<my::Actor>&>;
private:
    //! 状態
    my::ActorState _state;
    //! トランスフォーム
    def::Transform _transform;
    //! 衝突用
    std::shared_ptr<my::CollisionObject> _collision_object;
protected:
    /// <summary>
    /// 生成
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name=""></param>
    template<typename Type, typename Owner>
    void GenerateCollisionObject(std::shared_ptr<Owner> ptr) {
        _collision_object = std::make_shared<Type>();
        _collision_object->SetOwner(ptr);
    }
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="rotate"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="position"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Actor();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Actor();    
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="rotate"></param>
    void SetRotate(Mof::CVector3 rotate);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="scale"></param>
    void SetScale(Mof::CVector3 scale);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>名前</returns>
    std::string GetName(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetRotate(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetScale(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::ActorState GetState(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::CollisionObject> GetCollisionObject(void) const;
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    void End(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ACTOR_H