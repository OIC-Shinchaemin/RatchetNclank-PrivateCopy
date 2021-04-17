#ifndef MY_SIGHT_RECOGNITION_COMPONENT_H
#define MY_SIGHT_RECOGNITION_COMPONENT_H


#include "Component.h"


namespace my {
class SightRecognitionComponent : public my::Component {
    using super = my::Component;
private:
    //! 視野
    float _range;
    //! キャラ
    std::weak_ptr<class EnemyComponent> _enemy_com;

    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority">優先度</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SightRecognitionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 target);
#ifdef _DEBUG
    virtual bool IsRender(void) const override {
        return true;
    }
    virtual bool Render(void) override;
#endif // _DEBUG
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_SIGHT_RECOGNITION_COMPONENT_H