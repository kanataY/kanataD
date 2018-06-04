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

CObjCorrection::CObjCorrection()
{

}

//�C�j�V�����C�Y
void CObjCorrection::Init()
{
	m_py = 0.0f;
	m_px = 0.0f;
	m_screen_out = false;
	m_hole_control = false;
}

void CObjCorrection::Action()
{

}

void CObjCorrection::Draw()
{

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

//�I�u�W�F�N�g���������Ƃ���Y��������͈͂��O�����������璲�����鐅���܂�o�[�W����
float CObjCorrection::RangeYPuddle(float y)
{

	if (y > OUTOFRANGE_DOWN_PUDDLE)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_DOWN_PUDDLE;
	else if (y < OUTOFRANGE_UP_PUDDLE)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_UP_PUDDLE;

	return y;
}

//����\��������@��
void CObjCorrection::FireDisplayCrates(float x, float y)
{
	//��
	CObjFire* fi = new CObjFire(x , y , 0);
	Objs::InsertObj(fi, OBJ_FIRE, 999);

}

//����\��������
void CObjCorrection::FireDisplay(float x, float y)
{
	//��
	CObjFire* fi = new CObjFire(x, y, 1);
	Objs::InsertObj(fi, OBJ_FIRE, 999);
}

//��ʊO�ɍs���Ə����鏈��
bool CObjCorrection::Screen_Out(float x)
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//��ʊO�Ȃ�true��Ԃ�
	if (x + block->GetScroll() < -50)
	{
		return true;
	}

	return false;
}