#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H


namespace debug {
class DebugManager {
private:
    //! �f�o�b�O�t���O
    bool _debug;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DebugManager() :
        _debug(false){
    }
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static DebugManager& GetInstance(void) {
        static DebugManager obj;
        return obj;
    }
    /// <summary>
    /// ����
    /// </summary>
    bool IsDebugMode(void) {
        return _debug;
    }
    /// <summary>
    /// �ύX
    /// </summary>
    void ChangeDebugMode(void) {
        _debug = !_debug;
    }
};
}
#endif // !DEBUG_MANAGER_H