#ifndef MY_WEAPON_SYSTEM_H
#define MY_WEAPON_SYSTEM_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "../../Actor/Weapon/Mechanical.h"
#include "../../Factory/Factory.h"


namespace my {
class WeaponSystem : public my::Observer<const std::string&> {
    using Pair = std::pair<std::string, std::shared_ptr<my::Mechanical>>;
private:
    //! ����
    std::vector<Pair> _weapons;
    //! �ʒm�p
    my::Observable<std::shared_ptr<my::Mechanical>> _subject;
    //! �ʒm�p
    my::Observable<const my::Mechanical::Info&> _equipment_subject;
    //! �}�b�v
    std::unordered_map<std::string, std::string> _builder_name_map;
    //! �Z�[�u�f�[�^
    my::SaveData _save_data;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<my::WeaponSystem::Pair>& GetWeaponMap(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddMechanicalWeaponObserver(const std::shared_ptr<my::Observer<std::shared_ptr<my::Mechanical>>>& ptr);
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
    bool Load(my::SaveData& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
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
    std::shared_ptr<my::Mechanical>GetMechanicalWeapon(const std::string& name);
};
}
#endif // !MY_WEAPON_SYSTEM_H