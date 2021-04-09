#ifndef MY_TIMER_H
#define MY_TIMER_H


namespace my {
class Timer {
private:
    //! ����
    float _time;
    //! �ő厞��
    float _time_max;
    //! ���[�v
    bool _loop;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Timer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Timer();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="max"></param>
    /// <param name="loop"></param>
    /// <returns></returns>
    void Initialize(float max, bool loop);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    bool Tick(float delta_time);
};
}
#endif // !MY_TIMER_H