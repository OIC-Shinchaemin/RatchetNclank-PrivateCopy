#pragma once

//! �Ǝ��w�b�_
#define STAGE_FILE_HEADER     "STAGE_FILE_VER_0.01_FILE"

//! �Ǝ��w�b�_��
#define STAGE_FILE_HEADER_LEN strlen(STAGE_FILE_HEADER)

//! �Ǝ��t�b�^
#define STAGE_FILE_FOOTER     "EOF"

//! �Ǝ��t�b�^��
#define STAGE_FILE_FOOTER_LEN strlen(STAGE_FILE_FOOTER)

/// <summary>
/// �X�e�[�W�t�@�C�����̃`�����N���^�C�v��
/// </summary>
enum StageFileChank {
    StageFileChank_
};

/// <summary>
/// �X�e�[�W�t�@�C����͌��ʗ�
/// </summary>
enum StageFileResult {
    StageFileResult_Error_Unknown = 0,    //! �悭�킩��Ȃ��G���[
    StageFileResult_Success       = TRUE, //! ����I��
    StageFileResult_Error_Open,           //! �t�@�C���I�[�v�����s
    StageFileResult_Error_MeshLoad,       //! ���b�V���ǂݍ��ݎ��s
};

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g�̎�ޗ�
/// </summary>
enum StageObjectType {
    StageObjectType_None,              //! �ݒ�Ȃ�
    StageObjectType_StaticObject,      //! �ÓI�I�u�W�F�N�g
    StageObjectType_EnemySpawnPoint,   //! �G�o���ʒu
};