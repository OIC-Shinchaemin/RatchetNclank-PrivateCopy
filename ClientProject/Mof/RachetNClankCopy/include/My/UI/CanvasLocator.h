#ifndef MY_CANVAS_INTERFACE_H
#define MY_CANVAS_INTERFACE_H


#include "My/Core/ServiceLocator.h"

#include <memory>
#include <string>


namespace my {
class CanvasLocator : public my::ServiceLocator<class UICanvas> {
    using super = my::ServiceLocator<class UICanvas>;
    using ElemPtr = std::shared_ptr<class UIPanel>;
private:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class UICanvas> GetService(void) const = delete;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CanvasLocator();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CanvasLocator();
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
};
}
#endif // !MY_CANVAS_INTERFACE_H