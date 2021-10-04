#ifndef RATCHET_SCENE_DESCRIPTION_SCENE_H
#define RATCHET_SCENE_DESCRIPTION_SCENE_H


#include "Scene.h"


namespace ratchet::scene {
class GameDescription {
private:
public:
    void Render(std::shared_ptr<ratchet::ResourceMgr> r) {
        auto font = r->Get<std::shared_ptr<sip::CResourceFont>>("../Resource/font/kkm_analogtv.ttf\\KKM-アナログテレビフォント");

        const char* text;

        text = "ゲームの操作説明";
        ::CGraphicsUtilities::RenderString(400.0, 100.0f, text);

        text = " ◆ ESCAPEキーでゲーム終了\n\n \
◆ Nキーで攻撃\n\n \
◆ Jキーでジャンプ\n\n \
◆ Shiftキーで変更 武器選択はShift長押しで0~8キー\n\n \
◆ Vキーで武器が選択されていれば武器使用\n\n \
◆ WASDキーで移動\n\n \
◆ 十字キーでカメラ移動\n\n \
◆ Qキーでカメラ補正\n";
        ::CGraphicsUtilities::RenderString(130.0 + 1, 240.0f + 1, def::color_rgba_u32::kBlue, text);
        ::CGraphicsUtilities::RenderString(130.0, 240.0f, text);

        text = "Startボタン・Shiftキーで戻る";
        ::CGraphicsUtilities::RenderString(460.0, 700.0f, text);
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