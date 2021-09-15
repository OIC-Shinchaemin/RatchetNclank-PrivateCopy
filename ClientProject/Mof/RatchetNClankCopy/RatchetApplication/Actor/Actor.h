#ifndef RATCHET_ACTOR_ACTOR_H
#define RATCHET_ACTOR_ACTOR_H


#include <optional>
#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "Base/Core/Define.h"
#include "Base/Core/Observable.h"
#include "ActorDefine.h"


namespace ratchet::component { class Component; }
namespace ratchet::factory::builder { class IBuilder; }
namespace ratchet::actor {
class Actor :
    public std::enable_shared_from_this<actor::Actor>,
    public ::base::core::Observable<const char*, const std::shared_ptr<actor::Actor>&> {
public:
    using ComPtr = std::shared_ptr<component::Component>;
    using ComArray = std::vector<ComPtr>;
    using Observable = base::core::Observable<const char*, const std::shared_ptr<actor::Actor>&>;
    struct Param {
        //! ���O
        std::string name;
        //! �^�O
        std::string tag;
        //! �g�����X�t�H�[��
        def::Transform transform;
        Param() :
            name("nameless"),
            tag("none"),
            transform() {
        }
        virtual ~Param() {
        }
    };
private:
    //! ���
    ratchet::actor::ActorState _state;
    //! ���O
    std::string _name;
    //! �^�O
    std::string _tag;
    //! �g�����X�t�H�[��
    def::Transform _transform;
    //! �g�����X�t�H�[��
    def::Transform _initial_transform;
    //! �g�����X�t�H�[��
    std::optional<Mof::CMatrix44> _parent_transform;
    //! �@�\
    ComArray _components;
    ComArray _input_components;
    ComArray _update_components;
    ComArray _render_components;
public:
    /// <summary>
    /// ��ԕύX
    /// </summary>
    virtual void Activate(void);
    /// <summary>
    /// ��ԕύX
    /// </summary>
    virtual void Sleep(void);
    /// <summary>
    /// ��ԕύX
    /// </summary>
    virtual void Pause(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Actor();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Actor();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="name"></param>
    void SetName(const char* name);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="tag"></param>
    void SetTag(const char* tag);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Mof::CVector3 position);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rotate"></param>
    void SetRotate(Mof::CVector3 rotate);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="scale"></param>
    void SetScale(Mof::CVector3 scale);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="transform"></param>
    void SetParentTransform(std::optional<Mof::CMatrix44> transform);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    actor::ActorState GetState(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���O</returns>
    std::string GetName(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�^�O</returns>
    std::string GetTag(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetRotate(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetScale(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetInitialPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::optional<Mof::CMatrix44> GetParentTransform(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    std::shared_ptr<T>GetComponent(void) const {
        for (auto& com : _components) {
            auto ret = std::dynamic_pointer_cast<T>(com);
            if (ret) {
                return ret;
            } // if
        } // for
        return nullptr;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="out"></param>
    template <typename T>
    void GetComponents(std::vector<std::weak_ptr<T>>& out) const {
        for (auto& com : _components) {
            auto ptr = std::dynamic_pointer_cast<T>(com);
            if (ptr) {
                out.push_back(ptr);
            } // if
        } // for
    }
    /// <summary>
    /// �`�攻��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InCameraRange(void) const;
    /// <summary>
    /// �����������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InFrustum(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const ComPtr& component);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name=""></param>
    void CloneToComponents(const ComArray& com_array);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="component"></param>
    void RemoveComponent(const ComPtr& component);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(actor::Actor::Param* param);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<factory::builder::IBuilder>& builder);
};
}
#endif // !RATCHET_ACTOR_ACTOR_H