#ifndef MY_QUICK_CHANGE_SYSTEM_H
#define MY_QUICK_CHANGE_SYSTEM_H


#include "My/Core/Observable.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"
#include "../../ResourceManager.h"
#include "MY/UI/UICanvas.h"

#include "../../GameDefine.h"


namespace my {
class QuickChangeItem {
private:
    //! 位置
    Mof::CVector2 _position;
    //! 矩形
    Mof::CRectangle _rectangle;
    //! テクスチャ
    std::weak_ptr<Mof::CTexture> _texture;
    //! 所有
    std::string _weapon;
    //! リソース
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector2 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="rect"></param>
    void SetRectangle(Mof::CRectangle rect);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="name"></param>
    void SetWeapon(const char* name);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetWeapon(void) const;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(Mof::CVector4 color);
};
class QuickChangeSystem : public std::enable_shared_from_this<my::QuickChangeSystem>, public Observable<Mof::CVector4> {
    using Observable = my::Observable<Mof::CVector4>;
    enum class State {
        Enter,
        Exit
    };
private:
    //! 位置
    Mof::CVector2 _position;
    //! 色
    Mof::CVector4 _color;
    //! 状態
    State _state;
    //! アルファ
    float _alpha;
    //! 半径
    float _distance;
    //! 武器
    std::vector<int> _angles;
    //! 現在
    std::optional<float> _current_angle;
    //! アイテム
    std::unordered_map<int, my::QuickChangeItem> _items;
    //! パス
    std::unordered_map<std::string, std::string> _tex_names;
    //! 通知用
    my::Observable<const std::string&> _current;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! リソース
    std::weak_ptr<my::UICanvas> _ui_canvas;
    /// <summary>
    /// 開く
    /// </summary>
    /// <param name=""></param>
    void Open(void);
    /// <summary>
    /// 閉じる
    /// </summary>
    /// <param name=""></param>
    void Close(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    QuickChangeSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~QuickChangeSystem();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector4 GetColor(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddWeaponObserver(const std::shared_ptr<my::Observer<const std::string&>>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos, const std::shared_ptr<my::WeaponSystem>& weapon_system);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_QUICK_CHANGE_SYSTEM_H