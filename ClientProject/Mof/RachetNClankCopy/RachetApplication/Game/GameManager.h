#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include "Renderer.h"
#include "../Character.h"


namespace my {
class GameManager {
private:
	//! �����_���[
	my::Renderer _renderer;
	//! �L�����N�^
	std::shared_ptr<my::Character> _character;
private:
	/// <summary>
	/// �ǉ�
	/// </summary>
	/// <param name="ptr"></param>
	void AddElement(const std::shared_ptr<my::Character>& ptr);
	/// <summary>
	/// �ǉ�
	/// </summary>
	/// <param name="ptr"></param>
	void RemoveElement(const std::shared_ptr<my::Character>& ptr);
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