#ifndef MY_UI_ITEM_H
#define MY_UI_ITEM_H


#include "My/Core/Observable.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "My/Core/Define.h"

namespace my {
class UIItem : public std::enable_shared_from_this<my::UIItem>, public my::Observable<const std::shared_ptr<my::UIItem>&, const char* > {
protected:
    //! ���O
    std::string _name;
    //! �ʒu
    Mof::CVector2 _position;
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �F
    Mof::CVector4 _color;
    //! �Փ�
    Mof::CRectangle _rectangle;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    UIItem(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~UIItem();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    void SetColor(const Mof::CVector4 color);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CRectangle GetRectangle(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="tex"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    bool Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) = 0;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) = 0;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) = 0;
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void);
};
}
#endif // !MY_UI_ITEM_H