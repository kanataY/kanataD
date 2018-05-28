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

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 124, 300, ELEMENT_ITEM, OBJ_CHECK_POINT, 1);
}

//�A�N�V����
void CObjCheckPoint::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

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
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 256.0f;

	//�\���ʒu�̐ݒ�
	dst2.m_top = 0.0f + m_py* 3.0f;
	dst2.m_left = 64.0f + m_px + block->GetScroll() + 230.0f;
	dst2.m_right = 0.0f + m_px + block->GetScroll() + 230.0f;
	dst2.m_bottom = 64.0f + m_py * 3.0f;

	//�`��
	Draw::Draw(19, &src2, &dst2, c, 0.0f);
}

void CObjCheckPoint::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr) //�����i�[�Ɠ������Ă���
	{
		;
	}
}