#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle : public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_key_flag;//1:�X�e�[�W�Z���N�g2:�����L���O3:�^�C�g���ɖ߂�4:�������
	bool m_key_control;//�L�[�̐���p
	int m_key_control_time;//�L�[�̐���̃^�C��
	bool m_enter_flag;//�G���^�[���������ς̎��̃t���O
	int m_enter_flag_time;//�G���^�[�L�[�̉����Ă�Ƃ��̎��Ԃ��v������ϐ�

};