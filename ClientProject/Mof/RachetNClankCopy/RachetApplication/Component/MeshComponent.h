#ifndef MY_MESH_COMPONENT_H
#define MY_MESH_COMPONENT_H


#include "RenderComponent.h"

#include <vector>
#include <memory>


namespace my {
class MeshComponent : public my::RenderComponent {
    using super = my::RenderComponent;
private:
    //! ���b�V��
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! �A�j���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ��\���t���O
    bool _is_show;
    //! �\���F
    Mof::CVector4 _color;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    MeshComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    MeshComponent(const MeshComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MeshComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="mesh"></param>
    void SetMesh(const std::shared_ptr<Mof::CMeshContainer>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::weak_ptr<Mof::CMeshContainer> GetMesh(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
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
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// �\�����Ȃ�
    /// </summary>
    /// <param name=""></param>
    void Hide(void);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
};
}
#endif // !MY_MESH_COMPONENT_H