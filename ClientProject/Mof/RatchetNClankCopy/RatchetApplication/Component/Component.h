#ifndef RATCHET_COMPONENT_H
#define RATCHET_COMPONENT_H


#include <memory>

#include "rapidjson/document.h"

#include "../Actor.h"

#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/UI/UICanvas.h"


namespace ratchet {
class Component : public std::enable_shared_from_this<ratchet::Component> {
private:
    //! ���̋@�\�̏��L��
    std::weak_ptr<ratchet::Actor> _owner;
    //! �������قǏ�������鏇�Ԃ�����
    int _priority;
    //! �L��
    bool _active;
protected:
    //! ���\�[�X
    static std::weak_ptr<ratchet::ResourceMgr> _resource_manager;
    //! ���\�[�X
    static std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    static void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    static void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority">�D��x</param>
    Component(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    Component(const Component& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Component();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetOwner(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> GetOwner(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetPriority(void) const;
    /// <summary>
    /// �L������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsInput(void) const;
    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsUpdate(void) const;
    /// <summary>
    /// �`�攻��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsRender(void) const;
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Activate(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Inactivate(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) = 0;
#ifdef _DEBUG
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void);
#endif // _DEBUG
};
static bool operator<(const ratchet::Component& a, const ratchet::Component& b) noexcept {
    return a.GetPriority() < b.GetPriority();
}
static bool operator<(const std::shared_ptr<ratchet::Component>& a, const std::shared_ptr < ratchet::Component>& b) noexcept {
    return a->GetPriority() < b->GetPriority();
}
}
#endif // !RATCHET_COMPONENT_H