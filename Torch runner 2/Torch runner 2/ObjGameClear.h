#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_x; //��l����X�ʒu
	float m_y;	//��l����Y�ʒu
	float m_vx;//X�����̈ړ��x�N�g��
	float m_vy;//Y�����̈ړ��x�N�g��
	float m_sppde_power;//�X�s�[�h�p���[
	int m_time; //���ԊǗ�
};
