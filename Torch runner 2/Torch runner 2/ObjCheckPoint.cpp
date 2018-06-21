//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjCheckPoint.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCheckPoint::CObjCheckPoint(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//�C�j�V�����C�Y
void CObjCheckPoint::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_pos = 0.0f;
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��
	m_ani_change = 19;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 150, 300, ELEMENT_ITEM, OBJ_CHECK_POINT, 1);
}

//�A�N�V����
void CObjCheckPoint::Action()
{
	//�Q�[�W���������Ă���
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�����i�[���ڂ̑O�ɗ�����
	if (runner->GetCheckTransfer() == true)
	{
		m_time++;
		m_ani_change = 20; //�r��U�艺�낷
	}

	if (m_time > 50)	   //�U�艺�낵�Ă��΂炭�������瑖��o��
	{
		m_pos = 1.0f;      //������ς���
		m_ani_change = 19; //����`��ɕς���

		//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
		if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
		{
			m_ani_frame++;//�t���[����i�߂�
			m_ani_time = 0;
		}
		if (m_ani_frame == 4)//�t���[�����Ō�܂Ői�񂾂�߂�
		{
			m_ani_frame = 0;
		}

		m_vx += 1.0f;
	}

	//�V�[���ړ�����B
	if (m_time > 220)
	{
		((UserData*)Save::GetData())->m_point += (int)gauge->GetGauge() * 100;
		((UserData*)Save::GetData())->m_stage_count += 1;
		
		if (((UserData*)Save::GetData())->m_stage_count == 4)
		{
			Scene::SetScene(new CSceneGameClear());
		}
		else
			Scene::SetScene(new CSceneMain(3));
	}

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll() + 50.0f, m_py + 180.0f);

	HitBox();  //�����蔻��֘A
}

//�`��
void CObjCheckPoint::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py - 55.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 256.0f + m_px + block->GetScroll();
	dst.m_bottom = 256.0f + m_py * 3;

	//�`��
	Draw::Draw(18, &src, &dst, c, 0.0f);

	RECT_F src2; //�`�挳�؂���ʒu
	RECT_F dst2; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src2.m_top = 0.0f;
	src2.m_left = 64.0f + m_ani_frame * 64;
	src2.m_right = 128.0f + m_ani_frame * 64;
	src2.m_bottom = 256.0f;

	//�\���ʒu�̐ݒ�
	dst2.m_top = 0.0f + m_py* 3.0f;
	dst2.m_left = (64.0f -(64.0f * m_pos)) + m_px + block->GetScroll() + 230.0f + m_vx;
	dst2.m_right = (64.0f * m_pos) + m_px + block->GetScroll() + 230.0f + m_vx;
	dst2.m_bottom = 64.0f + m_py * 3.0f;

	//�`��
	Draw::Draw(m_ani_change, &src2, &dst2, c, 0.0f);

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���΂̂��Ƃ��[�[�[�[�[�[�[�[�[�[�[�[

	RECT_F src3; //�`�挳�؂���ʒu
	RECT_F dst3; //�`���\���ʒu

	//�؂���ʒu�̐ݒ� 
	src3.m_top = 1.0f;
	src3.m_left = 0.0f;
	src3.m_right = 64.0f;
	src3.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	if (m_ani_change == 19) //�r��U�艺�낵�Ă��Ȃ�
	{
		if (m_time > 50)
		{
			dst3.m_top = 0.0f + m_py * 3.0f - 10.0f;
			dst3.m_left = 0.0f + m_px + block->GetScroll() + 267.0f + m_vx;
			dst3.m_right = 20.0f + m_px + block->GetScroll() + 267.0f + m_vx;
			dst3.m_bottom = 32.0f + m_py * 3.0f - 10.0f;
		}
		else
		{
			dst3.m_top = 0.0f + m_py * 3.0f - 10.0f;
			dst3.m_left = 0.0f + m_px + block->GetScroll() + 240.0f;
			dst3.m_right = 20.0f + m_px + block->GetScroll() + 240.0f;
			dst3.m_bottom = 32.0f + m_py * 3.0f - 10.0f;
		}

		//�`��
		Draw::Draw(9, &src3, &dst3, c, 0.0f);
	}
	else //�r��U�艺�낵�Ă���
	{
		dst3.m_top = 0.0f + m_py * 3.0f + 18.0f;
		dst3.m_left = 0.0f + m_px + block->GetScroll() + 240.0f;
		dst3.m_right = 20.0f + m_px + block->GetScroll() + 240.0f;
		dst3.m_bottom = 32.0f + m_py * 3.0f + 18.0f;

		//�`��
		Draw::Draw(9, &src3, &dst3, c, 100.0f);
	}

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|���[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�`��J���[���

	RECT_F src4; //�`�挳�؂���ʒu
	RECT_F dst4; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src4.m_top = 0.0f;
	src4.m_left = 0.0f + m_ani_frame * 64;
	src4.m_right = 64.0f + m_ani_frame * 64;
	src4.m_bottom = 320.0f;

	if (m_ani_change == 20)//�r��U�艺�낵�Ă��Ȃ�
	{
		//�\���ʒu�̐ݒ�
		dst4.m_top = 0.0f + m_py* 3.0f + 26.0f;
		dst4.m_left = 0.0f + m_px + block->GetScroll() + 220.0f;
		dst4.m_right = 25.0f + m_px + block->GetScroll() + 220.0f;
		dst4.m_bottom = 25.0f + m_py* 3.0f + 26.0f;

		//�`��
		Draw::Draw(6, &src4, &dst4, c, 100.0f);
	}
	else if (m_time > 50)
	{
		//�\���ʒu�̐ݒ�
		dst4.m_top = 0.0f + m_py* 3.0f - 30.0f;
		dst4.m_left = 0.0f + m_px + block->GetScroll() + 265.0f + m_vx;
		dst4.m_right = 25.0f + m_px + block->GetScroll() + 265.0f + m_vx;
		dst4.m_bottom = 25.0f + m_py* 3.0f  - 30.0f;

		//�`��
		Draw::Draw(6, &src4, &dst4, c, 0.0f);
	}

}

void CObjCheckPoint::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
}