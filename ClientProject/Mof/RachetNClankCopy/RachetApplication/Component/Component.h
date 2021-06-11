#ifndef RATCHET_COMPONENT_H
#define RATCHET_COMPONENT_H


#include <memory>

#include "rapidjson/document.h"

#include "../Actor.h"

#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/UI/UICanvas.h"


namespace ratchet {
class Component : public std::enable_shared_from_this<ratchet::Component> {
private:
    //! この機能の所有者
    std::weak_ptr<ratchet::Actor> _owner;
    //! 小さいほど処理される順番が早い
    int _priority;
    //! 有効
    bool _active;
protected:
    //! リソース
    static std::weak_ptr<ratchet::ResourceMgr> _resource_manager;
    //! リソース
    static std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    static void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    static void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority">優先度</param>
    Component(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    Component(const Component& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Component();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetOwner(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> GetOwner(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetPriority(void) const;
    /// <summary>
    /// 有効判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// 入力判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsInput(void) const;
    /// <summary>
    /// 更新判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsUpdate(void) const;
    /// <summary>
    /// 描画判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsRender(void) const;
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Activate(void);
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Inactivate(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
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
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) = 0;
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void);
#endif // _DEBUG
};
static bool operator<(const ratchet::Component& a, const ratchet::Component& b) noexcept {
    return a.GetPriority() < b.GetPriority();
}
static bool operator<(const std::shared_ptr<ratchet::Component>& a, const std::shared_ptr < ratchet::Component>& b) noexcept {
    return a->GetPriority() < b->GetPriority();
}
}
#endif // !RATCHET_COMPONENT_H