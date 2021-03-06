#ifndef BASE_UI_UI_ITEM_H
#define BASE_UI_UI_ITEM_H


#include "../Core/Observable.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "../Core/Define.h"


namespace base {
namespace ui {
class UIItem : 
    public std::enable_shared_from_this<base::ui::UIItem>,
    public core::Observable<const std::shared_ptr<base::ui::UIItem>&, const char* > {
protected:
    //! 名前
    std::string _name;
    //! 位置
    Mof::CVector2 _position;
    //! テクスチャ
    std::weak_ptr<Mof::CTexture> _texture;
    //! 色
    Mof::CVector4 _color;
    //! 衝突
    Mof::CRectangle _rectangle;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    UIItem(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~UIItem();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Mof::CVector2 position);
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
    void SetColor(const Mof::CVector4 color);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector2 GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector2 GetSize(void) const;
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
}
#endif // !BASE_UI_UI_ITEM_H