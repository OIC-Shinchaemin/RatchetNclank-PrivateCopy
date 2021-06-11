#ifndef BASE_CORE_DEFINE_H
#define BASE_CORE_DEFINE_H


#include "Utility.h"


namespace def {
constexpr float kFPS = 60.0f;
constexpr float kDeltaTime = 1.0f / kFPS;
constexpr uint32_t kWindowWidth = 1024;
constexpr uint32_t kWindowHeight = 768;
constexpr float kWindowWidthF = static_cast<float>(def::kWindowWidth);
constexpr float kWindowHeightF = static_cast<float>(def::kWindowHeight);
namespace color_rgba {
static const Mof::CVector4 kBlack = Mof::CVector4(0.0f, 0.0f, 0.0f, 1.0f);
static const Mof::CVector4 kRed = Mof::CVector4(1.0f, 0.0f, 0.0f, 1.0f);
static const Mof::CVector4 kGreen = Mof::CVector4(0.0f, 1.0f, 0.0f, 1.0f);
static const Mof::CVector4 kBlue = Mof::CVector4(0.0f, 0.0f, 1.0f, 1.0f);
static const Mof::CVector4 kCyan = Mof::CVector4(0.0f, 1.0f, 1.0f, 1.0f);
static const Mof::CVector4 kMagenta = Mof::CVector4(1.0f, 0.0f, 1.0f, 1.0f);
static const Mof::CVector4 kYellow = Mof::CVector4(1.0f, 1.0f, 0.0f, 1.0f);
static const Mof::CVector4 kWhite = Mof::CVector4(1.0f, 1.0f, 1.0f, 1.0f);
static const Mof::CVector4 kGray = Mof::CVector4(0.5f, 0.5f, 0.5f, 1.0f);
}
namespace color_rgba_u32 {
static const MofU32 kBlack = def::color_rgba::kBlack.ToU32Color();
static const MofU32 kRed = def::color_rgba::kRed.ToU32Color();
static const MofU32 kGreen = def::color_rgba::kGreen.ToU32Color();
static const MofU32 kBlue = def::color_rgba::kBlue.ToU32Color();
static const MofU32 kCyan = def::color_rgba::kCyan.ToU32Color();
static const MofU32 kMagenta = def::color_rgba::kMagenta.ToU32Color();
static const MofU32 kYellow = def::color_rgba::kYellow.ToU32Color();
static const MofU32 kWhite = def::color_rgba::kWhite.ToU32Color();
static const MofU32 kGray = def::color_rgba::kGray.ToU32Color();
}

struct Transform {
    //! �ʒu
    Mof::CVector3 position;
    //! ��]
    Mof::CVector3 rotate;
    //! �g��
    Mof::CVector3 scale;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Transform() :
        position(),
        rotate(),
        scale(1.0f, 1.0f, 1.0f) {
    }
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�ʒu</param>
    Transform(Mof::CVector3 pos) :
        position(pos),
        rotate(),
        scale(1.0f, 1.0f, 1.0f) {
    }
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�ʒu</param>
    /// <param name="rot">��]</param>
    Transform(Mof::CVector3 pos, Mof::CVector3 rot) :
        position(pos),
        rotate(rot),
        scale(1.0f, 1.0f, 1.0f) {
    }
    Transform(Mof::CVector3 pos, Mof::CVector3 rot, Mof::CVector3 sca) :
        position(pos),
        rotate(rot),
        scale(sca) {
    }
    /// <summary>
    /// �}�g���N�X
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CMatrix44 Matrix(void) {
        Mof::CMatrix44 s, r, t;
        Mof::CQuaternion quat; quat.Rotation(rotate);

        s.Scaling(scale, s);
        quat.ConvertMatrixTranspose(r);
        t.Translation(position, t);

        Mof::CMatrix44 world = s * r * t;
        return world;
    }
};
} // namespace

namespace ratchet {
template <typename...FuncArgs>
class OnEvent : public std::vector<std::pair<std::string, std::function<bool(const FuncArgs...)>>> {
    using OnEventFunc = std::function<bool(const FuncArgs...)>;
    using OnEventPair = std::pair<std::string, OnEventFunc>;
    using super = std::vector<OnEventPair>;
public:
    void Register(const char* key, OnEventFunc func) {
        // �����L�[�ł̓o�^���Ȃ�
        auto it = std::find_if(super::begin(), super::end(), [&](const OnEventPair& pair) {
            return key == pair.first;
        });
        if (it != super::end()) {
            return;
        } // if
        this->push_back(std::make_pair(key, func));
    }
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="val"></param>
    void operator += (OnEventPair val) {
        this->Register(val.first.c_str(), val.second);
    }
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="key"></param>
    void operator -= (const char* key) {
        ut::EraseRemove(*this, [&](const OnEventPair& pair) {
            return pair.first == key;
        });
    }
    /// <summary>
    /// �p�^�[���}�b�`��S�폜
    /// </summary>
    /// <param name="key"></param>
    void RemoveMatch(const char* key) {
        ut::EraseRemove(*this, [&](const OnEventPair& pair) {
            return pair.first.find(key) != std::string::npos;
        });
    }
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name=""></param>
    /// <returns>�C�x���g���ŏ����I���Ȃ�true��Ԃ�</returns>
    bool operator ()(const FuncArgs... args) {
        for (auto& func : *this) {
            if (func.second(args...)) {
                return true;
            } // if
        } // for
        return false;
    }
};
template<class Sender, class Receiver = Sender>
struct Message {
    //! �^�C�v
    std::string type;
    //! ���M��
    std::shared_ptr<Sender> sender;
    //! ��M��
    std::shared_ptr<Receiver> receiver;
    //! �t�^���
    //std::optional<std::any>extra;
    std::any extra;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Message() = default;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="type"></param>
    /// <param name="sender"></param>
    /// <param name="receiver"></param>
    /// <param name="extra"></param>
    Message(const char* type,
            std::shared_ptr<Sender> sender,
            std::shared_ptr<Receiver> receiver,
            std::any extra = NULL) :
        type(type), sender(sender), receiver(receiver), extra(extra) {
    }
};
} // namespace
#endif // !BASE_CORE_DEFINE_H