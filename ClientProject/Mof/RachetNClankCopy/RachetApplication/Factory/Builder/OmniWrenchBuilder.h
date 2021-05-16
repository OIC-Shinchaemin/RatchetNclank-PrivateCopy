#ifndef MY_OMNI_WRENCH_BUILDER_H
#define MY_OMNI_WRENCH_BUILDER_H


#include "ActorBuilder.h"

#include "../../Actor/Weapon/OmniWrench.h"
//#include "../ResourceManager.h"
//#include "../GameDefine.h"


namespace my {
class OmniWrenchBuilder : public my::ActorBuilder {
    using super = my::ActorBuilder;
private:
    //! ���\�[�X
    //std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    OmniWrenchBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~OmniWrenchBuilder();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    //void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !MY_OMNI_WRENCH_BUILDER_H