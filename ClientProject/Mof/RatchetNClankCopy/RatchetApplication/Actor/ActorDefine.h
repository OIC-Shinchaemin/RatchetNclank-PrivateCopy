#ifndef RATCHET_ACTOR_ACTOR_DEFINE_H
#define RATCHET_ACTOR_ACTOR_DEFINE_H


namespace ratchet::actor {
enum class ActorState {
	Active, // 入力、更新、描画する
	Inactive, // 入力、更新、描画しない
	Sleep, // 入力しない、 更新する、描画する
	Pause, // 入力しない、更新しない、描画する
	Hide, // 入力する、更新する、描画しない
	End // 削除
};
}
#endif // !RATCHET_ACTOR_ACTOR_DEFINE_H