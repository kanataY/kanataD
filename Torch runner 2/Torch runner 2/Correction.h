#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define OUTOFRANGE_UP 277.0f		  //�͈͊O���ǂ������ׂ�l
#define OUTOFRANGE_DOWN 536.0f
#define OUTOFRANGE_UP_PUDDLE 328.0f   //�͈͊O���ǂ������ׂ�l�@�����܂�o�[�W����
#define OUTOFRANGE_DOWN_PUDDLE 536.0f

//�I�u�W�F�N�g�F�Q�[�W
class CObjCorrection : public CObj
{
public:

	~CObjCorrection() {};
	void Init();	//�C�j�V�����C�Y
	float RangeY(float y); //�͈͊O�ɂ���Ƃ��ɂ�����
	float RangeYPuddle(float y); //�͈͊O�ɂ���Ƃ��ɂ����������܂�o�[�W����
	void FireDisplay(float x, float y);   //���𕡐��\��������

private:
	float m_px;		//�ʒu
	float m_py;
	
};