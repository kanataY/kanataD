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
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 128, 128, ELEMENT_ENEMY, OBJ_TRACK, 1);
}

//�A�N�V����
void CObjTrack::Action()
{
	m_vx = -2.0f;

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

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 128.0f + m_px;
	dst.m_bottom = 128.0f + m_py;

	//�`��
	Draw::Draw(18, &src, &dst, c, 0.0f);
}