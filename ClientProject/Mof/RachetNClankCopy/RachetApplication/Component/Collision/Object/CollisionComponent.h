#ifndef MY_COLLISION_COMPONENT_H
#define MY_COLLISION_COMPONENT_H


#include "../../Component.h"

#include <optional>
#include <any>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include <Mof.h>

#include "../../../Stage/StageObject.h"
#include "../../../Stage/Gimmick/GimmickBase.h"


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
    float distance = 0.0f;
    //! ���܂�l
    Mof::CVector3 angle;

    //! �ՓˑΏ�
    std::any target;
    CollisionInfo() : distance(0.0f), angle() {}
    CollisionInfo(const Mof::COLLISIONOUTGEOMETRY& c) : distance(c.d), angle() {}
    //virtual ~CollisionInfo() {}
};
class CollisionComponent : public my::Component {
public:
    enum class CollisionFuncType {
        Enter,
        Stay,
        Exit,
    };
    class CollisionFunc {
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
        bool Execute(const my::CollisionInfo& info) const {
            return _func(info);
        }
    };

    using super = my::Component;
    using FuncArray = std::vector<CollisionFunc>;
private:
    //! �Փ˂����I�u�W�F�N�g
    std::vector<std::weak_ptr<my::CollisionComponent>> _collisioned;
    //! ���s�֐�
    std::unordered_map<std::string, FuncArray> _on_enter;
    //! ���s�֐�
    std::unordered_map<std::string, FuncArray> _on_stay;
    //! ���s�֐�
    std::unordered_map<std::string, FuncArray> _on_exit;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="target"></param>
    /// <param name="obj"></param>
    /// <param name="out"></param>
    void AddCollisionFunc(const std::string& target, const CollisionFunc& obj, std::unordered_map<std::string, FuncArray>& out);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="key"></param>
    /// <param name="info"></param>
    /// <param name="in"></param>
    /// <returns></returns>
    bool ExecuteFunction(const std::string& key, const my::CollisionInfo& info, const std::unordered_map<std::string, FuncArray>& in);
protected:
    /// <summary>
    /// �Փ˔���
    /// </summary>
    /// <param name="sphere"></param>
    /// <param name="box"></param>
    /// <returns></returns>
    bool CollisionShpereAABB(const Mof::CSphere& sphere, const Mof::CBoxAABB& box);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    CollisionComponent(int priority);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CollisionComponent();
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
    void AddCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="ptr"></param>
    /// <returns></returns>
    bool ExistCollisionedObject(const std::shared_ptr<my::CollisionComponent>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="type"></param>
    /// <param name="target"></param>
    /// <param name="obj"></param>
    void AddCollisionFunc(CollisionFuncType type, const std::string& target, const CollisionFunc& obj);
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
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="obj"></param>
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick);
};
}
#endif // !MY_COLLISION_COMPONENT_H