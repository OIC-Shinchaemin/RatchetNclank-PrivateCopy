#ifndef RATCHET_GAME_AUDIO_BGM_DEFINE_H
#define RATCHET_GAME_AUDIO_BGM_DEFINE_H


#include <string>

#include <Mof.h>


namespace ratchet::game::audio {
enum class BGMType {
    Title,
    Field,
    Battle,
};
struct BGMEventCommand {
    // ビットフラグやoptionalでもいいかも
    bool play = false;
    bool stop = false;
    bool set_loop = false;
    bool set_volume = false;
    bool loop = false;
    float volume = 1.0f;

    static BGMEventCommand Play(void) {
        auto instance = BGMEventCommand();
        instance.play = true;
        return instance;
    }
    static BGMEventCommand Stop(void) {
        auto instance = BGMEventCommand();
        instance.stop = true;
        return instance;
    }
    static BGMEventCommand SetLoop(bool loop) {
        auto instance = BGMEventCommand();
        instance.set_loop = true;
        instance.loop = loop;
        return instance;
    }
    static BGMEventCommand SetVolume(float volume) {
        auto instance = BGMEventCommand();
        instance.set_volume= true;
        instance.volume = volume;
        return instance;
    }

};

struct BGMEvent {
    using Type = BGMType;
    Type type;
    BGMEventCommand command;
};
}
#endif // !RATCHET_GAME_AUDIO_BGM_DEFINE_H