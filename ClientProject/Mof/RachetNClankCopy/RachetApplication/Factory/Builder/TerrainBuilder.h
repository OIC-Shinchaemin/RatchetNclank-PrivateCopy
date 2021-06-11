#ifndef RACHET_TERRAIN_BUILDER_H
#define RACHET_TERRAIN_BUILDER_H


#include "ActorBuilder.h"

#include "../../Actor/Terrain/Terrain.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace rachet {
class TerrainBuilder : public rachet::ActorBuilder {
    using super = rachet::ActorBuilder;
private:
    //! ���\�[�X
    std::weak_ptr<rachet::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TerrainBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TerrainBuilder();    
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
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
#endif // !RACHET_TERRAIN_BUILDER_H