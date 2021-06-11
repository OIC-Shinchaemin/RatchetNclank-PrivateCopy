#ifndef MY_GAME_SYSTEM_H
#define MY_GAME_SYSTEM_H


#include "Base/Core/Observable.h"

#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "WeaponSystem.h"
#include "Base/UI/UICanvas.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace my {
class GameSystem : public std::enable_shared_from_this<my::GameSystem>,
    public base::core::Observer<bool> {
    using this_type = my::GameSystem;
private:
    //! 通知用
    base::core::Observable<const std::shared_ptr<this_type>&> _subject;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::ResourceMgr> GetResource(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<base::ui::UICanvas> GetUICanvas(void) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameSystem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const std::shared_ptr<this_type>&>* GetSubject(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time);
};
}
#endif // !MY_GAME_SYSTEM_H