#ifndef RATCHET_HELP_DESK_H
#define RATCHET_HELP_DESK_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "GameQuest.h"


namespace ratchet {
class HelpDesk :
    public std::enable_shared_from_this<ratchet::HelpDesk>,
    public base::core::Observer<const ratchet::GameQuest&> {
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
    //ratchet::GameQuest _current_quest;
    //! 通知用
    base::core::Observable<const ratchet::HelpDesk::Info&> _subject;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
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
    virtual void OnNotify(const ratchet::GameQuest& quest) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
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
#endif // !RATCHET_HELP_DESK_H