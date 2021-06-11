#ifndef RACHET_WEAPON_SYSTEM_H
#define RACHET_WEAPON_SYSTEM_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "../../Actor/Weapon/Mechanical.h"
#include "../../Factory/Factory.h"


namespace rachet {
struct ChargeInfo {
    //! ����
    std::string type;
    //! ���U��
    std::uint32_t size;
};
class WeaponSystem : 
    public base::core::Observer<const std::string&>,
    public base::core::Observer<const rachet::ChargeInfo&>
{
    using Pair = std::pair<std::string, std::shared_ptr<rachet::Mechanical>>;
private:
    //! ����
    std::vector<Pair> _weapons;
    //! ����
    std::shared_ptr<rachet::Mechanical> _current_mechanical;
    //! �ʒm�p
    base::core::Observable<std::shared_ptr<rachet::Weapon>> _subject;
    //! �ʒm�p
    base::core::Observable<const rachet::Mechanical::Info&> _equipment_subject;
    //! �}�b�v
    std::unordered_map<std::string, std::string> _builder_name_map;
    //! �Z�[�u�f�[�^
    rachet::SaveData _save_data;
    //! ���\�[�X
    std::weak_ptr<rachet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    WeaponSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~WeaponSystem();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const std::string& change) override;
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const rachet::ChargeInfo& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Mechanical> GetCurrentMechanicalWeapon(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<rachet::WeaponSystem::Pair>& GetWeaponMap(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<base::core::Observer<std::shared_ptr<rachet::Weapon>>>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="out"></param>
    void CreateAvailableMechanicalWeaponNames(std::vector<std::string>& out);
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(rachet::SaveData& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="observer"></param>
    /// <returns></returns>
    bool Initialize(const std::shared_ptr<base::core::Observer<const char*, const std::shared_ptr<rachet::Actor>&>>& observer);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    std::shared_ptr<rachet::Mechanical>GetMechanicalWeapon(const std::string& name);
};
}
#endif // !RACHET_WEAPON_SYSTEM_H