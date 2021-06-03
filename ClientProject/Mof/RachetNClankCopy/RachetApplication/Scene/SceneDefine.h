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
    //! �V�F�[�_
    std::shared_ptr<Mof::CShader> value;
    //! �o�C���h
    std::shared_ptr<Mof::CShaderBindBase> bind;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="camera"></param>
    void SetCamera(Mof::ICamera& camera) {
        bind->SetCamera(&camera);
    }
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <returns></returns>
    bool Enable(unsigned long width = ::g_pGraphics->GetTargetWidth(), unsigned long height = ::g_pGraphics->GetTargetHeight()) {
        return ::CGraphicsUtilities::SetScreenSize(width, height, bind.get());
    }
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="path"></param>
    /// <returns></returns>
    template<typename T>
    bool Load(const char* path) {
        // �쐬
        value = std::make_shared< Mof::CShader>();
        bind = std::make_shared <T>();
        //�V�F�[�_�[�̓ǂݍ���
        if (!value->Load(path)) {
            value.reset();
            return false;
        } // if
        // �o�C���h
        if (!bind->Create(value.get())) {
            bind.reset();
            return false;
        } // if
        return true;
    }
    // bool Load(void* compiled_binary)
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="name"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    bool CreateShaderBuffer(const char* name, size_t size) {
        return bind->CreateShaderBuffer(name, size);
    }
    /// <summary>
    /// ���
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
    //! 0�ȉ��œK�p���ԏI��
    float time;
    //! �e�N�X�`���̕\���ʒu
    Mof::CVector2 position;
    //! �e�N�X�`���Ɏg�p����V�F�[�_
    my::ShaderPair shader;

    SceneEffect() :
        time(), position(), shader() {
    }
    virtual ~SceneEffect() {
    }
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="camera"></param>
    void SetCamera(Mof::ICamera& camera) {
        shader.SetCamera(camera);
    }
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsEnd(void) const {
        return time <= 0.0f;
    }
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path) {
        return shader.Load<Mof::CShaderBind_SpriteBase>(path);
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="name"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    bool CreateShaderBuffer(const char* name, size_t size) {
        return shader.CreateShaderBuffer(name, size);
    }
    /// <summary>
    /// �X�V
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) {
        shader.Release();
        return true;
    }
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <returns></returns>
    virtual bool Enable(unsigned long width = ::g_pGraphics->GetTargetWidth(), unsigned long height = ::g_pGraphics->GetTargetHeight()) {
        // �]��
        cbSceneEffectParam sb;
        sb.cbTime.x = time;
        shader.bind->GetShaderBuffer(0)->SetBuffer(&sb);
        return shader.Enable(width, height);
    }
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    //virtual void DebugRender(void)
};
}
#endif // !MY_SCENE_DEFINE_H