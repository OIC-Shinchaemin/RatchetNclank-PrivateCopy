#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include <memory>

#include "GameSystem/GameSystem.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/WeaponSystem.h"
#include "GameSystem/QuickChangeSystem.h"
#include "GameSystem/HelpDesk.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/ShopSystem.h"
#include "GameSystem/OptionSystem.h"


namespace my {
class GameManager : 
    public std::enable_shared_from_this<my::GameManager>,
    public my::Observer<const std::shared_ptr<my::GameSystem>&> {
private:
    //! �X�V�p
    std::vector<std::shared_ptr<my::GameSystem>> _update_system;
    //! �X�V�p
    std::vector<std::shared_ptr<my::GameSystem>> _disable_systems;
    //! ����
    std::shared_ptr<my::WeaponSystem>  _weapon_system;
    //! �N�C�b�N�`�F���W
    std::shared_ptr<my::QuickChangeSystem> _quick_change;
    //! �w���v�f�X�N
    std::shared_ptr<my::HelpDesk>  _help_desk;
    //! ����
    std::shared_ptr<my::GameMoney> _game_money;
    //! �V���b�v
    std::shared_ptr<my::ShopSystem> _shop_system;
    //! �I�v�V����
    std::shared_ptr<my::OptionSystem> _option_system;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameManager();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="ptr"></param>
    virtual void OnNotify(const std::shared_ptr<my::GameSystem>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::WeaponSystem> GetWeaponSystem(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::QuickChangeSystem> GetQuickChange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::HelpDesk> GetHelpDesk(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::GameMoney> GetGameMoney(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::ShopSystem> GetShopSystem(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::OptionSystem> GetOptionSystem(void) const;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name=""></param>
    void GameSystemLoad(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    bool Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void GameSystemRelease(void);
};
}
#endif // !MY_GAME_MANAGER_H