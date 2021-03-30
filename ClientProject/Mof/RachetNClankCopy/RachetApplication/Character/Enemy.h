#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include "../SightRecognition.h"


namespace my {
class Enemy : public my::Character {
    using super = my::Character;
private:
    //! 標的
    std::weak_ptr<my::Character>_target;
    //std::vector< std::weak_ptr<my::Character>>_recognized;
    //! 視覚
    my::SightRecognition _sight;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color );
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
    virtual bool Render(void) override;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
};
}
#endif // !MY_ENEMY_H