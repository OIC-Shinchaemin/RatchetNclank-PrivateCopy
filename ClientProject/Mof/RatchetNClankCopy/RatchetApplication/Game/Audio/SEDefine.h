#ifndef RATCHET_GAME_AUDIO_SE_DEFINE_H
#define RATCHET_GAME_AUDIO_SE_DEFINE_H


#include <string>

#include <Mof.h>


namespace ratchet::game::audio {
enum class SEType {
};
struct SEEventCommand {
    // ビットフラグやoptionalでもいいかも
    bool play = false;
    bool stop = false;
    bool set_loop = false;
    bool set_volume = false;
    bool loop = false;
    float volume = 1.0f;

    static SEEventCommand Play(void) {
        auto instance = SEEventCommand();
        instance.play = true;
        return instance;
    }
    static SEEventCommand Stop(void) {
        auto instance = SEEventCommand();
        instance.stop = true;
        return instance;
    }
    static SEEventCommand SetLoop(bool loop) {
        auto instance = SEEventCommand();
        instance.set_loop = true;
        instance.loop = loop;
        return instance;
    }
    static SEEventCommand SetVolume(float volume) {
        auto instance = SEEventCommand();
        instance.set_volume= true;
        instance.volume = volume;
        return instance;
    }

};

struct SEEvent {
    using Type = SEType;
    Type type;
    SEEventCommand command;
};
}
#endif // !RATCHET_GAME_AUDIO_SE_DEFINE_H