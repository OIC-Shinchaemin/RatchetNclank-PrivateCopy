#ifndef RACHET_PLAYER_H
#define RACHET_PLAYER_H


#include "Character.h"
#include "Base/Core/Observer.h"

#include <stack>
#include <unordered_map>

#include "../Weapon/OmniWrench.h"
#include "../Weapon/Mechanical.h"
#include "../../Game/GameSystem/QuickChangeSystem.h"
#include "../../Game/GameSystem/ShopSystem.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Game/GameSystem/GameQuest.h"


namespace rachet {
class Player : public rachet::Character,
    public base::core::Observer<std::shared_ptr<rachet::Weapon>>,
    public base::core::Observer<const rachet::QuickChangeSystem::Info&> {
    using super = rachet::Character;
    struct ObservablePair {
        std::string name;
        base::core::Observable<bool> subject;
        ObservablePair(const char* str) :
            name(str),
            subject (){
        }
    };
private:
    //! ����
    std::weak_ptr<rachet::Mechanical> _current_mechanical;
    //! ����
    std::shared_ptr<rachet::OmniWrench> _omniwrench;
    //! ����
    std::vector<std::shared_ptr<rachet::Actor>> _children;
    //! ����
    std::shared_ptr<rachet::Weapon> _current_weapon;
    //! �v���C���[
    std::weak_ptr<rachet::PlayerComponent> _player_com;
    //! �r�̈ʒu
    Mof::LPBONEMOTIONSTATE _upp_bone_state;
    //! �L��
    //bool _enable;
    //! �ʒm�p
    ObservablePair _shop_system_subject;
    //! �ʒm�p
    ObservablePair _quick_change_subject;
    //! �ʒm�p
    base::core::Observable<const rachet::GameQuest&> _quest_subject;
    //! �ʒm�p
    std::unordered_map<std::string, ObservablePair* >_notificationable_subject_map;
    //! �ʒm�p
    std::stack<ObservablePair*>_notificationable_subject_stack;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Player();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Player();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(std::shared_ptr<rachet::Weapon> change) override;
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const rachet::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    //virtual void OnNotify(const rachet::ShopSystem::Info& info) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<bool>* GetShopSystemSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<bool>* GetQuickChangeSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const rachet::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="tag"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Actor> GetChild(const std::string& tag) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Mechanical> GetCurrentMechanical(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddChild(const std::shared_ptr<rachet::Actor>& ptr);
    /// <summary>
    /// �v�b�V��
    /// </summary>
    /// <param name="name"></param>
    void PushNotificationableSubject(const std::string& name);
    /// <summary>
    /// �|�b�v
    /// </summary>
    /// <param name=""></param>
    void PopNotificationableSubject(void);
    /// <summary>
    /// �v�b�V��
    /// </summary>
    /// <param name="name"></param>
    void PopNotificationableSubject(const std::string& name);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(rachet::Actor::Param* param) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RACHET_PLAYER_H