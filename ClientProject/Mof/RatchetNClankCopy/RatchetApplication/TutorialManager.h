#ifndef TUTORIAL_MANAGER_H
#define TUTORIAL_MANAGER_H


#include <array>


namespace tutorial {
class TutorialManager {
public:
    enum class TutorialType {
        Attack,
        Jump,
        Weapon,
        CountMax,
    };
private:
    //! �J�n�t���O
    std::array<bool, static_cast<int>(TutorialType::CountMax)> _flags;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TutorialManager() :
        _flags() {
        _flags.fill(false);
        //this->Liberation(TutorialType::Attack);
        //this->Liberation(TutorialType::Jump);
        //this->Liberation(TutorialType::Weapon);
    }
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static TutorialManager& GetInstance(void) {
        static TutorialManager obj;
        return obj;
    }
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsLiberation(TutorialType type) {
        auto index = static_cast<int>(type);
        return _flags.at(index);
    }
    /// <summary>
    /// ���
    /// </summary>
    /// <param name="type"></param>
    void Liberation(TutorialType type) {
        auto index = static_cast<int>(type);
        _flags.at(index) = true;
    }
};
}
#endif // !TUTORIAL_MANAGER_H