#ifndef MY_GAME_MANAGER_H
#define MY_GAME_MANAGER_H


#include <memory>


namespace my {
class GameManager : public std::enable_shared_from_this<my::GameManager> {
private:
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_GAME_MANAGER_H