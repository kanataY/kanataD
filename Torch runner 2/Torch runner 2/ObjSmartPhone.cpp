//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjSmartphone.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSmartphone::CObjSmartphone(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//�C�j�V�����C�Y
void CObjSmartphone::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_time = 0;
	m_middle = false;
	m_time_fire = 0;
	m_fire_control = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 20; //�A�j���[�V�����Ԋu��
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_ENEMY, OBJ_SMARTPHONE, 1);
}

//�A�N�V����
void CObjSmartphone::Action()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	m_time++;

	//�X�e�[�W�Q�Ȃ�
	if (((UserData*)Save::GetData())->m_stage_count == 2)
	{
		if (m_time < 60)  //60�t���[���ɂȂ�܂ł͓����Ȃ�
		{
			if (m_middle == true) //�����i�[�ȊO��HitBox�ɓ����������^�񒆂�肵���Ȃ�
			{
				m_vx += 0.15f;    //��ɓ�������
				m_vy += -0.15f;
			}
			if (m_middle == false)//�����i�[�ȊO��HitBox�ɓ����������^�񒆂���Ȃ�
			{
				m_vx += 0.15f;   //���ɓ�������
				m_vy += 0.15f;
			}
		}
		if (m_time > 60 && m_time < 120)//���Ɉړ�
		{
			m_vx += 0.15f;
			m_vy += 0.15f;
		}
		if (m_time > 120 && m_time < 240)//��Ɉړ�
		{
			m_vx += 0.15f;
			m_vy += -0.15f;
		}
		if (m_time > 240 && m_time < 300)//���Ɉړ�
		{
			m_vx += 0.15f;
			m_vy += 0.15f;
		}
		if (m_time > 300)//���[�v������
			m_time = 60;
	}
	
	//�X�e�[�W�R�Ȃ�
	if (((UserData*)Save::GetData())->m_stage_count == 3)
	{
		float okax = runner->GetX() - (m_px + block->GetScroll());
		float okay = runner->GetY() - m_py;

		//atan2�Ŋp�x�����߂�
		float r2 = atan2(okay, okax)*180.0f / 3.14f;

		//-180�`-0��180�`360�ɕϊ�
		if (r2 < 0)
		{
			r2 = 360 - abs(r2);
		};

		float ar = r2;

		if (ar < 0)
		{
			ar = 360 - abs(ar);
		}

		//�X�}�z�̌��݂̌����Ă�p�x�����
		float bor = atan2(m_vy, m_vx)*180.0f / 3.14f;

		//-180�`-0��180�`360�ɕϊ�
		if (bor < 0)
		{
			bor = 360 - abs(bor);
		};
		float br = bor;

		//�����i�[�̂ق��Ƀz�[�~���O����
		//�ړ������������i�[�̕����ɂ���
		m_vy = sin(3.14f / 180 * ar);
		m_vy *= 7;

		m_vx += 0.15f;
	}
	//---------------------

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

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py,true); //Y�̈ʒu���������������璲������

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 16.0f + block->GetScroll(), m_py+16.0f);

	HitBox(); //HitBox�֘A

	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//��ʊO�ɍs���Ǝ���
	bool m_s_o = cor->Screen_Out(m_px + 250.0f);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

	CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX


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
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f + m_ani_frame * 64;
	src.m_bottom = 256.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(8, &src, &dst, c, 0.0f);
}

void CObjSmartphone::HitBox()
{
	//HitBox�̏��
	CHitBox* hit = Hits::GetHitBox(this);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//���̏����擾
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	if (hit->CheckObjNameHit(OBJ_CRATES) != nullptr) //�ؔ��Ɠ������Ă���
	{
		if (m_py >= 406.5f) //�^�񒆂�艺�Ȃ�t���O��ON�ɂ���
			m_middle = true;
		if (m_py < 406.5f)  //�^�񒆂���Ȃ�t���O��OFF�ɂ���
			m_middle = false;

		m_time = -60; //�^�C�����ŏ����O�ɖ߂��ē����Ȃ����Ԃ����
		m_vx -= 0.7f; //�o�b�N������

	}

	//�܂��������ĂȂ����
	if (m_fire_control == false)
	{
		//���΂Ɠ������Ă���ꍇ
		if (hit->CheckObjNameHit(OBJ_TORCH) != nullptr)
		{
			cor->FireDisplay(m_px, m_py); //���𔭐�������
			m_fire_control = true;
		}
	}
	//�������Ă���
	if (m_fire_control == true)
	{
		if (fire != nullptr)
		{
			m_vx = 0.0f; //�΂����Ă�Ԃ͓����Ȃ�����
			m_vy = 0.0f;
			m_time_fire++; //��莞�Ԃ�������X�}�z���N�������B
			if (m_time_fire > 65)
			{
				//�X�R�A����
				((UserData*)Save::GetData())->m_point += 600;
				this->SetStatus(false);		//���g�ɍ폜���߂��o��
				Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
			}
		}
	}
	//���ɓ������Ă���ƌジ����
	if (hit->CheckObjNameHit(OBJ_HOLE) != nullptr)
	{
		m_vx -= 0.5f; //�ジ����
	}
}