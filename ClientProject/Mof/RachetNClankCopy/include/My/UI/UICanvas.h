#ifndef MY_UI_CANVAS_H
#define MY_UI_CANVAS_H


#include <memory>
#include <vector>

#include "My/Core/Observer.h"
#include "My/Core/Observable.h"
#include "My/UI/UIPanel.h"


namespace my {
class UICanvas : public std::enable_shared_from_this<my::UICanvas>, public my::Observer<my::UIPanel>, public my::Observable<my::UICanvas> {
    using ElemPtr = std::shared_ptr<my::UIPanel>;
private:
    //! UIパネル
    std::vector<ElemPtr> _panels;
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
    virtual void OnNotify(const std::shared_ptr<my::UIPanel>& observable, const char* event) override;
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
#endif // !MY_UI_CANVAS_H