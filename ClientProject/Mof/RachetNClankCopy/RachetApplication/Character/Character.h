#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H


#include "../Actor.h"
#include "../ResourceLocator.h"

#include <memory>

#include <Mof.h>

#include "../GameDefine.h"


namespace my {
class Character : public my::Actor, public my::ResourceLocator {
    using super = my::Actor;
protected:
    //! ���b�V��
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! �傫��
    float _volume;
    //! ����
    float _height;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Character();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void);
};
}
#endif // !MY_CHARACTER_H