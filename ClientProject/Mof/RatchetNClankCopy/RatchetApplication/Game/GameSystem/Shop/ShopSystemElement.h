#ifndef RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H
#define RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H


#include "Base/UI/UICanvas.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"


namespace ratchet {
namespace game {
namespace gamesystem {
namespace shop {
class ShopSystemElement {
private:
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ShopSystemElement();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ShopSystemElement();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
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
    virtual bool Update(void);
};
}
}
}
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H