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

private:
	float m_px;		//�ʒu
	float m_py;
}; 
