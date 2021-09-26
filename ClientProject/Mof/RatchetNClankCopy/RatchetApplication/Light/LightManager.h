#ifndef RATCHET_LIGHT_LIGHT_MANAGER_H
#define RATCHET_LIGHT_LIGHT_MANAGER_H


#include <memory>
#include <vector>

#include <Mof.h>

#include "LightPillar.h"


namespace ratchet::light {
class LightManager {
private:
    // ����
    Mof::CDirectionalLight _simple_light;
    //! ����
    std::vector<std::shared_ptr<ratchet::light::LightPillar>> _light_pillars;
    //! ����
    std::vector<std::shared_ptr<ratchet::light::LightPillar>> _light_pillars_delete_list;
    //! �V�F�[�_
    std::shared_ptr<Mof::CShader> _pillar_shader;
    //! �o�C���_�[
    std::shared_ptr<Mof::CShaderBind_3DPrimitiveBase> _pillar_bind;
    //! �V�F�[�_
    std::shared_ptr<ratchet::light::Shader3DPrimitive>  _pillar_primitive_shader;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LightManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~LightManager();
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="info"></param>
    /// <returns></returns>
    std::weak_ptr<ratchet::light::LightPillar> CreateLightPillar(const ratchet::light::LightPillarCreateInfo& info);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
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
#endif // !RATCHET_LIGHT_LIGHT_MANAGER_H