#ifndef MY_GAME_DEFINE_H
#define MY_GAME_DEFINE_H


#include <stdexcept>
#include <memory>
#include <string>

#include <Mof.h>

#include "My/Core/Math.h"
#include "MotionNames.h"
#include "ResourceManager.h"
#include "my/Core/FunctionPointerContainer.h"
#include "my/Resource/ResourceFont.h"
#include "My/UI/UICanvas.h"


#define DEBUG_PRINT(arg, ...)
#define TRACE
#if defined(_DEBUG)
#undef DEBUG_PRINT
#undef TRACE 
#define DEBUG_PRINT(arg, ...)\
{char str[256]; \
::sprintf_s(str, arg, __VA_ARGS__); \
::OutputDebugString(str);std::cout<<str;}
#define TRACE \
DEBUG_PRINT("%s %s %d \n", __FILE__, __func__, __LINE__);
#endif // defined (_DEBUG)


namespace my {

constexpr int kTextWidth= 12;

template<typename UI>
class UICreator {
private:
    //! –¼‘O
    std::string _name;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;

    std::shared_ptr<my::UICanvas> GetUICanvas(void) const {
        if (auto ptr = _ui_canvas.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
    void TryRemove(const std::shared_ptr<my::UICanvas>& ui) {
        if (auto canvas = this->GetUICanvas()) {
            canvas->RemoveElement(_name.c_str());
        } // if
    }
public:
    UICreator(const char* str) :
        _name(str),
        _ui_canvas() {
    }
    ~UICreator() {
        if (auto canvas = this->GetUICanvas()) {
            this->TryRemove(canvas);
        } // if
        _ui_canvas.reset();
    }

    std::shared_ptr<UI> Create(const std::shared_ptr<my::UICanvas>& ui) {
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
        } // sif
        return  menu;
    }
};


struct Transform {
    Mof::CVector3 position = math::vec3::kZero;
    Mof::CVector3 rotate = math::vec3::kZero;
    Mof::CVector3 scale = math::vec3::kOne;
};
using ResourceMgr = my::ResourceManager<
    std::shared_ptr<Mof::CTexture>,
    std::shared_ptr<Mof::CMeshContainer>,
    std::shared_ptr<my::MotionNames>,
    std::shared_ptr<sip::CResourceFont>
>;

struct cbUVScrollParam {
    Mof::Vector4 value;
    cbUVScrollParam& operator+=(Mof::CVector2 scroll) {
        value.x += scroll.x;
        value.y += scroll.y;
        return *this;
    }
};
}
#endif // !MY_GAME_DEFINE_H