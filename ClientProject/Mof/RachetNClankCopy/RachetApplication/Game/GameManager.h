#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include <memory>

#include "GameSystem/GameMoney.h"
#include "GameSystem/WeaponSystem.h"
#include "GameSystem/QuickChangeSystem.h"


namespace my {
class GameManager : public std::enable_shared_from_this<my::GameManager> {
private:
    //! ����
    std::shared_ptr<my::WeaponSystem>  _weapon_system;
    //! �N�C�b�N�`�F���W
    std::shared_ptr<my::QuickChangeSystem>  _quick_change;
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
    /// <returns></returns>
    bool Update(void);
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