#ifndef RATCHET_ACTOR_TERRAIN_TERRAIN_H
#define RATCHET_ACTOR_TERRAIN_TERRAIN_H


#include "../Actor.h"

#include "../../GameDefine.h"
#include "../../ResourceManager.h"


namespace ratchet {
namespace actor {
namespace terrain {
class Terrain : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
private:
    //! ����
    Mof::LPGeometry _plane;
    //! �X�N���[��
    ratchet::cbUVScrollParam _uv_scroll;
    //! �X�N���[��
    Mof::CVector2 _scroll_increase;
    //�V�F�[�_�[
    Mof::CShader _shader;
    Mof::CShaderBind_3DPrimitiveBase _shader_bind;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Terrain();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Terrain();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
}
}
#endif // !RATCHET_ACTOR_TERRAIN_TERRAIN_H