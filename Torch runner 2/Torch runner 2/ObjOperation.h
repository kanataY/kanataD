#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjOperation : public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_scene_flag;//�摜�ύX�p �@0:������� 1:�ڂ��̐���
	bool m_enter_control;//�G���^�[�L�[�̐���p�̃t���O
	bool m_zkey_control; //Z�L�[�̐���p�̃t���O
	bool m_scene_start_control;//��������ɔ�񂾎���scene_flag��1�ɂȂ�̂�h���ϐ�
};