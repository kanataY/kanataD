#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�`�F�b�N�|�C���g
class CObjCheckPoint : public CObj
{
public:
	CObjCheckPoint(int x, int y);
	~CObjCheckPoint() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //�����蔻��֘A
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;			//�ړ��x�N�g��
	float m_vy;
	float m_pos;    //�����ʒu
	int   m_time; //���Ɍ��������̎��ԊǗ�

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	int m_ani_change; //�A�j���[�V�����ύX�ϐ�
};