//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjFire.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFire::CObjFire(float x,float y ,bool b)
{
	m_px = x;
	m_py = y;
	m_okama_hit = b;
}

//�C�j�V�����C�Y
void CObjFire::Init()
{
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 4; //�A�j���[�V�����Ԋu��

	//HitBox
	if(m_okama_hit == false)
		Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_NULL, OBJ_FIRE, 1);
}

//�A�N�V����
void CObjFire::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	m_time++; //�^�C����i�߂�

	//HitBox�̈ʒu�̕ύX
	if (m_okama_hit == false)
	{
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py);
	}

	if (m_time > 101)//��莞�Ԃ����������
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		if (m_okama_hit == false)
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 5)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}

	

}

//�`��
void CObjFire::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f +m_ani_frame * 64;
	src.m_bottom = 320.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py - 10.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll() - 10.0f;
	dst.m_right = 50.0f + m_px + block->GetScroll() -10.0f;
	dst.m_bottom = 50.0f + m_py -10.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + 30.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll() + 10.0f;
	dst.m_right = 50.0f + m_px + block->GetScroll() + 10.0f;
	dst.m_bottom = 50.0f + m_py + 30.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + 12.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll() + 35.0f;
	dst.m_right = 50.0f + m_px + block->GetScroll() + 35.0f;
	dst.m_bottom = 50.0f + m_py + 12.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);
}