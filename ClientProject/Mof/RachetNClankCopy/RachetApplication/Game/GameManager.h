#ifndef RATCHET_GAME_MANAGER_H
#define RATCHET_GAME_MANAGER_H


#include <memory>

#include "GameSystem/GameSystem.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/WeaponSystem.h"
#include "GameSystem/QuickChangeSystem.h"
#include "GameSystem/HelpDesk.h"
#include "GameSystem/GameMoney.h"
#include "GameSystem/ShopSystem.h"
#include "GameSystem/OptionSystem.h"
#include "GameSystem/GamePauseSystem.h"


namespace ratchet {
class GameManager : 
    public std::enable_shared_from_this<ratchet::GameManager>,
    public base::core::Observer<const std::shared_ptr<ratchet::GameSystem>&> {
private:
    //! �X�V�p
    std::vector<std::shared_ptr<ratchet::GameSystem>> _update_system;
    //! �X�V�p
    std::vector<std::shared_ptr<ratchet::GameSystem>> _disable_systems;
    //! ����
    std::shared_ptr<ratchet::WeaponSystem>  _weapon_system;
    //! �N�C�b�N�`�F���W
    std::shared_ptr<ratchet::QuickChangeSystem> _quick_change;
    //! �w���v�f�X�N
    std::shared_ptr<ratchet::HelpDesk>  _help_desk;
    //! ����
    std::shared_ptr<ratchet::GameMoney> _game_money;
    //! �V���b�v
    std::shared_ptr<ratchet::ShopSystem> _shop_system;
    //! �I�v�V����
    std::shared_ptr<ratchet::OptionSystem> _option_system;
    //! �|�[�Y
    std::shared_ptr<ratchet::GamePauseSystem> _pause_system;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;

    template<typename T>
    void SetPtr(T ptr) {
        ptr->SetResourceManager(_resource);
        ptr->SetUICanvas(_ui_canvas);
    }
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
    virtual void OnNotify(const std::shared_ptr<ratchet::GameSystem>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::WeaponSystem> GetWeaponSystem(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::QuickChangeSystem> GetQuickChange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::HelpDesk> GetHelpDesk(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::GameMoney> GetGameMoney(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::ShopSystem> GetShopSystem(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::OptionSystem> GetOptionSystem(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::GamePauseSystem> GetGamePauseSystem(void) const;
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
#endif // !RATCHET_GAME_MANAGER_H