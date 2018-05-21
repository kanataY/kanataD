#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�����i�[
class CObjRunner : public CObj
{
public:
	CObjRunner();
	~CObjRunner() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //�����蔻��֘A
	float GetX() { return m_px; }//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vy�̒l��n��
	float GetVX() { return m_vx; }
	void  SetX(float x) { m_px = x; }//m_px,m_py�̒l���ق���cpp�ł��������悤�ɂ���
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }//m_vx,m_vy�̒l���ق���cpp�ł��������悤�ɂ���
	void  SetVY(float y) { m_vy = y; }

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;		//�ړ��x�N�g��
	float m_vy;

	//����n---------
	bool m_torch_control;   //��������
	int  m_torch_time_control;   //��������
	bool m_puddle_control;  //�����܂萧��
	bool m_smart_control;  //�X�}�z���N����

	//�W�����v�n�i��������̂ŏ���or�A��j
	float qaajamp_memo;
	float jamp_memo; //�W�����v���邳���Ɏ�l�����ǂ��ɂ������𒲂ׂ�
	bool m_jamp_control; //�W�����v���Ă��邩�ǂ����𒲂ׂ�i���䂷��j
	int   m_time;

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	int m_ani_change; //�A�j���[�V�����ύX�ϐ�
};