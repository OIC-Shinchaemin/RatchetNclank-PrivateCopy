#ifndef MY_COLLISION_OBJECT_H
#define MY_COLLISION_OBJECT_H


#include <optional>
#include <any>
#include <memory>
#include <string>

#include <Mof.h>

#include "../../Component.h"


namespace my {
struct SightObject {
    //! ���_
    Mof::CVector3 position;
    //! ����
    Mof::CVector3 rotate;
    SightObject() :
        position(), rotate() {
    }
    SightObject(Mof::CVector3 pos, Mof::CVector3 rot) :
        position(pos), rotate(rot) {
    }
};

struct CollisionInfo {
    //! ���܂�l
    float d = 0.0f;
    //! �ՓˑΏ�
    std::any target;
    CollisionInfo() : d(0.0f) {}
    CollisionInfo(const Mof::COLLISIONOUTGEOMETRY& c) : d(c.d) {}
    //virtual ~CollisionInfo() {}
};
class CollisionObject : public my::Component {
    using super = my::Component;
public:
    enum class CollisionFuncType {
        Enter,
        Stay,
        Exit,
    };
    class CollisionFunc {
        //using Func = std::function<bool(std::shared_ptr<my::CollisionInfo>)>;
        using Func = std::function<bool(const my::CollisionInfo&)>;
    private:
        //! ���s�֐�
        Func _func;
    public:
        CollisionFunc() :_func() {}
        CollisionFunc(Func func) :_func(func) {}
        void AddFunction(Func lambda) {
            this->_func = lambda;
        }
        //bool Execute(std::shared_ptr<my::CollisionInfo> info) {
        bool Execute(const my::CollisionInfo& info) {
            return _func(info);
        }
    };
private:
    //! �Փ˂����I�u�W�F�N�g
    std::vector<std::weak_ptr<my::CollisionObject>> _collisioned;
    //! ���s�֐�
    std::unordered_map<std::string, CollisionFunc> _on_enter;
    //! ���s�֐�
    std::unordered_map<std::string, CollisionFunc> _on_stay;
    //! ���s�֐�
    std::unordered_map<std::string, CollisionFunc> _on_exit;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    CollisionObject(int priority);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CollisionObject();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="owner"></param>
    //virtual void SetOwner(std::any owner) = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual std::any GetOwner(void) const = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<my::SightObject> GetSightObject(void) = 0;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool ExistCollisionedObject(const std::shared_ptr<my::CollisionObject>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="type"></param>
    /// <param name="lambda"></param>
    void AddCollisionFunc(CollisionFuncType type, const std::string& key, CollisionFunc lambda);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteEnterFunction(const std::string& key, const my::CollisionInfo& info);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteStayFunction(const std::string& key, const my::CollisionInfo& info);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    bool ExecuteExitFunction(const std::string& key, const my::CollisionInfo& info);
};
}
#endif // !MY_COLLISION_OBJECT_H