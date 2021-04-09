#ifndef MY_ACTOR_H
#define MY_ACTOR_H


#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "My/Core/Define.h"
#include "My/Core/Observable.h"
#include "Collision/Object/CollisionObject.h"
#include "Velocity.h"


namespace my {
enum class ActorState {
    Active,
    End
};
class Actor : public std::enable_shared_from_this<my::Actor>, public my::Observable<const char*, const std::shared_ptr<my::Actor>&> {
public:
    using ComPtr = std::shared_ptr<class Component>;
    using ComArray = std::vector<ComPtr>;
    using Observable = my::Observable<const char*, const std::shared_ptr<my::Actor>&>;
public:
    struct Param {
        //! トランスフォーム
        def::Transform transform;
        //! 名前
        std::string name;

        Param() :
            transform(){
        }
        virtual ~Param() {
        }
    };
private:
    //! 状態
    my::ActorState _state;
    //! 名前
    std::string _name;
    //! トランスフォーム
    def::Transform _transform;
    //! 機能
    ComArray _components;
    ComArray _input_components;
    ComArray _update_components;
    ComArray _render_components;
    //! 衝突用
    std::vector<std::shared_ptr<my::CollisionObject>> _collision_objects;
protected:
    //! 速度
    my::Velocity _velocity;
    /// <summary>
    /// 生成
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name=""></param>
    template<typename Type>
    void AddCollisionObject(std::shared_ptr<Type> ptr) {
        _collision_objects.push_back(ptr);
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
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void UpdateTransform(float delta_time);
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
    /// <param name="name"></param>
    void SetName(const char* name);
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
    /// <returns></returns>
    my::ActorState GetState(void) const;
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
    const std::vector<std::shared_ptr<my::CollisionObject>>& GetCollisionObjects(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    std::shared_ptr<T>GetComponent(void) const {
        for (auto& com : _components) {
            auto ret = std::dynamic_pointer_cast<T>(com);
            if (ret) {
                return ret;
            } // if
        } // for
        return nullptr;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="out"></param>
    template <typename T>
    void GetComponents(std::vector<std::weak_ptr<T>>& out) const {
        for (auto& com : _components) {
            auto ptr = std::dynamic_pointer_cast<T>(com);
            if (ptr) {
                out.push_back(ptr);
            } // if
        } // for
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const ComPtr& component);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="component"></param>
    void RemoveComponent(const ComPtr& component);
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    void End(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param);
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
    /// 作成
    /// </summary>
    /// <param name="builder"></param>
    void Construct(const std::shared_ptr<class IBuilder>& builder);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ACTOR_H