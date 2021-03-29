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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class UICanvas> GetService(void) const = delete;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CanvasLocator();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CanvasLocator();
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="elem"></param>
    void AddElement(const ElemPtr& elem);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="elem"></param>
    void RemoveElement(const ElemPtr& elem);
};
}
#endif // !MY_CANVAS_INTERFACE_H