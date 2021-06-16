#ifndef RATCHET_UI_UI_CREATOR_H
#define RATCHET_UI_UI_CREATOR_H


#include <memory>
#include <string>

#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace ratchet {
namespace ui {
template<typename UI>
class UICreator {
    // �t�@�N�g�����󂯎���template�������v��Ȃ��Ȃ�
private:
    //! ���O
    std::string _name;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<base::ui::UICanvas> GetUICanvas(void) const {
        if (auto ptr = _ui_canvas.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="ui"></param>
    void TryRemove(const std::shared_ptr<base::ui::UICanvas>& ui) {
        if (auto canvas = this->GetUICanvas()) {
            canvas->RemoveElement(_name.c_str());
        } // if
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="str"></param>
    UICreator(const char* str) :
        _name(str),
        _ui_canvas() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <param name=""></param>
    ~UICreator() {
        if (auto canvas = this->GetUICanvas()) {
            this->TryRemove(canvas);
        } // if
        _ui_canvas.reset();
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="ui"></param>
    /// <returns></returns>
    std::shared_ptr<UI> Create(const std::shared_ptr<base::ui::UICanvas>& ui, const std::shared_ptr<ratchet::ResourceMgr>& resource) {
        this->_ui_canvas = ui;

        std::shared_ptr<UI> menu;
        if constexpr (ty::has_func_release<UI>::value) {
            menu = ut::MakeSharedWithRelease<UI>(_name.c_str());
        } // if
        else {
            menu = std::make_shared <UI>(_name.c_str());
        } // else
        if (auto canvas = this->GetUICanvas()) {
            this->TryRemove(canvas);
            canvas->AddElement(menu);
        } // if
        if (resource) {
            menu->SetResourceManager(resource);
            menu->Initialize();
        } // if
        return  menu;
    }
};
}
}
#endif // !RATCHET_UI_UI_CREATOR_H