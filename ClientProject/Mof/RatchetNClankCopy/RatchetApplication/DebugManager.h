#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H


namespace debug {
class DebugManager {
private:
    //! デバッグフラグ
    bool _debug;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DebugManager() :
        _debug(false){
    }
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static DebugManager& GetInstance(void) {
        static DebugManager obj;
        return obj;
    }
    /// <summary>
    /// 判定
    /// </summary>
    bool IsDebugMode(void) {
        return _debug;
    }
    /// <summary>
    /// 変更
    /// </summary>
    void ChangeDebugMode(void) {
        _debug = !_debug;
    }
};
}
#endif // !DEBUG_MANAGER_H