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
    //! �X�g�b�v
    bool _stop;
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
    /// ���݂̎��Ԃ�Ԃ�
    /// </summary>
    float operator() (void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="max"></param>
    /// <param name="loop"></param>
    /// <param name="stop"></param>
    /// <returns></returns>
    void Initialize(float max, bool loop, bool stop = false);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns>�w��l�ɓ��B</returns>
    bool Tick(float delta_time);
};
}
#endif // !MY_TIMER_H