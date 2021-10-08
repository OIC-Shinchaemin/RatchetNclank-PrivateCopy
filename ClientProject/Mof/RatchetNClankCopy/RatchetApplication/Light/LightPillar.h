#ifndef RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H
#define RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H


#include <Mof.h>


namespace ratchet::light {
struct Shader3DPrimitive {
    //! �V�F�[�_
    std::weak_ptr<Mof::CShader> shader;
    //! �o�C���_�[
    std::weak_ptr<Mof::CShaderBind_3DPrimitiveBase> bind;

    std::shared_ptr<Mof::CShader> GetShader(void) const {
        if (auto ptr = shader.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
    std::shared_ptr<Mof::CShaderBind_3DPrimitiveBase> GetBind(void) const {
        if (auto ptr = bind.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
};
struct cbLightPillarParam {
    Mof::Vector4 cblgPosition;
    Mof::Vector4 cblgDiffuse;
    Mof::Vector4 cblgAttenuation;
};
struct LightPillarCreateInfo {
    Mof::CVector3 position;
};

class LightPillar {
private:
    //! �L��
    bool _enable;
    //! �ʒu
    Mof::CVector3 _position;
    //! ������
    int _pillar_slice = 256;
    //! ���a
    float _pillar_radius = 2.0f;
    //! ����
    float _pillar_height = 200.0f;
    //! �W�I���g��
    Mof::LPGeometry _geometry;
    //! �V�F�[�_
    std::weak_ptr<ratchet::light::Shader3DPrimitive>  _primitive_shader;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LightPillar();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~LightPillar();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetPosition(const Mof::CVector3& value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetShader(const std::shared_ptr<ratchet::light::Shader3DPrimitive>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Disable(void);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H