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
	m_rx = x / 64;
	m_ry = y / 64;
}

//�C�j�V�����C�Y
void CObjTrack::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_time_warning = 0;
	m_ani_change = 0;

	m_ani_time = 0;
	m_ani_frame = 0;		//�Î~�t���[���������ɂ���
	m_ani_max_time = 2;		//�A�j���[�V��������Ԋu�ő�l

		//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (block->GetMap(m_rx, m_ry) == 7)//�}�b�v��Ƀg���b�N����������
	{
		m_ani_change = 0;//0�ɂ���
	}
	if (block->GetMap(m_rx, m_ry) == 8)//�}�b�v��Ƀg���b�N2����������
	{
		m_ani_change = 1;//1�ɂ���
	}
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 128, 68, ELEMENT_ENEMY, OBJ_TRACK, 1);
}

//�A�N�V����
void CObjTrack::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYTrack(m_py); //Y�̈ʒu���������������璲������

	//�x�����o���Ă���
	m_time_warning++;

	//�ŏ��Ɍx�����o���i���̊ԃg���b�N�͂ǂ����ɍs�����Ƃ��j
	if (m_time_warning < 2 && m_time_warning > 0)
	{
		m_px = 0.0f;
		//�x�����o���i�`�悷��j
		CObjWarning* war = new CObjWarning(500, (int)m_py);
		Objs::InsertObj(war, OBJ_WARNING, 20);
	}
	//�x�����������̂Ńg���b�N�����܂̉E�[�ɂ��ǂ��B
	if (m_time_warning > 60 && m_time_warning < 65)
	{
		m_px = 790.0f - block->GetScroll();
	}

	//�x�����I�������o�Ă���
	if (m_time_warning > 65)
	{
		//�ړ����x
		m_vx = -5.5f;

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

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + 60.0f);

		HitBox(); //HitBox�֘A
		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;

		//��ʊO�ɍs���Ǝ���
		bool m_s_o = cor->Screen_Out(m_px);

		if (m_s_o == 1)
		{
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}

		CObj::SetPrio((int)m_py + 50); //�`��D�揇�ʕύX
	}
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
	//m_ani_change��0�̎��g���b�N�̕`��
	if (m_ani_change == 0)
	{
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
	//m_ani_change��1�̎��g���b�N2�̕`��
	if (m_ani_change == 1)
	{
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
		Draw::Draw(27, &src, &dst, c, 0.0f);
	}
}

void CObjTrack::HitBox()
{
	//HitBox�̏��
	CHitBox* hit = Hits::GetHitBox(this);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�����i�[�Ɠ������Ă���ꍇ----------------------------------------------
	if (runner->GetInvincible() < 0) //���G���ԂłȂ���Δ����݂���B
	{
		//�����i�[�̃q�b�g�{�b�N�X�ɐG��Ă��鎞
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//m_ani_cange��0�̎��g���b�N1�̎d�l�ɂ���
			if (m_ani_change == 0)
			{
				//�g���b�N��Y���̈ʒu+65.0f��胉���i�[�̈ʒu����Ȃ�
				if (m_py + 65.0f > runner->GetY())
				{
					//�����i�[�����Ɉړ�������
					runner->SetVX(-9.0f);
				}
			}
			//m_ani_cange��1�̎��g���b�N2�̎d�l�ɂ���
			if (m_ani_change == 1)
			{
				//�g���b�N��Y���̈ʒu+65.0f��胉���i�[�̈ʒu����Ȃ�
				if (m_py + 65.0f > runner->GetY())
				{
					//�����i�[�����Ɉړ�������
					runner->SetVX(-20.0f);
				}
			}
		}
	}
}