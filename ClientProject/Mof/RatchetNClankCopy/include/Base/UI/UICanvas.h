#ifndef BASE_UI_UI_CANVAS_H
#define BASE_UI_UI_CANVAS_H


#include <memory>
#include <vector>

#include "../Core/Observer.h"
#include "../Core/Observable.h"
#include "UIPanel.h"


namespace base {
namespace ui {
class UICanvas : public std::enable_shared_from_this<base::ui::UICanvas>,
    public core::Observer<const std::shared_ptr<base::ui::UIPanel>&, const char* > {
    using ElemPtr = std::shared_ptr<base::ui::UIPanel>;
private:
    //! UIパネル
    std::vector<ElemPtr> _panels;
    //! UIパネル
    std::vector<ElemPtr> _enable_list;
    //! UIパネル
    std::vector<ElemPtr> _disable_list;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    UICanvas();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~UICanvas();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="observable"></param>
    /// <param name="event"></param>
    virtual void OnNotify(const std::shared_ptr<base::ui::UIPanel>& ptr, const char* event) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    ElemPtr GetElement(const std::string& name) const;
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
    /// 削除
    /// </summary>
    /// <param name="name"></param>
    bool RemoveElement(const std::string& name);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
};
}
}
#endif // !BASE_UI_UI_CANVAS_H