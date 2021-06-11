#ifndef RACHET_HELP_DESK_H
#define RACHET_HELP_DESK_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "GameQuest.h"


namespace rachet {
class HelpDesk :
    public std::enable_shared_from_this<rachet::HelpDesk>,
    public base::core::Observer<const rachet::GameQuest&> {
public:
    struct Info {
        std::string text;
    };
private:
    //! 情報
    Info _info;
    //! 情報
    Info _prev_info;
    //! 達成したいこと
    //rachet::GameQuest _current_quest;
    //! 通知用
    base::core::Observable<const rachet::HelpDesk::Info&> _subject;
    //! リソース
    std::weak_ptr<rachet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    HelpDesk();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~HelpDesk();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const rachet::GameQuest& quest) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RACHET_HELP_DESK_H