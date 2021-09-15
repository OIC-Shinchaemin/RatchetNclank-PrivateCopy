#ifndef RATCHET_ACTOR_ACTOR_H
#define RATCHET_ACTOR_ACTOR_H


#include <optional>
#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "Base/Core/Define.h"
#include "Base/Core/Observable.h"
#include "ActorDefine.h"


namespace ratchet::component { class Component; }
namespace ratchet::factory::builder { class IBuilder; }
namespace ratchet::actor {
class Actor :
    public std::enable_shared_from_this<actor::Actor>,
    public ::base::core::Observable<const char*, const std::shared_ptr<actor::Actor>&> {
public:
    using ComPtr = std::shared_ptr<component::Component>;
    using ComArray = std::vector<ComPtr>;
    using Observable = base::core::Observable<const char*, const std::shared_ptr<actor::Actor>&>;
    struct Param {
        //! 名前
        std::string name;
        //! タグ
        std::string tag;
        //! トランスフォーム
        def::Transform transform;
        Param() :
            name("nameless"),
            tag("none"),
            transform() {
        }
        virtual ~Param() {
        }
    };
private:
    //! 状態
    ratchet::actor::ActorState _state;
    //! 名前
    std::string _name;
    //! タグ
    std::string _tag;
    //! トランスフォーム
    def::Transform _transform;
    //! トランスフォーム
    def::Transform _initial_transform;
    //! トランスフォーム
    std::optional<Mof::CMatrix44> _parent_transform;
    //! 機能
    ComArray _components;
    ComArray _input_components;
    ComArray _update_components;
    ComArray _render_components;
public:
    /// <summary>
    /// 状態変更
    /// </summary>
    virtual void Activate(void);
    /// <summary>
    /// 状態変更
    /// </summary>
    virtual void Sleep(void);
    /// <summary>
    /// 状態変更
    /// </summary>
    virtual void Pause(void);
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
    /// <param name="tag"></param>
    void SetTag(const char* tag);
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
    /// セッター
    /// </summary>
    /// <param name="transform"></param>
    void SetParentTransform(std::optional<Mof::CMatrix44> transform);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    actor::ActorState GetState(void) const;
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
    /// <returns>タグ</returns>
    std::string GetTag(void) const;
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
    Mof::CVector3 GetInitialPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::optional<Mof::CMatrix44> GetParentTransform(void) const;
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
    /// 描画判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InCameraRange(void) const;
    /// <summary>
    /// 視錐台内判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InFrustum(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const ComPtr& component);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name=""></param>
    void CloneToComponents(const ComArray& com_array);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="component"></param>
    void RemoveComponent(const ComPtr& component);
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(actor::Actor::Param* param);
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
    virtual void Construct(const std::shared_ptr<factory::builder::IBuilder>& builder);
};
}
#endif // !RATCHET_ACTOR_ACTOR_H