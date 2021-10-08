#ifndef RATCHET_ACTOR_ACTOR_DEFINE_H
#define RATCHET_ACTOR_ACTOR_DEFINE_H


namespace ratchet::actor {
enum class ActorState {
	Active, // ���́A�X�V�A�`�悷��
	Inactive, // ���́A�X�V�A�`�悵�Ȃ�
	Sleep, // ���͂��Ȃ��A �X�V����A�`�悷��
	Pause, // ���͂��Ȃ��A�X�V���Ȃ��A�`�悷��
	Hide, // ���͂���A�X�V����A�`�悵�Ȃ�
	End // �폜
};
}
#endif // !RATCHET_ACTOR_ACTOR_DEFINE_H