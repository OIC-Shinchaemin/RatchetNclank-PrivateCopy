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
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! 大きさ
    float _volume;
    //! 高さ
    float _height;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Character();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetSphere(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void);
};
}
#endif // !MY_CHARACTER_H