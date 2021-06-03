#ifndef MY_SCENE_DEFINE_H
#define MY_SCENE_DEFINE_H


#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

namespace my {
class Scene;
struct SceneType {
    static std::string kTitleScene;
    static std::string kGameScene;
    static std::string kClearScene;
    static std::string kDescriptionScene;
};
struct SceneMessage {
    std::string type_name;
    std::string info_name;
    SceneMessage(const std::string& type, const std::string& info) :
        type_name(type), info_name(info) {
    }
};

struct ShaderPair {
    //! シェーダ
    std::shared_ptr<Mof::CShader> value;
    //! バインド
    std::shared_ptr<Mof::CShaderBindBase> bind;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="camera"></param>
    void SetCamera(Mof::ICamera& camera) {
        bind->SetCamera(&camera);
    }
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <returns></returns>
    bool Enable(unsigned long width = ::g_pGraphics->GetTargetWidth(), unsigned long height = ::g_pGraphics->GetTargetHeight()) {
        return ::CGraphicsUtilities::SetScreenSize(width, height, bind.get());
    }
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="path"></param>
    /// <returns></returns>
    template<typename T>
    bool Load(const char* path) {
        // 作成
        value = std::make_shared< Mof::CShader>();
        bind = std::make_shared <T>();
        //シェーダーの読み込み
        if (!value->Load(path)) {
            value.reset();
            return false;
        } // if
        // バインド
        if (!bind->Create(value.get())) {
            bind.reset();
            return false;
        } // if
        return true;
    }
    // bool Load(void* compiled_binary)
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="name"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    bool CreateShaderBuffer(const char* name, size_t size) {
        return bind->CreateShaderBuffer(name, size);
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void) {
        if (bind) {
            if (!bind->Release()) {
                return false;
            } // if
        } // if
        if (value) {
            if (!value->Release()) {
                return false;
            } // if
        } // if
        bind.reset();
        value.reset();
        return true;
    }
};


struct cbSceneEffectParam {
    Vector4	cbTime;
};

struct SceneEffect {
    //! 0以下で適用期間終了
    float time;
    //! テクスチャの表示位置
    Mof::CVector2 position;
    //! テクスチャに使用するシェーダ
    my::ShaderPair shader;

    SceneEffect() :
        time(), position(), shader() {
    }
    virtual ~SceneEffect() {
    }
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="camera"></param>
    void SetCamera(Mof::ICamera& camera) {
        shader.SetCamera(camera);
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsEnd(void) const {
        return time <= 0.0f;
    }
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path) {
        return shader.Load<Mof::CShaderBind_SpriteBase>(path);
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="name"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    bool CreateShaderBuffer(const char* name, size_t size) {
        return shader.CreateShaderBuffer(name, size);
    }
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) {
        time -= delta_time;
        if (time <= 0.0f) {
            time = 0.0f;
        } // if
        return true;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) {
        shader.Release();
        return true;
    }
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <returns></returns>
    virtual bool Enable(unsigned long width = ::g_pGraphics->GetTargetWidth(), unsigned long height = ::g_pGraphics->GetTargetHeight()) {
        // 転送
        cbSceneEffectParam sb;
        sb.cbTime.x = time;
        shader.bind->GetShaderBuffer(0)->SetBuffer(&sb);
        return shader.Enable(width, height);
    }
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    //virtual void DebugRender(void)
};
}
#endif // !MY_SCENE_DEFINE_H