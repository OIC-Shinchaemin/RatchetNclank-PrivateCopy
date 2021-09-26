#ifndef RATCHET_LIGHT_LIGHT_MANAGER_H
#define RATCHET_LIGHT_LIGHT_MANAGER_H


#include <memory>
#include <vector>

#include <Mof.h>

#include "LightPillar.h"


namespace ratchet::light {
class LightManager {
private:
    // 光源
    Mof::CDirectionalLight _simple_light;
    //! 光柱
    std::vector<std::shared_ptr<ratchet::light::LightPillar>> _light_pillars;
    //! 光柱
    std::vector<std::shared_ptr<ratchet::light::LightPillar>> _light_pillars_delete_list;
    //! シェーダ
    std::shared_ptr<Mof::CShader> _pillar_shader;
    //! バインダー
    std::shared_ptr<Mof::CShaderBind_3DPrimitiveBase> _pillar_bind;
    //! シェーダ
    std::shared_ptr<ratchet::light::Shader3DPrimitive>  _pillar_primitive_shader;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LightManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LightManager();
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="info"></param>
    /// <returns></returns>
    std::weak_ptr<ratchet::light::LightPillar> CreateLightPillar(const ratchet::light::LightPillarCreateInfo& info);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_LIGHT_LIGHT_MANAGER_H