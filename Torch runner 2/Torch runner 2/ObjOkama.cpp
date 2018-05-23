//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjOkama.h"
#include "Correction.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjOkama::CObjOkama(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//�C�j�V�����C�Y
void CObjOkama::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_hug = false;
	m_rebagacha = 0;
	m_time = 0;
	m_time_fire = 0;
	m_r_time = 0;
	m_fire_control = false;
	m_homing = false;
	m_rebagacha_cotrol_r = false;
	m_rebagacha_cotrol_l = false;
	m_rebagacha_cotrol_u = false;
	m_rebagacha_cotrol_d = false;
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��

	//�\���L�[�̃A�j���[�V�����ϐ�
	m_ani_crosskey_time = 0;
	m_ani_crosskey_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_crosskey_max_time = 5; //�A�j���[�V�����Ԋu��
						 //HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_OKAMA, 1);
}

//�A�N�V����
void CObjOkama::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	if (m_homing == false)
		m_vx = -2.f;
	m_time++;

	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//�A�j���[�V����---------------------
	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 7)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}
	
	//�\���L�[�p�A�j���[�V����
	m_ani_crosskey_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_crosskey_time > m_ani_crosskey_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_crosskey_frame++;//�t���[����i�߂�
		m_ani_crosskey_time = 0;
	}
	if (m_ani_crosskey_frame == 4)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_crosskey_frame = 0;
	}

	//���΂炭�i��ł���z�[�~���O����------------------------------------------------------------
	if (m_time > 50)
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

		//�I�J�}�̌��݂̌����Ă�p�x�����
		float bor = atan2(m_vy, m_vx)*180.0f / 3.14f;

		//-180�`-0��180�`360�ɕϊ�
		if (bor < 0)
		{
			bor = 360 - abs(bor);
		};
		float br = bor;

		//�����i�[�̂ق��Ƀz�[�~���O����
		if (m_homing == false)
		{
			//�ړ������������i�[�̕����ɂ���
			m_vx = cos(3.14 / 180 * ar);
			m_vy = sin(3.14 / 180 * ar);
			m_vx *= 10; // �ړ����x��10�ׂ��ɂ���
			m_vy *= 10;
			m_homing = true;
			//�����i�[�̕��Ƀz�[�~���O������A�j���[�V�������o��1�ɂ���
			m_ani_max_time = 1;
		}
	}

	//�z�[�~���O�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�␳�̏��������Ă���--------------------------------------------
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py); //Y�̈ʒu���������������璲������

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr) //�����i�[�Ɠ������Ă���
	{
		m_vx = 0; m_vy = 0;  //�����Ȃ��悤�ɂ���
		m_hug = true;        //�������Ă���
	}

	//���o�K�`���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	if (m_hug == true) // �������Ă���
	{
		m_px = runner->GetX() + 20.0f - block->GetScroll(); //�I�J�}�̈ʒu�𒲐�
		m_py = runner->GetY(); //Y�̈ʒu�������i�[�ɍ��킹��

		//���E�㉺�������ƃJ�E���g���P������
		if (Input::GetVKey(VK_RIGHT) == true && Input::GetVKey(VK_LEFT) == true)  //���E���������i�o�O������̂ŉ��}���u�j
		{
			runner->SetVX(-0.0f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_r == false && m_rebagacha_cotrol_l == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_r = true;
				m_rebagacha_cotrol_l = true;
			}
		}

		else if (Input::GetVKey(VK_RIGHT) == true)  //�E
		{
			runner->SetVX(-0.8f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_r == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_r = true;
			}
		}

		else if (Input::GetVKey(VK_LEFT) == true)  //��
		{
			runner->SetVX(0.8f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_l == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_l = true;
			}
		}

		if (Input::GetVKey(VK_RIGHT) == false)  //�E
			m_rebagacha_cotrol_r = false;

		if (Input::GetVKey(VK_LEFT) == false) 
			m_rebagacha_cotrol_l = false;

		if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_DOWN) == true)//�㉺
		{
			runner->SetVY(0.0f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_u == false && m_rebagacha_cotrol_d == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_u = true;
				m_rebagacha_cotrol_d = true;
			}
		}

		else if (Input::GetVKey(VK_UP) == true)//��
		{
			runner->SetVY(0.8f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_u == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_u = true;
			}
		}

		else if (Input::GetVKey(VK_DOWN) == true)//��
		{
			runner->SetVY(-0.8f);//�����i�[�̈ړ��ʂ��O�ɂ���
			if (m_rebagacha_cotrol_d == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_d = true;
			}
		}

		if (Input::GetVKey(VK_UP) == false)
			m_rebagacha_cotrol_u = false;

		if (Input::GetVKey(VK_DOWN) == false)
			m_rebagacha_cotrol_d = false;
	}

	

	if (m_rebagacha > 25) //���o�K�`��50�񂵂���
	{
		m_hug = false;
		m_vx = 100.f; //���ɂԂ����
		m_r_time++;
		if (m_r_time > 5) //���΂炭�����������
		{
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}
	}

	//��ʊO�ɍs���Ǝ���
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
	HitBox(); //HitBox�֘A
	CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
}

//�`��
void CObjOkama::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	if (m_hug == false)
	{
		if (m_homing == false)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 512.0f;

			//�u���b�N���������Ă���
			CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + block->GetScroll();
			dst.m_right = 64.0f + m_px + block->GetScroll();
			dst.m_bottom = 64.0f + m_py;

			//�`��
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
		
		else
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 512.0f;

			//�u���b�N���������Ă���
			CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + block->GetScroll();
			dst.m_right = 64.0f + m_px + block->GetScroll();
			dst.m_bottom = 64.0f + m_py;

			//�`��
			Draw::Draw(13, &src, &dst, c, 0.0f);
		}
	}
	//�����܂��������Ă���Ƃ��̕`��-------------------------------------------------------------
	if (m_hug == true)
	{
		//�������Ă��邨���܂�����-----------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 512.0f;

		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 64.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;

		//�`��
		Draw::Draw(14, &src, &dst, c, 0.0f);

		//�\���L�[�̕`��-------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_crosskey_frame * 64;
		src.m_right = 64.0f + m_ani_crosskey_frame * 64;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = -100.0f + m_py;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 64.0f + m_px + block->GetScroll();
		dst.m_bottom =-44.0f + m_py;

		//�\���L�[�̕`��
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------------

		//�A�ŁI�I�I�̕`��------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = -256.0f + m_py;
		dst.m_left = -100.0f + m_px + block->GetScroll();
		dst.m_right = 156.0f + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//�A�ŁI�I�̉摜�`��
		Draw::Draw(17, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------------------
	}
	//-----------------------------------------------------------------------------------------------------
}

void CObjOkama::HitBox()
{
	//HitBox�̏��
	CHitBox* hit = Hits::GetHitBox(this);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//���̏����擾
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	if (m_hug == true) //�������Ă���
	{
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
	
	}
	//�������Ă���
	if (m_fire_control == true)
	{
		if (fire != nullptr)
		{	
			m_time_fire++; //��莞�Ԃ�������I�J�}�������B
		}
		if (fire == nullptr && m_time_fire > 9) //������������I�J�}��������悤�ɂ���
		{
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}

	}
}