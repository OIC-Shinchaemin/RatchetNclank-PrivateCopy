#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H

#include <memory>
#include <vector>

#include "Renderer.h"
#include "../GameSystem/GameMoney.h"
#include "../GameSystem/WeaponSystem.h"
#include "../GameSystem/QuickChangeSystem.h"
#include "../Stage/Stage.h"
#include "../Character/Character.h"
#include "../Character/Enemy.h"
#include "../Weapon/Weapon.h"


namespace my {
class GameManager {
private:
	//! レンダラー
	my::Renderer _renderer;
	//! 金
	std::unique_ptr<my::GameMoney>  _game_money;
	//! 武器
	std::shared_ptr<my::WeaponSystem>  _weapon_system;
	//! クイックチェンジ
	std::shared_ptr<my::QuickChangeSystem>  _quick_change;
	//! ステージ
	Stage _stage;
	//! キャラクタ
	std::shared_ptr<my::Character> _character;
	//! キャラクタ
	std::vector<std::shared_ptr<my::Enemy>> _enemies;
	//! 武器
	std::shared_ptr<my::Weapon> _current_weapon;
private:
	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="ptr"></param>
	void AddElement(const std::shared_ptr<my::Character>& ptr);
	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="ptr"></param>
	void RemoveElement(const std::shared_ptr<my::Character>& ptr);
	/// <summary>
	/// collision
	/// </summary>
	/// <param name=""></param>
	void Collision(void);
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameManager();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Initialize(void);
	/// <summary>
	/// 入力
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Input(void);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta_time"></param>
	/// <returns></returns>
	bool Update(float delta_time);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Render(void);
	/// <summary>
	/// 解放
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void);
};
}
#endif // !MY_GAME_MANAGER_H