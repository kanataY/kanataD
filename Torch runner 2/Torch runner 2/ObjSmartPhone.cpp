//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSmartphone.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSmartphone::CObjSmartphone(int x, int y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjSmartphone::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_time = 0;
}

//�A�N�V����
void CObjSmartphone::Action()
{
	m_time++;
	if (m_time < 60)  //60�t���[���ɂȂ�܂ł͓����Ȃ�
		;
	if (m_time > 60 && m_time < 120)//���Ɉړ�
	{
		m_vx += 0.25f;
		m_vy += 0.25f;
	}
	if (m_time > 120 && m_time < 240)//��Ɉړ�
	{
		m_vx += 0.25f;
		m_vy += -0.25f;
	}
	if (m_time > 240 && m_time < 300)//���Ɉړ�
	{
		m_vx += 0.25f;
		m_vy += 0.25f;
	}
	if(m_time > 300)//���[�v������
		m_time = 60;
	

	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�`��
void CObjSmartphone::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 256.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(5, &src, &dst, c, 0.0f);
}