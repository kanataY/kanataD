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

	if (y > 536.0f)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
		return 536.0f;
	else if (y < 277.0f)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return 277.0f;

	return y;
}