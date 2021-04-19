#ifndef MY_SAVE_SYSTEM_H
#define MY_SAVE_SYSTEM_H


#include <string>

#include "SaveData.h"


namespace my {
class SaveSystem {
private:
    std::string _path;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SaveSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SaveSystem();
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="out"></param>
    /// <returns></returns>
    bool Fetch(my::SaveData& out);
    /// <summary>
    /// 書き込み
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    bool Save(const my::SaveDataParam& param);
};
}
#endif // !MY_SAVE_SYSTEM_H