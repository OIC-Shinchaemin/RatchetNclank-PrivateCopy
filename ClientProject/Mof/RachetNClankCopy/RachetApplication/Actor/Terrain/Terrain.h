#ifndef MY_TERRAIN_H
#define MY_TERRAIN_H


#include "../../Actor.h"
#include "../../GameDefine.h"
#include "../../ResourceManager.h"


namespace my {
class Terrain : public my::Actor {
    using super = my::Actor;
private:
    //! ����
    Mof::LPGeometry _plane;
    //! �X�N���[��
    my::cbUVScrollParam _uv_scroll;
    //! �X�N���[��
    Mof::CVector2 _scroll_increase;
    //�V�F�[�_�[
    Mof::CShader _shader;
    Mof::CShaderBind_3DPrimitiveBase _shader_bind;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
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
#endif // !MY_TERRAIN_H