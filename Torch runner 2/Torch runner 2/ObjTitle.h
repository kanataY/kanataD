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
	float m_mou_x;	//�}�E�X�̈ʒuX
	float m_mou_y;	//�}�E�X�̈ʒuY

	bool  m_mou_l;	//�}�E�X�̍��{�^�� false:�����Ă��Ȃ� true:�����Ă���
	bool m_key_flag;//�L�[�t���O false:�����Ȃ� true:������
	bool  m_pic_f;	//�w�i���Ō�܂ł��������ǂ��� false:�����ĂȂ� true:������

					//int  key_select;//�Q�[���I���L�[���ǂ��ɋ��邩���ׂ�
	int  m_time;	//���ԊǗ�
	int  m_pic;		//�g���摜�̓o�^�ԍ�1�Ǘ�
};