#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�Q�[�W
class CObjCorrection : public CObj
{
public:

	~CObjCorrection() {};
	void Init();	//�C�j�V�����C�Y
	float RangeY(float y); //�͈͊O�ɂ���Ƃ��ɂ�����

private:
	float m_px;		//�ʒu
	float m_py;
};