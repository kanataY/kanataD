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

//�R���X�g���N�^
CObjPuddle::CObjPuddle(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 64;
	m_ry = y / 64;
}

//�C�j�V�����C�Y
void CObjPuddle::Init()
{
	m_drow_down = 1;
	m_map_con = false;
	
	for (int j = 1; j < 10; j++)  //�}�b�v��Y�̒l�����T��
	{
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//�}�b�v�ԍ�������Ă���@
		if (block->GetMap(m_rx, m_ry + j) == 3)//�����܂肪���ɂ���Ȃ瑝�₷
		{
			m_drow_down++;
		}

		if (block->GetMap(m_rx, m_ry - j) == 3)//�����܂肪��ɂ���Ȃ牺�ɂ���̂�����
		{
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}
	}
	
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 55, 45 * (float)m_drow_down, ELEMENT_ITEM, OBJ_PUDDLE, 1);
}

//�A�N�V����
void CObjPuddle::Action()
{
	////�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYPuddle(m_py); //Y�̈ʒu���������������璲������

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 5.0f + block->GetScroll(), m_py + 8.0f * m_drow_down);

	HitBox();

	//��ʊO�ɍs���Ǝ���
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

}

//�`��
void CObjPuddle::Draw()
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
	Draw::Draw(7, &src, &dst, c, 0.0f);
}

//�����蔻��֘A
void CObjPuddle::HitBox()
{
	//HitBox�̏��
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�����i�[�Ɠ������Ă���ꍇ

	if (runner->GetInvincible() < 0 ) //���G���ԂłȂ���Δ����݂���B
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//�����i�[�̑��̈ʒu�������܂�ɂ������ĂȂ��ꍇ�͔�����Ȃ���
			if (m_py + (40.0f * ((float)m_drow_down - 1)) > runner->GetY())
			{
				if (Input::GetVKey('D') == true)  //�E�ړ�
				{
					runner->SetVX(0.5f);//�����i�[�̈ړ��ʂ�����������
				}
				if (Input::GetVKey('A') == true)  //���ړ�
				{
					runner->SetVX(-0.5f);//�����i�[�̈ړ��ʂ�����������
				}
				if (Input::GetVKey('W') == true)//��ړ�
				{
					runner->SetVY(0.5f);//�����i�[�̈ړ��ʂ�����������
				}
				if (Input::GetVKey('S') == true)//���ړ�
				{
					runner->SetVY(-0.5f);//�����i�[�̈ړ��ʂ�����������
				}
			}
		}
	}

}