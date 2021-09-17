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
    //! 開始フラグ
    std::array<bool, static_cast<int>(TutorialType::CountMax)> _flags;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TutorialManager() :
        _flags() {
        _flags.fill(false);
        //this->Liberation(TutorialType::Attack);
        //this->Liberation(TutorialType::Jump);
        //this->Liberation(TutorialType::Weapon);
    }
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static TutorialManager& GetInstance(void) {
        static TutorialManager obj;
        return obj;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool IsLiberation(TutorialType type) {
        auto index = static_cast<int>(type);
        return _flags.at(index);
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name="type"></param>
    void Liberation(TutorialType type) {
        auto index = static_cast<int>(type);
        _flags.at(index) = true;
    }
};
}
#endif // !TUTORIAL_MANAGER_H