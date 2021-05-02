#ifndef MY_BOMB_GLOVE_BULLET_COMPONENT_H
#define MY_BOMB_GLOVE_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "../Collision/Object/CollisionComponent.h"


namespace my {
class BombGloveBulletComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool CollisionEnemy(const my::CollisionInfo& in);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BombGloveBulletComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BombGloveBulletComponent(const BombGloveBulletComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGloveBulletComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_BOMB_GLOVE_BULLET_COMPONENT_H