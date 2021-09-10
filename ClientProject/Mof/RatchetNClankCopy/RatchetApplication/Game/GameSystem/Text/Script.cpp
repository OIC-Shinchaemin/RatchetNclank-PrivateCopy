#include	"Script.h"

//�R�}���h��͕������`
const char* gScriptCommand[] = {
    "text",
    "sprite",
    "setpos",
    "setshow",
    "label",
    "jump",
    "next",
    "select",
    "flag",
    "if",

    "",
};

//���Z�q��͕������`
const char* gScriptOp[] = {
    "+",
    "-",
    "*",
    "/",
    "=",

    "",
};

//���Z�q��͕������`
const char* gScriptCmp[] = {
    ">",
    ">=",
    "=",
    "!",
    "<=",
    "<",

    "",
};

/**
 * ������̐擪�ƌ�납��󔒂���s�����𖳂���
 *
 * ����
 * [in]			s				�Ώە�����
 */
char* Trim(char* s) {
    //�����̕����񂪂Ȃ�
    if (!s) 	{
        return NULL;
    }
    //������̌�납��󔒈ȊO�����������̈ʒu��\0�i�I�[�j��ݒ肷��
    int l = strlen(s);
    while (--l >= 0) 	{
        if (s[l] != '\t' && s[l] != '\r' && s[l] != '\n' && s[l] != ' ') 		{
            break;
        }
    }
    s[l + 1] = '\0';
    //�擪����󔒈ȊO���������ʒu�̃|�C���^��Ԃ�
    int p = 0;
    while (p < l) 	{
        if (s[p] != '\t' && s[p] != '\r' && s[p] != '\n' && s[p] != ' ') 		{
            return &s[p];
        }
        p++;
    }
    return s;
}

/**
 * �R���X�g���N�^
 *
 */
CScript::CScript() :
    m_FileBuffer(NULL),
    m_CommandList() {
    memset(m_FileName, 0, MAX_PATH);
}

/**
 * �f�X�g���N�^
 *
 */
CScript::~CScript() {
}

/**
 * �ǂݍ���
 * �X�N���v�g�t�@�C����ǂݍ���ŉ�͂������Ȃ�
 *
 * ����
 * [in]			name			�ǂݍ��݃t�@�C����
 */
bool CScript::Load(const char* name) {
    //�e�L�X�g�t�@�C�����J��
    if (!LoadTextFile(name)) 	{
        return false;
    }

    //�X�N���v�g�̉�͂��s��
    char* fb = m_FileBuffer;
    while (TRUE) 	{
        //�w��̍s�̍ŏ��́C�܂ł��R�}���h�̎w��
        char* cmd = strtok(fb, ",");
        fb = NULL;
        if (!cmd) 		{
            break;
        }
        //�R�}���h�̑O��ɋ󔒂Ȃǂ�����Ȃ珜��������
        cmd = Trim(cmd);
        //�R�}���h�̎���
        int sCmd = 0;
        for (sCmd = 0; sCmd < CMD_COUNT && stricmp(cmd, gScriptCommand[sCmd]) != 0; sCmd++);
        //�R�}���h�̉��
        ParseCommand(sCmd);
    }
    return true;
}

/**
 * �R�}���h�̉��
 *
 * ����
 * [in]			sCmd			�R�}���h�̃^�C�v
 */
void CScript::ParseCommand(int sCmd) {
    //�R�}���h�ɕK�v�ȃp�����[�^�̉��
    switch (sCmd) 	{
        case CMD_TEXT:				//�e�L�X�g�̕\���R�}���h
            TextCommand();
            break;
        case CMD_SPRITE:			//�X�v���C�g�̍쐬�R�}���h
            SpriteCommand();
            break;
        case CMD_SETPOS:			//�X�v���C�g�̍��W�ݒ�R�}���h
            SetPosCommand();
            break;
        case CMD_SETSHOW:			//�X�v���C�g�̕\���ݒ�R�}���h
            SetShowCommand();
            break;
        //����̈����̂��߃R�}���h��͂����ʉ�
        case CMD_LABEL:				//���x���ݒ�R�}���h
        case CMD_JUMP:				//�W�����v�R�}���h
        case CMD_NEXT:				//�t�@�C���ύX�R�}���h
            NameCommand(sCmd);
            break;
        case CMD_SELECT:			//�I�����R�}���h
            SelectCommand();
            break;
        case CMD_FLAG:				//�t���O����R�}���h
            FlagCommand();
            break;
        case CMD_IF:				//����R�}���h
            IfCommand();
            break;
        default:					//��`����Ă��Ȃ��R�}���h
            break;
    }
}

/**
 * �e�L�X�g�R�}���h�̉��
 *
 */
void CScript::TextCommand(void) {
    TEXTCOMMAND* pCmd = new TEXTCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->px = atof(pstr);
    pstr = strtok(NULL, ",");
    pCmd->py = atof(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Text, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * �X�v���C�g�R�}���h�̉��
 *
 */
void CScript::SpriteCommand(void) {
    SPRITECOMMAND* pCmd = new SPRITECOMMAND();
    char* pstr = strtok(NULL, ",");
    strcpy(pCmd->Name, Trim(pstr));
    pstr = strtok(NULL, ";");
    strcpy(pCmd->FName, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * ���W�ݒ�R�}���h�̉��
 *
 */
void CScript::SetPosCommand(void) {
    SETPOSCOMMAND* pCmd = new SETPOSCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->px = atof(pstr);
    pstr = strtok(NULL, ",");
    pCmd->py = atof(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * �\���ύX�R�}���h�̉��
 *
 */
void CScript::SetShowCommand(void) {
    SETSHOWCOMMAND* pCmd = new SETSHOWCOMMAND();
    char* pstr = strtok(NULL, ",");
    Trim(pstr);
    if (stricmp(pstr, "true") == 0) 	{
        pCmd->bShow = true;
    }
    else if (stricmp(pstr, "false") == 0) 	{
        pCmd->bShow = false;
    }
    else 	{
        pCmd->bShow = atoi(pstr);
    }
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * ���O�w��n�R�}���h�̉��
 *
 * ����
 * [in]			sCmd			�R�}���h�̃^�C�v
 */
void CScript::NameCommand(int sCmd) {
    NAMECOMMAND* pCmd = new NAMECOMMAND(sCmd);
    char* pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * �I���R�}���h�̉��
 *
 */
void CScript::SelectCommand(void) {
    SELECTCOMMAND* pCmd = new SELECTCOMMAND();
    char* pstr = strtok(NULL, ",");
    strcpy(pCmd->Name, Trim(pstr));
    pstr = strtok(NULL, ",");
    pCmd->Count = atoi(pstr);
    pCmd->pItem = (char**)malloc(sizeof(char*) * pCmd->Count);
    pCmd->pLabel = (char**)malloc(sizeof(char*) * pCmd->Count);
    for (int i = 0; i < pCmd->Count; i++) 	{
        //�I�𕶎���ǂݍ���
        pstr = strtok(NULL, ",");
        pstr = Trim(pstr);
        pCmd->pItem[i] = (char*)malloc(strlen(pstr) + 1);
        strcpy(pCmd->pItem[i], pstr);
        //�ړ��惉�x���ǂݍ���
        //�Ō�̃��x���̂݋�؂肪,����;�ɕύX
        pstr = strtok(NULL, ((i == pCmd->Count - 1) ? ";" : ","));
        pstr = Trim(pstr);
        pCmd->pLabel[i] = (char*)malloc(strlen(pstr) + 1);
        strcpy(pCmd->pLabel[i], pstr);
    }
    pCmd->Select.Create(pCmd->Name, pCmd->pItem, pCmd->Count);
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * �t���O�R�}���h�̉��
 *
 */
void CScript::FlagCommand(void) {
    FLAGCOMMAND* pCmd = new FLAGCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->No = atoi(pstr);
    pstr = strtok(NULL, ",");
    Trim(pstr);
    for (pCmd->Op = 0; pCmd->Op < OP_COUNT && strcmp(pstr, gScriptOp[pCmd->Op]) != 0; pCmd->Op++);
    pstr = strtok(NULL, ";");
    pCmd->Value = atoi(pstr);
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * IF�R�}���h�̉��
 *
 */
void CScript::IfCommand(void) {
    IFCOMMAND* pCmd = new IFCOMMAND();
    char* pstr = strtok(NULL, ",");
    pCmd->No = atoi(pstr);
    pstr = strtok(NULL, ",");
    Trim(pstr);
    for (pCmd->Op = 0; pCmd->Op < CMP_COUNT && strcmp(pstr, gScriptCmp[pCmd->Op]) != 0; pCmd->Op++);
    pstr = strtok(NULL, ",");
    pCmd->Value = atoi(pstr);
    pstr = strtok(NULL, ";");
    strcpy(pCmd->Name, Trim(pstr));
    m_CommandList.Add((COMMAND**)&pCmd);
}

/**
 * �ǂݍ���
 * �e�L�X�g�t�@�C����ǂݍ���
 *
 * ����
 * [in]			name			�ǂݍ��݃t�@�C����
 */
bool CScript::LoadTextFile(const char* name) {
    //�e�L�X�g�t�@�C�����J��
    FILE* fp = fopen(name, "rt");
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
    m_FileBuffer = (char*)malloc(fSize + 1);
    //�t�@�C����S�ăo�b�t�@�ɓǂݍ���
    //�����Ŏ��ۂɓǂݍ��߂��T�C�Y�𒲂ׂĂ��̏I�[��\0�����
    fSize = fread(m_FileBuffer, 1, fSize, fp);
    m_FileBuffer[fSize] = '\0';
    //�t�@�C�����̕ۑ�
    strcpy(m_FileName, name);
    //�t�@�C�������
    fclose(fp);
    return true;
}

/**
 * ���
 *
 */
void CScript::Release(void) {
    if (m_FileBuffer) 	{
        free(m_FileBuffer);
        m_FileBuffer = NULL;
    }
    m_CommandList.Release();
}