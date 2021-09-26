#ifndef RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H
#define RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H


#include <Mof.h>


namespace ratchet::light {
struct Shader3DPrimitive {
    //! シェーダ
    std::weak_ptr<Mof::CShader> shader;
    //! バインダー
    std::weak_ptr<Mof::CShaderBind_3DPrimitiveBase> bind;

    std::shared_ptr<Mof::CShader> GetShader(void) const {
        if (auto ptr = shader.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
    std::shared_ptr<Mof::CShaderBind_3DPrimitiveBase> GetBind(void) const {
        if (auto ptr = bind.lock()) {
            return ptr;
        } // if
        return nullptr;
    }
};
struct cbLightPillarParam {
    Mof::Vector4 cblgPosition;
    Mof::Vector4 cblgDiffuse;
    Mof::Vector4 cblgAttenuation;
};
struct LightPillarCreateInfo {
    Mof::CVector3 position;
};

class LightPillar {
private:
    //! 有効
    bool _enable;
    //! 位置
    Mof::CVector3 _position;
    //! 分割数
    int _pillar_slice = 256;
    //! 半径
    float _pillar_radius = 2.0f;
    //! 高さ
    float _pillar_height = 200.0f;
    //! ジオメトリ
    Mof::LPGeometry _geometry;
    //! シェーダ
    std::weak_ptr<ratchet::light::Shader3DPrimitive>  _primitive_shader;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LightPillar();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~LightPillar();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPosition(const Mof::CVector3& value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetShader(const std::shared_ptr<ratchet::light::Shader3DPrimitive>& ptr);
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Disable(void);
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
#endif // !RATCHET_LIGHT_LIGHT_PILLAR_MANAGER_H