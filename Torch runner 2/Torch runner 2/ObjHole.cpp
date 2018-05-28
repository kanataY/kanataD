//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjPuddle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

///////////////////////////////////////////////////////////����܌�
//�R���X�g���N�^
CObjHole::CObjHole(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 64;
	m_ry = y / 64;
}

//�C�j�V�����C�Y
void CObjHole::Init()
{
	m_drow_down = 1;
	m_map_con = false;
	m_hole_fall = false;

	for (int j = 1; j < 10; j++)  //�}�b�v��Y�̒l�����T��
	{
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//�}�b�v�ԍ�������Ă���@
		if (block->GetMap(m_rx, m_ry + j) == 3)//�������ɂ���Ȃ瑝�₷
		{
			m_drow_down++;
		}

		if (block->GetMap(m_rx, m_ry - j) == 3)//������ɂ���Ȃ牺�ɂ���̂�����
		{
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}
	}

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 30, 35 * (float)m_drow_down, ELEMENT_ITEM, OBJ_HOLE, 1);
}

//�A�N�V����
void CObjHole::Action()
{
	////�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYPuddle(m_py); //Y�̈ʒu���������������璲������

	//�����i�[�����ɗ����鎞�Ɏg��

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 18.0f + block->GetScroll(), m_py + 17.0f * m_drow_down);
	
	HitBox(); //�����蔻��֘A

	//��ʊO�ɍs���Ǝ���
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

}

//�`��
void CObjHole::Draw()
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
	src.m_bottom = 64.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f * m_drow_down + m_py;

	//�`��
	Draw::Draw(15, &src, &dst, c, 0.0f);
}

//�����蔻��֘A
void CObjHole::HitBox()
{
	//HitBox�̏��
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�����i�[�Ɠ������Ă���ꍇ
	if (runner->GetInvincible() < 0) //���G���ԂłȂ���Δ����݂���B
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//�����i�[�̑��̈ʒu�����ɂ������ĂȂ��ꍇ�͔�����Ȃ���
			if (m_py + (40.0f * ((float)m_drow_down - 1)) > runner->GetY())
			{
				m_hole_fall = true;//����
			}

			if (m_hole_fall == true) //�����i�[�����ɗ����Ă���ꍇ
			{
				runner->SetHoleFall(1.0f);									 //�����i�[�̂ق��ŕ`�������������
				runner->SetX(m_px + block->GetScroll() + 15.0f);			 //�����i�[�̈ʒu�����̐^�񒆂ɂ���悤�ɂ���

				if (m_drow_down >= 4)//�����l�������傤�̑傫���Ȃ�
					runner->SetY(m_py + 35.0f   * ((float)m_drow_down - 1)); //�����i�[�̂��ʒu��^�񒆂ɒ�������
				else
					runner->SetY(m_py + 50.0f * ((float)m_drow_down - 1));
			}
		}
		else
		{
			m_hole_fall = false;
		}
	}
}