#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�����i�[
class CObjRunner : public CObj
{
public:
	CObjRunner();
	~CObjRunner(){};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

private:
	float m_px;		//�ʒu
	float m_py;
	float m_vx;
	float m_vy;
};