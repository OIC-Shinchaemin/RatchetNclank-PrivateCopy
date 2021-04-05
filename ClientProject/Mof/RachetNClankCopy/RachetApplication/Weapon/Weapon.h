#ifndef MY_WEAPON_H
#define MY_WEAPON_H


#include "../Actor.h"
#include "../ResourceLocator.h"

#include <memory>

#include <Mof.h>


namespace my {
class Weapon : public my::Actor , public my::ResourceLocator{
    using super = my::Actor;
protected:
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Weapon();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Weapon();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    virtual bool Render(Mof::LPBONEMOTIONSTATE bone_state);
};
}
#endif // !MY_WEAPON_H