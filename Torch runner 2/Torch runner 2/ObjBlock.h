#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock();
	~CObjBlock() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

private:
	float m_px;		//�ʒu
	float m_py;
	float m_bx1;     //�w�i�̓����l
	float m_bx2;     //�w�i�̓����l2
	
	float m_scroll; //�X�N���[���ʒu
};