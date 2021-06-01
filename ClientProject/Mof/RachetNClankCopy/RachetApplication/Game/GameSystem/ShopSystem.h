#ifndef MY_SHOP_SYSTEM_H
#define MY_SHOP_SYSTEM_H


#include "My/Core/Observer.h"

#include <string>
#include <vector>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"


namespace my {
class ShopSystem :
    public std::enable_shared_from_this<my::ShopSystem>, public my::Observer<bool> {
public:
    struct Info {
        //! �\��
        bool enable;
        //! �A�C�e���̃C���f�b�N�X
        std::uint32_t index;
        //! ���ڑI��
        bool select;
        //! �w����
        std::uint32_t count;
        Info() :
            enable(false),
            index(0),
            select(false),
            count(0) {
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0){
        }
    };
    struct Item {
        std::string name;
        bool enable;
        Item() :
            name(),
            enable(false) {
        }
        Item(const char* str, bool flag) :
            name(str),
            enable(flag) {
        }
    };
private:
    //! �\�����
    my::ShopSystem::Info _infomation;
    //! �ʒm�p
    my::Observable<const my::ShopSystem::Info&> _subject;
    //! �ʒm�p
    my::Observable<const my::ChargeInfo&> _buy_subject;
    //! �Z�[�u�f�[�^
    my::SaveData _save_data;
    //! �w���\���C���i�b�v
    std::vector<my::ShopSystem::Item> _items;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;

    /// <summary>
    /// �w��
    /// </summary>
    /// <param name=""></param>
    void Buy(void);
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
    my::Observable<const my::ChargeInfo&>* GetChargeInfoSubject(void);
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
    bool Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_SHOP_SYSTEM_H