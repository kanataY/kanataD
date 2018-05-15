//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "Correction.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjCorrection::Init()
{
	m_py = 0.0f;
	m_px = 0.0f;
}

//�I�u�W�F�N�g���������Ƃ���Y��������͈͂��O�����������璲������
float CObjCorrection::RangeY(float y)
{

	if (y > OUTOFRANGE_DOWN)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_DOWN;
	else if (y < OUTOFRANGE_UP)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_UP;

	return y;
}

//���𕡐��\��������
void CObjCorrection::FireDisplay(float x, float y)
{
	//��
	CObjFire* fi = new CObjFire(x - 10.0f , y -10.0f);
	Objs::InsertObj(fi, OBJ_FIRE, 20);
	//��2
	CObjFire* fi2 = new CObjFire(x + 30.0f, y + 10.0f);
	Objs::InsertObj(fi2, OBJ_FIRE, 20);
	//��3
	CObjFire* fi3 = new CObjFire(x + 12.0f, y + 35.0f);
	Objs::InsertObj(fi3, OBJ_FIRE, 20);
}