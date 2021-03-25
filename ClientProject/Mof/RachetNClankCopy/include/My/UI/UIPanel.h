#ifndef MY_UI_PANEL_H
#define MY_UI_PANEL_H


#include "My/Core/Observer.h"
#include "My/Core/Observable.h"

#include <memory>
#include <vector>

#include <Mof.h>

#include "UIItem.h"


namespace my {
class UIPanel : public std::enable_shared_from_this<my::UIPanel> , public my::Observer<my::UIItem>, public my::Observable<my::UIPanel> {
public:
    using ElemPtr = std::shared_ptr<my::UIItem>;
protected:
    //! �w�i
    std::weak_ptr<Mof::CTexture>_background;
    //! �v�f
    std::vector<ElemPtr> _items;
    //! �ʒu
    Mof::CVector2 _position;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    UIPanel();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual~UIPanel();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="observable"></param>
    /// <param name="event"></param>
    virtual void OnNotify(const std::shared_ptr<my::UIItem>& observable, const char* event) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector2 GetPosition(void) const;
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
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    virtual bool Initialize(Mof::CVector2 pos);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
};
}
#endif // !MY_UI_PANEL_H