#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�}�z���N
class CObjSmartphone : public CObj
{
public:
	CObjSmartphone(int x, int y);
	~CObjSmartphone() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;		//�ړ���
	float m_vy;
	int   m_time;     //�^�C��
	bool  m_middle;  //�^�񒆂ɂ��Ȃ�������ׂ�ϐ�
};
