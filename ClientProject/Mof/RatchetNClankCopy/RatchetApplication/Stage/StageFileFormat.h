#pragma once
#define TRUE 1

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
enum class StageFileChank {
};

/// <summary>
/// �X�e�[�W�t�@�C����͌��ʗ�
/// </summary>
enum class StageFileResult : int {
    Error_Unknown = 0,    //! �悭�킩��Ȃ��G���[
    Success       = TRUE, //! ����I��
    Error_Open,           //! �t�@�C���I�[�v�����s
    Error_MeshLoad,       //! ���b�V���ǂݍ��ݎ��s
};
