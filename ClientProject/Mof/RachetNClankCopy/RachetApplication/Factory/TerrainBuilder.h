#ifndef MY_TERRAIN_BUILDER_H
#define MY_TERRAIN_BUILDER_H


#include "ActorBuilder.h"

#include "../Actor/Terrain/Terrain.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace my {
class TerrainBuilder : public my::ActorBuilder {
    using super = my::ActorBuilder;
private:
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
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
#endif // !MY_TERRAIN_BUILDER_H