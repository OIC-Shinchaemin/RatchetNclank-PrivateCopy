#ifndef RATCHET_SCENE_DESCRIPTION_SCENE_H
#define RATCHET_SCENE_DESCRIPTION_SCENE_H


#include "Scene.h"
#include "../GameDefine.h"


namespace ratchet::scene {
class GameDescription {
private:
    //! 表示
    bool _show = false;
    //! 位置
    Mof::CVector2 _title_position = Mof::CVector2(400.0, 100.0f);
    //! 位置
    Mof::CVector2 _desc_position = Mof::CVector2(130.0, 240.0f);
    //! 位置
    Mof::CVector2 _back_position = Mof::CVector2(460.0, 700.0f);
    //! テキスト
    std::string _title_text = "ゲームの操作説明";
    //! テキスト
    std::string _desc_text = " ◆ Escape(Esc)キーでゲーム終了\n\n \
◆ Nキーで攻撃\n\n \
◆ Jキーでジャンプ\n\n \
◆ Shiftキーで変更\n\n \
◆ Vキーで武器が選択されていれば武器使用\n\n \
◆ WASDキーで移動\n\n \
◆ 十字キーでカメラ移動\n\n \
◆ Qキーでカメラ補正\n";
    //! テキスト
    std::string _back_text = "Escape(Esc)キーで戻る";
public:
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsShow(void) const {
        return this->_show ;
    }
    void Show(void) {
        this->_show = true;
    }
    void Hide(void) {
        this->_show = false;
    }
    void Render(const Mof::CVector2& position, const std::string& text) {
        ::CGraphicsUtilities::RenderString(position.x, position.y, text.c_str());
    }
    void Render(std::shared_ptr<ratchet::ResourceMgr> r) {
        this->Render(_title_position, _title_text);
        this->Render(_desc_position, _desc_text);
        this->Render(_back_position, _back_text);
    }
};
class DescriptionScene : public ratchet::scene::Scene {
    using super = ratchet::scene::Scene;
protected:
/// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool SceneUpdate(float delta_time) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool LoadingUpdate(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DescriptionScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~DescriptionScene();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<super::Param> param) override;
};
}
#endif // !RATCHET_SCENE_DESCRIPTION_SCENE_H