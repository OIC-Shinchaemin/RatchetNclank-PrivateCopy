#pragma once

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g�̎�ޗ�
/// </summary>
enum class StageObjectType {
    None,              //! �ݒ�Ȃ�
    StaticObject,      //! �ÓI�I�u�W�F�N�g
    EnemySpawnPoint,   //! �G�o���ʒu
    Elevator,          //! �G���x�[�^�[
    Bridge,            //! ��
    BoxBullet,
    BoxBolt,
    BoxNanotech,
    MoveCloud_Near,
    MoveCloud_Middle,
    MoveCloud_Far,
};