#ifndef MY_SHOP_SYSTEM_H
#define MY_SHOP_SYSTEM_H


#include "GameSystem.h"
//#include "My/Core/Observer.h"

#include <optional>
#include <string>
#include <vector>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"
#include "GameMoney.h"


namespace my {
class ShopSystemMenu;
class ShopSystem :
    public my::GameSystem {
    using super = my::GameSystem;
    using this_type = my::ShopSystem;
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
            weapon() ,
            close(false){
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0),
            weapon() ,
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
    //my::Observable<const std::shared_ptr<This>&> _subject;
    //! �ʒm�p
    my::Observable<const this_type::Info&> _info_subject;
    //! �ʒm�p
    my::Observable<const my::ChargeInfo&> _buy_subject;
    //! �ʒm�p
    my::Observable<const my::Mechanical::Info&> _equipment_weapon_menu_subject;
    //! �ʒm�p
    my::Observable<int> _game_money_menu_subject;
    //! �Z�[�u�f�[�^
    my::SaveData _save_data;
    //! �w���\���C���i�b�v
    std::vector<this_type::Item> _items;
    //! ����
    std::optional<std::string>_prev_weapon;
    //! ����
    std::weak_ptr<my::WeaponSystem> _weapon_system;
    //! ����
    std::weak_ptr<my::GameMoney> _game_money;
    //! UI�Ǘ�
    my::UICreator<ShopSystemMenu> _ui_creator;

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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponSystem(std::weak_ptr<my::WeaponSystem> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameMoney(std::weak_ptr<my::GameMoney> ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const my::ChargeInfo&>* GetChargeInfoSubject(void);
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
    bool Load(my::SaveData& in);
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
#endif // !MY_SHOP_SYSTEM_H