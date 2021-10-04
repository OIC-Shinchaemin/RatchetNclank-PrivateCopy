#ifndef RATCHET_SCENE_LOADING_ANIMATION_H
#define RATCHET_SCENE_LOADING_ANIMATION_H


#include "Base/Core/Timer.h"
#include <Mof.h>


namespace ratchet::scene::loading {
class LoadingAnimationBase {
public:
    LoadingAnimationBase() {
    }
    virtual ~LoadingAnimationBase() {
    }
    virtual bool Update(float delta_time) {
        return true;
    }
    virtual bool Render(void) {
        return true;
    }
};
class LoadingDotAnimation : public LoadingAnimationBase {
    using super = LoadingAnimationBase;
private:
    //! カウンター
    base::core::Timer _loading_counter;
    //! カウンター
    int _loading_dot_count;
    //! 経過時間 / 所要時間
    float _loading_progress;
public:
    LoadingDotAnimation() :
        super(),
        _loading_counter(),
        _loading_dot_count(0),
        _loading_progress() {
        _loading_counter.Initialize(1.0f, true);
    }
    virtual ~LoadingDotAnimation() {
    }
    virtual bool Update(float delta_time) override {
        if (_loading_counter.Tick(delta_time)) {
            _loading_dot_count++;
            int count_max = 4;
            _loading_dot_count = std::clamp(_loading_dot_count, 0, count_max);
            if (_loading_dot_count == count_max) {
                _loading_dot_count = 0;
            } // if
        } // if
        return true;
    }
    virtual bool Render(void) override {
        auto text = std::string("Now Loading");
        for (int i = 0; i < _loading_dot_count; i++) {
            text += ".";
        } // for
        ::CGraphicsUtilities::RenderString(800.0f, 700.0f, def::color_rgba_u32::kWhite, text.c_str());
        return true;
    }
};
}
#endif // !RATCHET_SCENE_LOADING_ANIMATION_H