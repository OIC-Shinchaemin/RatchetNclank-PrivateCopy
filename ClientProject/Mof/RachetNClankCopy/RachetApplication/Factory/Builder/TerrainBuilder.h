#ifndef RATCHET_TERRAIN_BUILDER_H
#define RATCHET_TERRAIN_BUILDER_H


#include "ActorBuilder.h"

#include "../../Actor/Terrain/Terrain.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"


namespace ratchet {
class TerrainBuilder : public ratchet::ActorBuilder {
    using super = ratchet::ActorBuilder;
private:
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
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
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
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
#endif // !RATCHET_TERRAIN_BUILDER_H