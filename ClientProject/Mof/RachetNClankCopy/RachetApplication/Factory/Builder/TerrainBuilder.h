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
    //! リソース
    std::weak_ptr<rachet::ResourceMgr> _resource;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TerrainBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TerrainBuilder();    
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !RACHET_TERRAIN_BUILDER_H