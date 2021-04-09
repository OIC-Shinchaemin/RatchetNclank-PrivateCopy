#ifndef MY_COMPONENT_H
#define MY_COMPONENT_H


#include <memory>

#include "rapidjson/document.h"

#include "../Actor.h"


namespace my {
class Component : public std::enable_shared_from_this<my::Component> {
private:
    //! この機能の所有者
    std::weak_ptr<my::Actor> _owner;
protected:
    //! 小さいほど処理される順番が早い
    int _priority;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority">優先度</param>
    Component(int priority);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Component();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetOwner(const std::shared_ptr<my::Actor>& ptr);
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
    std::shared_ptr<my::Actor> GetOwner(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetPriority(void) const;
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
    virtual std::shared_ptr<my::Component> Clone(void) = 0;
};
static bool operator<(const my::Component& a, const my::Component& b) noexcept {
    return a.GetPriority() < b.GetPriority();
}
static bool operator<(const std::shared_ptr<my::Component>& a, const std::shared_ptr < my::Component>& b) noexcept {
    return a->GetPriority() < b->GetPriority();
}
}
#endif // !MY_COMPONENT_H