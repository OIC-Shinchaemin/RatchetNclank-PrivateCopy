#include "Stage.h"
#include "JsonStageParser.h"

/// <summary>
/// �ÓI�ȃX�e�[�W���b�V���̐���
/// </summary>
/// <returns>true : ����, false : ������</returns>
bool Stage::CreateStaticStageMesh(void) {
    // �ÓI�I�u�W�F�N�g���Ȃ���Γ����蔻��p�̃��b�V���͐������Ȃ�
    if (_static_object_array.size() <= 0) {
        return false;
    }
    // ���b�V���̐���
    MeshPtr stage_mesh = std::make_shared<CMeshContainer>();
    for (auto& object : _static_object_array) {
        // �����ꃁ�b�V���o�^���Ă��Ȃ��I�u�W�F�N�g������Βe��
        // �����蔻��̐ݒ�����Ă��Ȃ��I�u�W�F�N�g���e��
        if (object->GetMeshNo() < 0 || !object->IsCollisionEnable()) {
            continue;
        }
        const int index = _copy_tmp_array.GetArrayCount();
        _copy_tmp_array.Add(_mesh_array[object->GetMeshNo()]->CreateCopyObject());
        LPMeshContainer mesh_tmp   = _copy_tmp_array[index];
        const int       mesh_count = mesh_tmp->GetMeshCount();
        for (int i = 0; i < mesh_count; i++) {
            // �I�u�W�F�N�g�̊g��A��]�ɍ��킹�ăW�I���g���̍Čv�Z
            const int geo_count = mesh_tmp->GetGeometryCount();
            for (int j = 0; j < geo_count; j++) {
                CMatrix44& matrix = mesh_tmp->GetMesh(i)->GetGeometry(j)->GetMatrix();
            
                // ���݂̃f�[�^���擾
                CVector3 scale, rotate, trans;
                matrix.GetScaling(scale);
                matrix.GetRotation(rotate);
                matrix.GetTranslation(trans);

                // �Čv�Z
                CMatrix44 scale_, rotate_, trans_;
                scale_.Scaling(scale * object->GetScale());
                trans_.Translation(trans * object->GetScale());
                rotate_.RotationZXY(object->GetRotate());
                trans_ *= rotate_;
                matrix  = scale_ * trans_;
            }
            // �Čv�Z��̃��b�V����o�^
            stage_mesh->GetMesh()->Add(std::move(mesh_tmp->GetMesh(i)));
        }
    }
    // �ÓI�I�u�W�F�N�g�������Ă���������蔻������Ȃ��ꍇ���b�V���̒ǉ��͂��Ȃ�
    if (stage_mesh->GetMesh()->GetArrayCount() <= 0) {
        return false;
    }
    // ���b�V���z��̍Ō�ɒǉ�����
    stage_mesh->SetName("static_stage_mesh");
    //stage_mesh->Save("static_stage_mesh.mom");
    _mesh_array.push_back(std::move(stage_mesh));
    return true;
}

/// <summary>
/// �X�e�[�W�̓ǂݍ���
/// </summary>
/// <param name="path">�X�e�[�W�f�[�^�t�@�C���p�X</param>
/// <returns>true : ����, false : �G���[</returns>
bool Stage::Load(const std::string& path) {
    // �p�[�T�[�̏���
    ParseData parse_data;
    parse_data.mesh_array_pointer          = &_mesh_array;
    parse_data.static_object_array_pointer = &_static_object_array;
    parse_data.enemy_spawn_array_pointer   = &_enemy_spawn_array;
    StageParserPtr parser = nullptr;

    // �g���q�̎擾
    int length      = path.find_last_of('.');
    std::string ext = path.substr(length);

    // �p�[�T�[�̑I��
    if (ext == ".json") {
        parser = std::make_shared<JsonStageParser>();
    }
    // �p�[�X�ł��Ȃ��g���q
    else {
        return false;
    }

    // �ǂݍ���
    if (parser->Load(path, parse_data) != TRUE) {
        return false;
    }

    // �ÓI�I�u�W�F�N�g�̔���p���b�V������
    _create_static_stage_mesh = CreateStaticStageMesh();

    return true;
}

/// <summary>
/// ������
/// </summary>
void Stage::Initialize(void) {

}

/// <summary>
/// �X�V
/// </summary>
void Stage::Update(void) {

}

/// <summary>
/// �`��
/// </summary>
void Stage::Render(void) {
    for (const auto& it : _static_object_array) {
        const int mesh_no = it->GetMeshNo();
        if (mesh_no < 0) {
            continue;
        }
        _mesh_array[mesh_no]->Render(it->GetWorldMatrix());
    }
}

/// <summary>
/// ���
/// </summary>
void Stage::Release(void) {

    // ����p���b�V���̎蓮���
    if (_create_static_stage_mesh) {
        for (int i = 0; i < _copy_tmp_array.GetArrayCount(); i++) {
            MOF_SAFE_DELETE(_copy_tmp_array[i]);
        }
        const int tail = (_mesh_array.size() - 1);
        for (int i = 0; i < _mesh_array[tail]->GetMeshCount(); i++) {
            _mesh_array[tail]->GetMesh()->SetData(nullptr, i);
        }
        _mesh_array[tail]->GetMesh()->ReSize(0);
        _mesh_array[tail] = nullptr;
    }

    for (auto& it : _mesh_array) {
        if (it) {
            it->Release();
            it = nullptr;
        }
    }
    _mesh_array.clear();
    _static_object_array.clear();
    _static_object_array.clear();
}

/// <summary>
/// �ÓI�ȃX�e�[�W���b�V���𐶐��������̃t���O�擾
/// </summary>
/// <returns>�ÓI�ȃX�e�[�W���b�V���𐶐��������̃t���O</returns>
bool Stage::IsCreateStaticStageMesh(void) const {
    return _create_static_stage_mesh;
}

/// <summary>
/// �ÓI�ȃX�e�[�W���b�V���̎擾
/// </summary>
/// <returns>�������Ă��Ȃ��ꍇ nullptr ���Ԃ�</returns>
MeshPtr Stage::GetStaticStageMesh(void) {
    if (_create_static_stage_mesh) {
        return _mesh_array.back();
    }
    return nullptr;
}

/// <summary>
/// �G�̏o���ʒu�z��̎擾
/// </summary>
/// <returns>�G�̏o���ʒu�z��</returns>
EnemySpawnArray& Stage::GetEnemySpawnArray(void) {
    return _enemy_spawn_array;
}
