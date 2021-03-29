#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include "Renderer.h"
#include "../Character.h"
#include "../QuickChangeSystem.h"
#include "../GameMoney.h"
#include "../Weapon/Weapon.h"
#include "../WeaponSystem.h"


namespace my {
class GameManager {
private:
	//! レンダラー
	my::Renderer _renderer;
	//! キャラクタ
	std::shared_ptr<my::Character> _character;
	//! 金
	std::unique_ptr<my::GameMoney>  _game_money;
	//! 武器
	std::shared_ptr<my::Weapon> _current_weapon;
	//! 武器
	std::shared_ptr<my::WeaponSystem>  _weapon_system;
	//! クイックチェンジ
	std::shared_ptr<my::QuickChangeSystem>  _quick_change;
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