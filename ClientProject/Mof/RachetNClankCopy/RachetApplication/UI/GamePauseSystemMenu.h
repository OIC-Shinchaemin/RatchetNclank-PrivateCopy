#ifndef MY_GAME_PAUSE_SYSTEM_MENU_H
#define MY_GAME_PAUSE_SYSTEM_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <memory>

#include "My/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/GamePauseSystem.h"


namespace my {
class GamePauseSystemMenu : public my::UIPanel,
    public my::Observer<const my::GamePauseSystem::Info&> {
    using super = my::UIPanel;
private:
    //! 情報
    my::GamePauseSystem::Info _infomation;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    GamePauseSystemMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::GamePauseSystem::Info& info) override;
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
    /// 追加
    /// </summary>
    /// <param name="in"></param>
    //void AddItem(const my::OptionSystemItem& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
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
    virtual bool Render(void) override;
};
}
#endif // !MY_GAME_PAUSE_SYSTEM_MENU_H