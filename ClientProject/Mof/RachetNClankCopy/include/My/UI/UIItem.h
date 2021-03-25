#ifndef MY_UI_ITEM_H
#define MY_UI_ITEM_H


#include "My/Core/Observable.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "My/Core/Define.h"

namespace my {
class UIEvent {
    using EventOwner = std::shared_ptr<class UIItem>;
    using OnEventFunc = std::function<bool(const EventOwner&)>;
private:
    //! 削除予定のイベントキー
    std::vector<std::string> _delete_keys;
    //! 決定イベント
    my::OnEvent<EventOwner > _on_enter;
    //! キャンセルイベント
    my::OnEvent<EventOwner > _on_cancel;
    //! 選択可能時イベント
    my::OnEvent<EventOwner > _on_cursor_in;
    //! 選択可能時
    my::OnEvent<EventOwner > _on_cursor_out;
protected:
public:
    bool OnEnter(const EventOwner& obj) {
        return _on_enter(obj);
    }
    bool OnCancel(const EventOwner& obj) {
        return _on_cancel(obj);
    }
    bool OnCursorIn(const EventOwner& obj) {
        return _on_cursor_in(obj);
    }
    bool OnCursorOut(const EventOwner& obj) {
        return _on_cursor_out(obj);
    }
public:
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void RegisterEnterEvent(const char* key, OnEventFunc func) {
        _on_enter.Register(key, func);
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void RegisterCancelEvent(const char* key, OnEventFunc func) {
        _on_cancel.Register(key, func);
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void RegisterCursorInEvent(const char* key, OnEventFunc func) {
        _on_cursor_in.Register(key, func);
    }
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="key"></param>
    /// <param name="func"></param>
    void RegisterCursorOutEvent(const char* key, OnEventFunc func) {
        _on_cursor_out.Register(key, func);
    }
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="key"></param>
    void RemoveMatchEvent(const char* key) {
        _on_enter.RemoveMatch(key);
        _on_cancel.RemoveMatch(key);
        _on_cursor_in.RemoveMatch(key);
        _on_cursor_out.RemoveMatch(key);
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="key"></param>
    void RemoveMatchDelay(const char* key) {
        _delete_keys.push_back(key);
    }
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool RemoveEventOnDeleteKey(void) {
        if (_delete_keys.empty()) {
            return false;
        } //if
        for (auto& str : _delete_keys) {
            this->RemoveMatchEvent(str.c_str());
        } //for
        _delete_keys.clear();
        return true;
    }
};
class UIItem : public my::UIEvent, public std::enable_shared_from_this<my::UIItem>, public my::Observable<UIItem> {
    using Event = my::UIEvent;
    /*
    enum class State {
        Default,
        CursorIn,
        Select,
        Enter,
        Active,
        CursorOut,
        Cancel,
        Exit,
        End
    };
    //! イベント
    std::unordered_map<State, std::function<bool(void)>> _event_func;
    //! 状態
    my::UIItem::State _state;
    */
protected:
    //! 名前
    std::string _name;
    //! 背景
    std::weak_ptr<Mof::CTexture> _texture;
    //! 位置
    Mof::CVector2 _position;
    //! 衝突
    Mof::CRectangle _rectangle;
    //! 色
    Mof::CVector4 _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    UIItem();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    UIItem(const std::string& name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~UIItem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="shared_this"></param>
    /// <param name="event"></param>
    void Notify(const std::shared_ptr<my::UIItem>& shared_this, const char* event);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetBlendColor(const Mof::CVector4 color);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CRectangle GetRectangle(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="tex"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) = 0;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) = 0;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) = 0;
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void);
};
}
#endif // !MY_UI_ITEM_H