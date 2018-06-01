//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjTrack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjTrack::CObjTrack(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;

}

//�C�j�V�����C�Y
void CObjTrack::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_ani_time = 0; 
	m_ani_frame = 0;		//�Î~�t���[���������ɂ���
	m_ani_max_time = 2;		//�A�j���[�V��������Ԋu�ő�l
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 128, 128, ELEMENT_ENEMY, OBJ_TRACK, 1);
}

//�A�N�V����
void CObjTrack::Action()
{
	//�ړ����x
	m_vx = -6.0f;

	//�A�j���[�V����---------------------------------------------------
	m_ani_time++;
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}
	//-------------------------------------------------------------------




	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	HitBox(); //HitBox�֘A
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�`��
void CObjTrack::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 128;
	src.m_right = 128.0f + m_ani_frame * 128;
	src.m_bottom = 512.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 128.0f + m_px + block->GetScroll();
	dst.m_bottom = 128.0f + m_py;

	//�`��
	Draw::Draw(21, &src, &dst, c, 0.0f);
}