#pragma once

#include		<memory>
#include		<list>

namespace Behaviour {
//�m�[�h�|�C���^�u������
template < typename T > class INodeExecutor;
template < typename T > using NodeExecutorPtr = std::shared_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorList = std::list<NodeExecutorPtr<T>>;

/** �m�[�h���s�p�N���X */
template < typename T >
class INodeExecutor : public std::enable_shared_from_this<INodeExecutor<T>> {
public:
	/**
	 * @brief		�m�[�h�̏��
	 */
	enum class State {
		Inactive,           //�����s
		Running,            //���s��
		Completed,          //���s�I��
		Incompleted,		//���s���s
	};

	/**
	 * @brief		�m�[�h�̌���
	 */
	enum class Result {
		None,               //�܂����s�O/���s��
		Sucess,             //���s����
		Failure,            //���s���s
	};

	/**
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		Succeeded	���s�̐���
	 *				Failed		���s�̎��s
	 */
	virtual Result Exec(T& actor) = 0;

	/**
	 * @brief		�m�[�h�̎��s��Ԃ�S�ă��Z�b�g����
	 *				��Ԃ�Inactive�ɐݒ肷��
	 */
	virtual void Reset() = 0;

	/**
	 * @brief		�e�̐ݒ�
	 * @param[in]	ptr			�e�A�N�^�[
	 */
	virtual void SetParent(NodeExecutorWeakPtr<T>& ptr) = 0;
};
}