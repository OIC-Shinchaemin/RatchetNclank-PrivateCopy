#ifndef RATCHET_EFFECT_EFFECT_H
#define RATCHET_EFFECT_EFFECT_H


#include <Mof.h>

#include <memory>

#include "../GameDefine.h"
#include "EffectDefine.h"
#include "Base/Core/Timer.h"


namespace ratchet::effect {
class Effect {
public:
    struct EnvironmentParam {
        bool use_gravity;
        float gravity_scale;
        bool use_velocity_drag;
        float velocity_drag;
    };
    struct UpdateParam {
        //! �ʒu
        Mof::CVector3 velocity;
        //! ��]
        Mof::CVector3 rotate;
        //! �g��
        Mof::CVector3 scale;
        //! ���Z�F
        Mof::CVector4 color;

        UpdateParam& operator+=(const ratchet::effect::Effect::EnvironmentParam& environment) {
            if (environment.use_velocity_drag) {
                velocity *= environment.velocity_drag;
            } // if
            return *this;
        }
    };
    struct BasicParam {
        ratchet::effect::EffectType type;
        //! �g�����X�t�H�[��
        def::Transform transform;
        //! �F
        Mof::CVector4 color;
        //! ���݊���
        float life_duration;

        BasicParam& operator+=(const ratchet::effect::Effect::UpdateParam& update) {
            this->transform.position += update.velocity;
            this->transform.rotate += update.rotate;
            this->transform.scale += update.scale;

            auto min_clamp = [](float& v, float min = 0.0f) { if (v < min) { v = min; } // if 
            };
            min_clamp(transform.scale.x);
            min_clamp(transform.scale.y);
            min_clamp(transform.scale.z);
            this->color += update.color;
            return *this;
        }
        BasicParam& operator+=(const ratchet::effect::Effect::EnvironmentParam& environment) {
            if (environment.use_gravity) {
                this->transform.position.y -= environment.gravity_scale;
            } // if
            return *this;
        }
    };
    struct Info {
        BasicParam init_param;
        UpdateParam update_param;
        EnvironmentParam environment_param;
    };
private:
    //! �L��
    bool _enable;
    //! ����
    base::core::Timer _life_timer;
    //! �������p�����[�^
    std::optional<BasicParam> _initialize_param;
    //! ��{�p�����[�^
    BasicParam _basic_param;
    //! �X�V�p�����[�^
    ratchet::effect::Effect::UpdateParam _update_param;
    //! ���p�����[�^
    ratchet::effect::Effect::EnvironmentParam _environment_param;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Effect();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Effect();
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const ratchet::effect::Effect::BasicParam& GetBasicParam(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    bool Render(void);
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name="info"></param>
    void Start(const ratchet::effect::Effect::Info& info);
};
}
#endif // !RATCHET_EFFECT_EFFECT_H