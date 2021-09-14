#ifndef RATCHET_COMPONENT_CHARACTER_COMPONENT_H
#define RATCHET_COMPONENT_CHARACTER_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>

#include "Base/Core/Observable.h"


namespace ratchet::component {
class CharacterComponent : public ::ratchet::component::UpdateComponent {
    using super = ::ratchet::component::UpdateComponent;
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_CHARACTER_COMPONENT_H