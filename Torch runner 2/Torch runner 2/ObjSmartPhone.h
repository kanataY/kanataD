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
	void HitBox();  //HitBox�֘A
	float GetX() { return m_px; }//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vy�̒l��n��
	float GetVX() { return m_vx; }

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;		//�ړ���
	float m_vy;
	int   m_time;     //�^�C��
	bool  m_middle;  //�^�񒆂ɂ��Ȃ�������ׂ�ϐ�

	int m_time_fire;     //�^�C��

	//����n
	bool m_fire_control; //�΂��t�������̐���

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
};
