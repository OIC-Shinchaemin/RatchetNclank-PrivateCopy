#ifndef MY_HELP_DESK_H
#define MY_HELP_DESK_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "GameQuest.h"


namespace my {
class HelpDesk :
    public std::enable_shared_from_this<my::HelpDesk>,
    public my::Observer<const my::GameQuest&> {
public:
    struct Info {
        std::string text;
    };
private:
    //! 達成したいこと
    //my::GameQuest _current_quest;
    //! 通知用
    my::Observable<const my::HelpDesk::Info&> _subject;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    virtual void OnNotify(const my::GameQuest& quest) override;
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
#endif // !MY_HELP_DESK_H