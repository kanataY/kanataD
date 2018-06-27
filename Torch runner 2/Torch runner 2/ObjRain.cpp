//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRain::CObjRain(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjRain::Init()
{
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;	//�Î~�t���[���������ɂ���
	m_ani_max_time = 10;//�A�j���[�V�����Ԋu��
}

//�A�N�V����
void CObjRain::Action()
{
	//�Q�[�W�̏��������Ă���
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	m_time++; //�^�C����i�߂�

	if (m_time > 250)//��莞�Ԃ����������
	{
		runner->SetRainTime(true);		//�J���~��I���������n��
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
	}
	else
	{
		runner->SetRainTime(false);		//�J���~���Ă���
	}

	//�Q�[�W�����炷
	if (m_time % 50 == 0)
	{
		gauge->SetGauge(1);
	}

	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 2)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}
}

//�`��
void CObjRain::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,0.3f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 800.0f + m_ani_frame * 64;
	src.m_bottom = 800.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 800.0f + m_px;
	dst.m_bottom = 600.0f + m_py;

	//�`��
	Draw::Draw(12 + m_ani_frame, &src, &dst, c, 0.0f);

	//�X�e�[�W�R�Ȃ� �J�𑝂₷
	if (((UserData*)Save::GetData())->m_stage_count == 3)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px - 10.0f;
		dst.m_right = 800.0f + m_px - 10.0f;
		dst.m_bottom = 600.0f + m_py;

		//�`��
		Draw::Draw(12 + m_ani_frame, &src, &dst, c, 0.0f);

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py + 10.0f;
		dst.m_left = 0.0f + m_px;
		dst.m_right = 800.0f + m_px;
		dst.m_bottom = 600.0f + m_py+10.0f;

		//�`��
		Draw::Draw(12 + m_ani_frame, &src, &dst, c, 0.0f);

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px - 10.0f;
		dst.m_right = 800.0f + m_px - 10.0f;
		dst.m_bottom = 600.0f + m_py;

		//�`��
		Draw::Draw(12 + m_ani_frame, &src, &dst, c, 0.0f);
	}
}