#ifndef MY_ACTOR_H
#define MY_ACTOR_H


#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "My/Core/Define.h"
#include "My/Core/Observable.h"
#include "Collision/Object/CollisionObject.h"
#include "Velocity.h"


namespace my {
enum class ActorState {
    Active,
    End
};
class Actor : public std::enable_shared_from_this<my::Actor>, public my::Observable<const char*, const std::shared_ptr<my::Actor>&> {
public:
    using ComPtr = std::shared_ptr<class Component>;
    using ComArray = std::vector<ComPtr>;
    using Observable = my::Observable<const char*, const std::shared_ptr<my::Actor>&>;
public:
    struct Param {
        //! �g�����X�t�H�[��
        def::Transform transform;
        //! ���O
        std::string name;

        Param() :
            transform(){
        }
        virtual ~Param() {
        }
    };
private:
    //! ���
    my::ActorState _state;
    //! ���O
    std::string _name;
    //! �g�����X�t�H�[��
    def::Transform _transform;
    //! �@�\
    ComArray _components;
    ComArray _input_components;
    ComArray _update_components;
    ComArray _render_components;
    //! �Փ˗p
    std::vector<std::shared_ptr<my::CollisionObject>> _collision_objects;
protected:
    //! ���x
    my::Velocity _velocity;
    /// <summary>
    /// ����
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name=""></param>
    template<typename Type>
    void AddCollisionObject(std::shared_ptr<Type> ptr) {
        _collision_objects.push_back(ptr);
    }
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="rotate"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="position"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void UpdateTransform(float delta_time);
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::ActorState GetState(void) const;
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
    const std::vector<std::shared_ptr<my::CollisionObject>>& GetCollisionObjects(void) const;
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
    /// �ǉ�
    /// </summary>
    /// <param name="component"></param>
    void AddComponent(const ComPtr& component);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="component"></param>
    void RemoveComponent(const ComPtr& component);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    void End(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param);
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
    void Construct(const std::shared_ptr<class IBuilder>& builder);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void);
};
}
#endif // !MY_ACTOR_H