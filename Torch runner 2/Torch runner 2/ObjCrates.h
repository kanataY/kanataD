#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�ؔ�
class CObjCrates : public CObj
{
public:
	CObjCrates(int x,int y);
	~CObjCrates() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //HitBox�֘A
	float GetX() { return m_px; }						//m_px,m_py�̒l��n��
	float GetY() { return m_py; }

private:
	float m_px;		//�ʒu
	float m_py;
	int m_time;     //�^�C��

	//����n
	bool m_fire_control; //�΂��t�������̐���
}; 
