#ifndef MY_CHARACTER_COMPONENT_H
#define MY_CHARACTER_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>

#include "My/Core/Observable.h"


namespace my {
class CharacterComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
protected:
    //! 大きさ
    float _volume;
    //! 高さ
    float _height;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    CharacterComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    CharacterComponent(const CharacterComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CharacterComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
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
    float GetVolume(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetHeight(void) const;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_CHARACTER_COMPONENT_H