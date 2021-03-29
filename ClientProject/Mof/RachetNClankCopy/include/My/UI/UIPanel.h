#ifndef MY_UI_PANEL_H
#define MY_UI_PANEL_H


#include "My/Core/Observer.h"
#include "My/Core/Observable.h"

#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "UIItem.h"


namespace my {
class UIPanel : public std::enable_shared_from_this<my::UIPanel> , public my::Observer<my::UIItem>, public my::Observable<my::UIPanel> {
public:
    using ElemPtr = std::shared_ptr<my::UIItem>;
protected:
    //! 名前
    std::string _name;
    //! 位置
    Mof::CVector2 _position;
    //! 要素
    std::vector<ElemPtr> _items;
    //! 背景
    std::weak_ptr<Mof::CTexture>_texture;
    //! 色
    Mof::CVector4 _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    UIPanel(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual~UIPanel();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="observable"></param>
    /// <param name="event"></param>
    virtual void OnNotify(const std::shared_ptr<my::UIItem>& observable, const char* event) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector2 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="color"></param>
    void SetColor(Mof::CVector4 color);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector2 GetPosition(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="elem"></param>
    void AddElement(const ElemPtr& elem);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="elem"></param>
    void RemoveElement(const ElemPtr& elem);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
};
}
#endif // !MY_UI_PANEL_H