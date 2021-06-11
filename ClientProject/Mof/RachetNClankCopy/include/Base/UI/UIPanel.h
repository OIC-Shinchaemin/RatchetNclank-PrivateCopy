#ifndef BASE_UI_UI_PANEL_H
#define BASE_UI_UI_PANEL_H


#include "../Core/Observer.h"
#include "../Core/Observable.h"

#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "UIItem.h"


namespace base {
namespace ui {
class UIPanel : public std::enable_shared_from_this<base::ui::UIPanel>, public base::core::Observer<const std::shared_ptr<base::ui::UIItem>&, const char* >, public base::core::Observable<const std::shared_ptr<base::ui::UIPanel>&, const char* > {
public:
    using ElemPtr = std::shared_ptr<base::ui::UIItem>;
protected:
    //! ���O
    std::string _name;
    //! �ʒu
    Mof::CVector2 _position;
    //! �v�f
    std::vector<ElemPtr> _items;
    //! �w�i
    std::weak_ptr<Mof::CTexture>_texture;
    //! �F
    Mof::CVector4 _color;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    UIPanel(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual~UIPanel();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="observable"></param>
    /// <param name="event"></param>
    virtual void OnNotify(const std::shared_ptr<base::ui::UIItem>& observable, const char* event) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector2 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="color"></param>
    void SetColor(Mof::CVector4 color);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetName(void) const;
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
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    [[nodiscard]] virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
};
}
}
#endif // !BASE_UI_UI_PANEL_H