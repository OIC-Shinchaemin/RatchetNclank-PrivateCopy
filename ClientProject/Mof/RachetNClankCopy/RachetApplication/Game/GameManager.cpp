#include "GameManager.h"

#include "My/Core/Trait.h"
#include "My/Core/Utility.h"
#include "../GameSystem/Save/SaveData.h"
#include "../GameSystem/Save/SaveSystem.h"
#include "../Character/Enemy.h"
#include "../Character/Player.h"


void my::GameManager::AddElement(const std::shared_ptr<my::Actor>& ptr) {
    _game_world.AddActor(ptr);
    _renderer.AddElement(ptr);
}

void my::GameManager::RemoveElement(const std::shared_ptr<my::Actor>& ptr) {
    _game_world.RemoveActor(ptr);
    _renderer.RemoveElement(ptr);
}

void my::GameManager::Collision(void) {
    auto player = _character->GetPosition();

    auto player_sphere = _character->GetSphere();

    for (auto& enemy : _enemies) {
        if (enemy->ContainInRecognitionRange(player)) {
            enemy->SetTarget(_character);
        } // if
        else {
            enemy->SetTarget(nullptr);
        } // else

        if (enemy->GetSphere().CollisionSphere(player_sphere)) {
            enemy->End();
        } // if
    } // for
}

my::GameManager::GameManager() :
    _game_world(),
    _renderer(),
    _game_money(),
    _weapon_system(),
    _quick_change(),
    _stage(),
    _character(),
    _current_weapon() {
}

my::GameManager::~GameManager() {
}

void my::GameManager::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "DeleteRequest") {
        _delete_actors.push_back(ptr);
    } // if
}

bool my::GameManager::Initialize(void) {
    _stage.Initialize();

    _game_money = std::make_unique<my::GameMoney>();
    _weapon_system = std::make_shared<my::WeaponSystem>();
    _quick_change = std::make_shared<my::QuickChangeSystem>();
    _character = std::make_shared<Player>();

    auto save_data = my::SaveData();
    my::SaveSystem().Fetch(save_data);

    _game_money->Initialize(save_data.GetMoney());
    _weapon_system->Initialize(save_data);
    _quick_change->Initialize({}, _weapon_system);
    _character->Initialize({});

    _current_weapon = _weapon_system->GetWeapon("OmniWrench");

    auto transform = def::Transform();
    transform.position = Mof::CVector3(4.0f, 0.0f, 0.0f);
    // Enemy‚ğ‰Šú‰»‚·‚é‚½‚ß‚ÉƒLƒƒƒbƒVƒ…
    auto temp = ut::MakeSharedWithRelease<my::Enemy>();
    temp->AddObserver(shared_from_this());
    temp->Initialize(transform);
    _enemies.push_back(temp);

    this->AddElement(_character);
    this->AddElement(temp);
    return true;
}

bool my::GameManager::Input(void) {
    _game_money->Input();
    _quick_change->Input();

    if (::g_pInput->IsKeyPush(MOFKEY_1)) {
        _current_weapon = _weapon_system->GetWeapon("BombGlove");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_2)) {
        _current_weapon = _weapon_system->GetWeapon("Pyrocitor");
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_3)) {
        _current_weapon = _weapon_system->GetWeapon("OmniWrench");
    } // if

    _game_world.Input();
    return true;
}

bool my::GameManager::Update(float delta_time) {
    for (auto& ptr : _delete_actors) {
        this->RemoveElement(ptr);
    } // for
    _delete_actors.clear();
    

    _quick_change->Update();
    _stage.Update();

    _game_world.Update(delta_time);
    _current_weapon->Update(delta_time);
    this->Collision();
    return true;
}

bool my::GameManager::Render(void) {
    _renderer.Render();

    _current_weapon->Render();

    _stage.Render();
    _quick_change->Render();

    _game_money->Render();
    return true;
}

bool my::GameManager::Release(void) {
    _character->Release();
    _stage.Release();

    //! save
    std::vector<std::string> weapon;
    _weapon_system->CreateAvailableWeaponNames(weapon);
    auto save_param = my::SaveDataParam(_game_money->GetValue(), weapon);
    my::SaveSystem().Save(save_param);

    _quick_change->Release();
    return true;
}