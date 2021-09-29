#include	"SpriteSet.h"

ratchet::game::gamesystem::text::CSpriteSet::CSpriteSet() :
    m_Motion(),
    CSprite2D() {
    memset(m_FileName, 0, MAX_PATH);
}

ratchet::game::gamesystem::text::CSpriteSet::~CSpriteSet() {
    Release();
}

bool ratchet::game::gamesystem::text::CSpriteSet::Load(const char* pName) {
    //�e�L�X�g�t�@�C�����J��
    FILE* fp = fopen(pName, "rt");
    if (fp == NULL) 	{
        return false;
    }
    //�t�@�C���̑S�e�ʂ𒲂ׂ�
    //��x�t�@�C���̏I�[�Ɉړ����āA���̈ʒu�𒲂ׂ邱�ƂŃT�C�Y���킩��
    //���׏I�������̓t�@�C���̐擪�Ɉړ����Ė߂��Ă���
    //���������̕��@�ł�����ȃT�C�Y��ǂݍ��ނ��Ƃ͂ł��Ȃ�
    fseek(fp, 0, SEEK_END);
    long fSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //�t�@�C���T�C�Y�������̃��������m�ۂ���
    //�I�[���܂߂邽�߁{�P���Ă���
    char* pBuffer = (char*)malloc(fSize + 1);
    //�t�@�C����S�ăo�b�t�@�ɓǂݍ���
    //�����Ŏ��ۂɓǂݍ��߂��T�C�Y�𒲂ׂĂ��̏I�[��\0�����
    fSize = fread(pBuffer, 1, fSize, fp);
    pBuffer[fSize] = '\0';
    char* pstr;
    //�t�@�C�����ۑ�
    strcpy(m_FileName, pName);

    //�e�N�X�`���̓ǂݍ���
    pstr = strtok(pBuffer, ",");
    pstr = Trim(pstr);
    if (!CreateSprite(pstr)) 	{
        return false;
    }

    //�A�j���[�V������
    pstr = strtok(NULL, ",");
    int cnt = atoi(pstr);
    SpriteAnimationCreate* anim = new SpriteAnimationCreate[cnt];
    for (int i = 0; i < cnt; i++) 	{
        pstr = strtok(NULL, ",");
        anim[i].Name = Trim(pstr);
        pstr = strtok(NULL, ",");
        anim[i].OffsetX = atof(pstr);
        pstr = strtok(NULL, ",");
        anim[i].OffsetY = atof(pstr);
        pstr = strtok(NULL, ",");
        anim[i].Width = atof(pstr);
        pstr = strtok(NULL, ",");
        anim[i].Height = atof(pstr);
        pstr = strtok(NULL, ",");
        anim[i].bLoop = atoi(pstr);
        pstr = strtok(NULL, ",");
        int pcnt = atoi(pstr);
        for (int j = 0; j < pcnt; j++) 		{
            pstr = strtok(NULL, ",");
            anim[i].Pattern[j].Wait = atoi(pstr);
            pstr = strtok(NULL, ",");
            anim[i].Pattern[j].No = atoi(pstr);
            pstr = strtok(NULL, ",");
            anim[i].Pattern[j].Step = atoi(pstr);
        }
        anim[i].Pattern[pcnt].No = 0;
        anim[i].Pattern[pcnt].Step = 0;
        anim[i].Pattern[pcnt].Wait = 0;
    }
    //�A�j���[�V������񐶐�
    m_Motion.Create(anim, cnt);
    m_Motion.ChangeMotion(0);

    //�t�@�C�������
    fclose(fp);
    free(pBuffer);
    delete[] anim;
    return true;
}

MofBool ratchet::game::gamesystem::text::CSpriteSet::Update(void) {
    //�e�̏��������s����
    CSprite2D::Update();
    //�A�j���[�V�����̍X�V
    m_Motion.AddTimer(CUtilities::GetFrameSecond());
    m_ImageRect = m_Motion.GetSrcRect();
    return TRUE;
}

MofBool ratchet::game::gamesystem::text::CSpriteSet::Release(LPMofVoid pData) {
    //�����Œǉ������f�[�^�̉��
    m_Motion.Release();
    //�e�̏��������s����
    return CSprite2D::Release(pData);
}