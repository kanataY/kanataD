//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjTorch.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjTorch::CObjTorch(float x,float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjTorch::Init()
{
	m_time = 0;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 12, 12, ELEMENT_RUNNER, OBJ_TORCH, 1);
}

//�A�N�V����
void CObjTorch::Action()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	m_px = runner->GetX();
	m_py = runner->GetY();

	m_time++;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 55.0f, m_py + 28.0f);
	if (m_time > 30)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//�G�����L����HitBox�ɍ폜����
	}
}

//�`��
void CObjTorch::Draw()
{
	////-----------�w�i-----------
	////�`��J���[���
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src; //�`�挳�؂���ʒu
	//RECT_F dst; //�`���\���ʒu

	//			//�؂���ʒu�̐ݒ�
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 192.0f;
	//src.m_bottom = 32.0f;

	////�\���ʒu�̐ݒ�
	//dst.m_top = 0.0f + m_py;
	//dst.m_left = 0.0f + m_px;
	//dst.m_right = 192.0f + m_px;
	//dst.m_bottom = 32.0f + m_py;

	////�`��
	//Draw::Draw(3, &src, &dst, c, 0.0f);
}