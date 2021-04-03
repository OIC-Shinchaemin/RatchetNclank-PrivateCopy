#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H

#include <memory>
#include <vector>

#include "My/Core/Observer.h"
#include "GameWorld.h"
#include "Renderer.h"
#include "PhysicWorld.h"
#include "../GameSystem/GameMoney.h"
#include "../GameSystem/WeaponSystem.h"
#include "../GameSystem/QuickChangeSystem.h"
#include "../Stage/Stage.h"
#include "../Character/Character.h"
#include "../Character/Enemy.h"


namespace my {
class GameManager : public std::enable_shared_from_this<my::GameManager>, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
private:
    //! �폜
    std::vector<std::shared_ptr<my::Actor>> _delete_actors;
    //! �Q�[��
    my::GameWorld _game_world;
    //! �����_���[
    my::Renderer _renderer;
    //! �R���W����
    my::PhysicWorld _physic_world;
    //! ��
    std::unique_ptr<my::GameMoney>  _game_money;
    //! ����
    std::shared_ptr<my::WeaponSystem>  _weapon_system;
    //! �N�C�b�N�`�F���W
    std::shared_ptr<my::QuickChangeSystem>  _quick_change;
    //! �X�e�[�W
    Stage _stage;
    //! �L�����N�^
    std::shared_ptr<my::Character> _character;
    //! �L�����N�^
    std::vector<std::shared_ptr<my::Enemy>> _enemies;
private:
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// collision
    /// </summary>
    /// <param name=""></param>
    void Collision(void);
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
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>&ptr) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_MANAGER_H