#ifndef RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H


#include "GameSystem.h"

#include <optional>
#include <string>
#include <stack>
#include <vector>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"
#include "GameMoney.h"
#include "../../UI/UICreator.h"
#include "Shop/ShopSystemElement.h"
#include "Shop/ShopSystemEntry.h"


namespace ratchet::ui { class ShopSystemMenu; }
namespace ratchet::game::gamesystem {
class ShopSystem :
    public ratchet::game::gamesystem::GameSystem,
    public base::core::Observer<const std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>&> {
    using super = ratchet::game::gamesystem::GameSystem;
    using this_type = ratchet::game::gamesystem::ShopSystem;
public:
    struct Info {
        //! �\��
        bool enable;
        //! �A�C�e���̃C���f�b�N�X
        int  index;
        //! ���ڑI��
        bool select;
        //! �w����
        int count;
        //! ���O
        std::string weapon;
        //! ����
        bool close;
        Info() :
            enable(false),
            index(0),
            select(false),
            count(0),
            weapon(),
            close(false) {
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0),
            weapon(),
            close(false) {
        }
    };
    struct Item {
        std::string name;
        bool enable;
        int price;
        Item() :
            name(),
            price(),
            enable(false) {
        }
        Item(const char* str, int value, bool flag) :
            name(str),
            price(value),
            enable(flag) {
        }
    };
private:
    //! �\�����
    this_type::Info _infomation;
    //! �ʒm�p
    base::core::Observable<const this_type::Info&> _info_subject;
    //! �ʒm�p
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&> _buy_subject;
    //! �ʒm�p
    base::core::Observable<const ratchet::actor::weapon::Mechanical::Info&> _equipment_weapon_menu_subject;
    //! �ʒm�p
    base::core::Observable<int> _game_money_menu_subject;
    //! �Z�[�u�f�[�^
    ratchet::game::gamesystem::save::SaveData _save_data;
    //! �w���\���C���i�b�v
    std::vector<this_type::Item> _items;
    //! ����
    std::optional<std::string>_prev_weapon;
    //! ����
    std::weak_ptr<ratchet::game::gamesystem::WeaponSystem> _weapon_system;
    //! ����
    std::weak_ptr<ratchet::game::gamesystem::GameMoney> _game_money;
    //! UI�Ǘ�
    ratchet::ui::UICreator<ratchet::ui::ShopSystemMenu> _ui_creator;
    //! �v�f
    std::stack<std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>> _element_stack;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    bool Close(void);
    /// <summary>
    /// �w��
    /// </summary>
    /// <param name=""></param>
    void Buy(void);
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    void NotifyEquipmentWeaponMenu(void);
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    void NotifyGameMoneyMenu(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ShopSystem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ShopSystem();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>& add) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponSystem(std::weak_ptr<ratchet::game::gamesystem::WeaponSystem> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameMoney(std::weak_ptr<ratchet::game::gamesystem::GameMoney> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&>* GetChargeInfoSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(ratchet::game::gamesystem::save::SaveData& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H