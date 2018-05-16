#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�I�J�}
class CObjOkama : public CObj
{
public:
	CObjOkama(int x, int y);
	~CObjOkama() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //HitBox�֘A
	float GetX() { return m_px; }//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }//m_vx,m_vy�̒l��n��
	float GetVX() { return m_vx; }
	bool  GetHug() { return m_hug; } //�������Ă��邩�ǂ�����n��

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;		//�ړ���
	float m_vy;
	int   m_time;     //�^�C��
	bool m_hug;  //�������������ׂ�ϐ�
	int  m_rebagacha;//���o�K�`��
	int  m_r_time;   //���o�K�`��������̌ジ���鋗���Ɏg��

	int m_time_fire;     //�^�C��
	
	//����n
	bool m_fire_control; //�΂��t�������̐���
	bool m_homing;       //�z�[�~���O����񐔂𐧌�
	bool m_rebagacha_cotrol_r; // R���o�K�`���𐧌�
	bool m_rebagacha_cotrol_l; // L���o�K�`���𐧌�
	bool m_rebagacha_cotrol_u; // U���o�K�`���𐧌�
	bool m_rebagacha_cotrol_d; // D���o�K�`���𐧌�


	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
};
