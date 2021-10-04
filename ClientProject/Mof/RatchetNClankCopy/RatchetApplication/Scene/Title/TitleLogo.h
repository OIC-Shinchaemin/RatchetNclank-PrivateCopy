#ifndef RATCHET_SCENE_TITLE_TITLE_LOGO_H
#define RATCHET_SCENE_TITLE_TITLE_LOGO_H


#include <memory>

#include <Mof.h>


namespace ratchet::scene::title {
class TitleLogo {
private:
    //! �ʒu
    Mof::CVector2 _position;
    //! Y�f�t�H���g�ʒu
    float _default_position_y;
    //! �ʒu
    Mof::CVector2 _position_offset;
    //! �e�N�X�`��
    std::weak_ptr<Mof::CTexture> _texture;
    //! �\��
    bool _show;
    //! �\��
    base::core::Timer _show_timer;
    //! �A���t�@�l
    float _alpha;
    //! �A���t�@�l�ő�l
    float _alpha_max;
    //! �A���t�@�l����
    float _alpha_increments;
    //! �\���g�嗦
    float _scale;
public:
    TitleLogo() :
        _position(),
        _default_position_y(250.0f),
        _position_offset(Mof::CVector2(-10.0f, 0.0f)),
        _texture(),
        _show(false),
        _show_timer(),
        _alpha(0.0f),
        _alpha_max(1.0f),
        _alpha_increments(0.03f),
        _scale(0.8f) {
        _show_timer.Initialize(0.8f, false);
    }
    ~TitleLogo() {
        _show = false;
    }

    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
        auto center = Mof::CVector2(::g_pFramework->GetWindow()->GetWidth() * 0.5f, ::g_pFramework->GetWindow()->GetHeight() * 0.5f);
        this->_texture = ptr;
        auto size = Mof::CVector2(ptr->GetWidth(), ptr->GetHeight()) * _scale;
        auto half_size = size * 0.5f;

        _position = Mof::CVector2(center.x - half_size.x, _default_position_y) + _position_offset;
    }
    bool Update(float delta_time) {
        if (_show_timer.Tick(delta_time)) {
            _show = true;
        } // if

        if (_show) {
            _alpha = std::clamp(_alpha + _alpha_increments, 0.0f, _alpha_max);
        } // if
        return true;
    }
    bool Render(void) {
        if (!_show) {
            return false;
        } // if
        if (auto tex = _texture.lock()) {
            auto color = Mof::CVector4(1.0f, 1.0f, 1.0f, _alpha).ToU32Color();
            tex->RenderScale(_position.x, _position.y, _scale, color, Mof::TextureAlignment::TEXALIGN_BOTTOMLEFT);
        } // if
        return true;
    }
};
}
#endif // !RATCHET_SCENE_TITLE_TITLE_LOGO_H