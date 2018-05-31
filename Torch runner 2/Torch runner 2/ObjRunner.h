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
	float GetX() { return m_px; }						//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }						//m_vx,m_vy�̒l��n��
	float GetVX() { return m_vx; }
	int   GetInvincible() { return m_invincible; }		//���G���Ԃ̒l��n��
	bool  GetHoleFallCon(){ return m_hole_control; }	//���ɗ����Ă������n��
	bool  GetCheckPoint() { return m_check_control; }	//�`�F�b�N�|�C���g�ɓ������Ă��邩�ǂ����̏���n��
	int   GetCheckTime()  { return m_check_time; }		//�`�F�b�N�|�C���g�ɓ������Ă���̃^�C����n���B
	bool  GetCheckTransfer() { return m_check_transfer; }//�`�F�b�N�|�C���g�ɓ��B���ĉ΂������Ă��邩�ǂ�����n��
	bool  GetDeath() { return m_death; }				//�����i�[������ł��邩�ǂ���������B
	void  SetX(float x) { m_px = x; }					//m_px,m_py�̒l���ق���cpp�ł��������悤�ɂ���
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }					//m_vx,m_vy�̒l���ق���cpp�ł��������悤�ɂ���
	void  SetVY(float y) { m_vy = y; }
	void  SetHoleFall(float f) { m_hole_fall += f; } //���ɗ��������`���ς���悤SetHoleFallCon

private:
	float m_px;			//�ʒu
	float m_py;
	float m_vx;			//�ړ��x�N�g��
	float m_vy;
	int   m_invincible; //���G����
	int   m_check_time; //�`�F�b�N�|�C���g�̃^�C���Ǘ�

	//�`��֘A
	float m_hole_fall;  //���ɗ��������̕`�悷��Ƃ����ς���ϐ�

	//����n---------
	bool m_torch_control;			//��������
	int  m_torch_time_control;		//��������
	bool m_puddle_control;			//�����܂萧��
	bool m_smart_control;			//�X�}�z���N����
	bool m_hole_control;			//������
	bool m_check_control;			//�`�F�b�N�|�C���g����
	bool m_check_control_x;			//�`�F�b�N�|�C���g����X
	bool m_homing;                  //���̃����i�[�Ɍ������Ă���
	bool m_check_transfer;			//�`�F�b�N�|�C���g�ɓ��B���ĉ΂������Ă��邩�ǂ���������ϐ�
	bool m_check_s1;				//S1�̃`�F�b�N�|�C���g��ʉ߂������ǂ���������ϐ�
	bool m_death;					//�����i�[�����񂾂Ƃ�

	//�W�����v�n�i��������̂ŏ���or�A��j
	float jamp_memo; //�W�����v���邳���Ɏ�l�����ǂ��ɂ������𒲂ׂ�
	bool m_jamp_control; //�W�����v���Ă��邩�ǂ����𒲂ׂ�i���䂷��j
	bool m_jamp_control_2; //�W�����v���Ă��邩�ǂ����𒲂ׂ�2
	int   m_time;

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	int m_ani_change; //�A�j���[�V�����ύX�ϐ�
};