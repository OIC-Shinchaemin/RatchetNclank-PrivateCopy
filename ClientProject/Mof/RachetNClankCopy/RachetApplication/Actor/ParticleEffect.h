#ifndef MY_PARTICLE_EFFECT_H
#define MY_PARTICLE_EFFECT_H


#include "../Actor.h"

#include <Mof.h>


namespace my {
class ParticleEffect : public my::Actor {
    using super = my::Actor;
public:
    struct Param : public super::Param {
        //! �F
        Mof::CVector4 color;
        //! ����
        float life_time;
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
    };
    struct EnvironmentParam {
        bool gravity;
    };
    struct Info {
        Param init_param;
        UpdateParam update_param;
        EnvironmentParam environment_param;
    };
private:
    //! �F
    Mof::CVector4 _color;
    //! ����
    float _life_time;
    //! �f�t�H���g�T�C�Y
    float _size;
    //! �X�V�p�����[�^
    my::ParticleEffect::UpdateParam _update_param;
    //! ���ݒ�
    my::ParticleEffect::EnvironmentParam _environment_param;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ParticleEffect();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ParticleEffect();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    virtual bool Render(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name="info"></param>
    void Start(const my::ParticleEffect::Info& info);
};
}
#endif // !MY_PARTICLE_EFFECT_H