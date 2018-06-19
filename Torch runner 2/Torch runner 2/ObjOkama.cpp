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
	m_time_warning = 0;
	m_hole_out = false;
	ar = 0.0f;
	m_time_hole = 0;
	m_time_fire = 0;
	m_r_time = 0;
	m_avoidance = false;
	m_avoidance_time = 0;
	m_crates_hit = 0;
	m_crates_vy = false;
	m_fire_control = false;
	m_homing = false;
	m_rebagacha_cotrol_r = false;
	m_rebagacha_cotrol_l = false;
	m_rebagacha_cotrol_u = false;
	m_rebagacha_cotrol_d = false;
	m_crates_jamp = false;
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��

	//�\���L�[�̃A�j���[�V�����ϐ�
	m_ani_key_time = 0;
	m_ani_key_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_key_max_time = 5; //�A�j���[�V�����Ԋu��

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

	//���̈ʒu���擾
	CObjCrates* cra = (CObjCrates*)Objs::GetObj(OBJ_CRATES);

	//�x�����o���Ă���
	m_time_warning++;

	//�ŏ��Ɍx�����o���i���̊ԃI�J�}�͂ǂ����ɍs�����Ƃ��j
	if (m_time_warning < 2 && m_time_warning > 0)
	{
		m_px = 0.0f;
		//�x�����o���i�`�悷��j
		CObjWarning* war = new CObjWarning(500, (int)m_py);
		Objs::InsertObj(war, OBJ_WARNING, 20);
	}
	//�x�����������̂ŃI�J�}�����܂̉E�[�ɂ��ǂ��B
	if (m_time_warning > 60 && m_time_warning < 65)
	{
		m_px = 790.0f - block->GetScroll();
	}

	//�x�����I�������o�Ă���
	if (m_time_warning > 65)
	{
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

		//�L�[�{�[�h�\���p�A�j���[�V����
		m_ani_key_time++;//�t���[�����슴�o�^�C����i�߂�
		if (m_ani_key_time > m_ani_key_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
		{
			m_ani_key_frame++;//�t���[����i�߂�
			m_ani_key_time = 0;
		}
		if (m_ani_key_frame == 4)//�t���[�����Ō�܂Ői�񂾂�߂�
		{
			m_ani_key_frame = 0;
		}

		//���΂炭�i��ł���z�[�~���O����------------------------------------------------------------
		if (m_time > 40)
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
				m_vx = cos(3.14f / 180 * ar);
				m_vy = sin(3.14f / 180 * ar);
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
		//���ɓ������ĂȂ�����
		if (m_hole_out == false && m_avoidance == false)
		{
			m_py = cor->RangeY(m_py); //Y�̈ʒu���������������璲������
		}

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py);

		HitBox(); //HitBox�֘A

		//���o�K�`���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		if (m_rebagacha > 15) //���o�K�`��25�񂵂���
		{
			m_hug = false;
			m_vx = 100.f; //���ɂԂ����
			m_r_time++;
			if (m_r_time > 5) //���΂炭�����������
			{
				((UserData*)Save::GetData())->m_point += 300;
				this->SetStatus(false);		//���g�ɍ폜���߂��o��
				Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
			}
		}
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		//�������Ă���
		if (m_fire_control == false)
		{
			//�ؔ�or�����--------------------------------------------------------------------------------------
			if (hit->CheckObjNameHit(OBJ_CRATES) != nullptr && m_fire_control == false)
			{
				m_avoidance = true;
			}

			if (m_avoidance == true)
			{
				m_avoidance_time++; //�^�C����i�߂�

				if (m_avoidance_time < 2)
				{
					m_crates_jamp = true;  //�W�����v�ł���悤�ɂ���
				}

				if (m_avoidance_time < 12) //�ؔ��ɓ�����������
				{
					m_vy = -8.0f;
				}

				//�ړ��ʂ�ω�������
				if (m_avoidance_time > 12 && m_avoidance_time < 22)
				{
					m_vy = 8.0f;
				}

				//�z�[�~���O�ł���悤�ɂ���B
				if (m_avoidance_time > 20 && m_avoidance_time < 25)
				{
					//�ؔ��ɓ������ĂȂ����Ƃɂ���
					m_avoidance = false;
					if (m_crates_jamp == true) //�W�����v������Ƀz�[�~���O����
					{
						m_homing = false;
					}
					m_crates_jamp = false;
				}
				if (m_avoidance_time > 25)
				{
					m_avoidance_time = 3; //���ڂ̃z�[�~���O�͂����Ȃ�
				}
			}
		}
		//--------------------------------------------------------------------------------------

		//���ɓ������������ŉ��
		if (m_hole_out == true)
		{
			m_time_hole++;
			//�W�����v����
			if (10 > m_time_hole)
			{
				m_vy = -8.0f;
			}
			//��������
			if (m_time_hole > 10 && m_time_hole < 20)
			{
				m_vy = 8.0f;
			}
			//���̂܂܍s��
			else if (m_time_hole > 20 && m_time_hole < 30)
			{
				m_hole_out = false;
				m_vy = 0.0f;
				//m_time = 50;
				//m_homing = false; //�z�[�~���O������
				//m_hole_out = false;
			}
			//�ق�̂��������ɂ����Ȃ�����
			else if (m_time_hole > 30)
			{
				m_time_hole = 0;
				
			}
		}

		//��ʊO�ɍs���Ǝ���
		bool m_s_o = cor->Screen_Out(m_px);

		if (m_s_o == 1)
		{
			//�������Ă���
			if (m_fire_control == true)
			{
				((UserData*)Save::GetData())->m_point += 300;
			}
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}

		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;


		CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
	}
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
		src.m_left = 0.0f + m_ani_key_frame * 64;
		src.m_right = 64.0f + m_ani_key_frame * 64;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = -100.0f + m_py;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 64.0f + m_px + block->GetScroll();
		dst.m_bottom = -44.0f + m_py;

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
		dst.m_left = -90.0f + m_px + block->GetScroll();
		dst.m_right = 166.0f + m_px + block->GetScroll();
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

	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//�����������Ă���
	CObjHole* hole = (CObjHole*)Objs::GetObj(OBJ_HOLE);

	//���̏����擾
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	//���ɗ��������I�J�}���E���B
	if (runner->GetHoleFallCon() == true && m_hug == true)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}

	if (m_hug == true) //�������Ă���
	{
		//�܂��������ĂȂ����
		if (m_fire_control == false)
		{
			////���΂Ɠ������Ă���ꍇ
			//if (hit->CheckObjNameHit(OBJ_TORCH) != nullptr)
			//{
			//	cor->FireDisplay(m_px, m_py); //���𔭐�������
			//	m_fire_control = true;
			//}
		}
	}
	//�������Ă���
	if (m_fire_control == true)
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
		if (fire != nullptr)
		{
			m_time_fire++; //��莞�Ԃ�������I�J�}�������B
		}
		if (fire == nullptr && m_time_fire > 9) //������������I�J�}��������悤�ɂ���
		{
			((UserData*)Save::GetData())->m_point += 300;
			this->SetStatus(false);		//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
		}

	}

	if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
	{
		//��
		if (m_fire_control == false)
		{
			CObjFire* fi = new CObjFire(m_px, m_py, 3);
			Objs::InsertObj(fi, OBJ_FIRE, 999);
			m_vx = 0.0f;
			m_vy = 0.0f;
			m_fire_control = true;
		}
	}

	//���ɓ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_HOLE) != nullptr)
	{
		if (hole != nullptr)
		{
			if (m_px + block->GetScroll() < 700.0f)
				m_hole_out = true;
		}
		else
			m_hole_out = false;
	}

	//�����i�[�ɓ���������-------------------------------------
	if (runner->GetInvincible() < 0 && runner->GetDeath() == false) //���G���ԂłȂ���Δ����݂���B
	{
		if (runner->GetHoleFallCon() == false) //�����i�[�����ɗ����Ă��Ȃ����
		{
			if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr && m_fire_control == false) //�����i�[�Ɠ������Ă���
			{
				m_vx = 0; m_vy = 0;  //�����Ȃ��悤�ɂ���
				m_hug = true;        //�������Ă���
			}


			//���o�K�`���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
			if (m_hug == true) // �������Ă���
			{
				m_px = runner->GetX() + 20.0f - block->GetScroll(); //�I�J�}�̈ʒu�𒲐�
				m_py = runner->GetY(); //Y�̈ʒu�������i�[�ɍ��킹��

				// �I�J�}�������������̎�l��
				float m_okama_run_hag_x_r = -2.8f;
				float m_okama_run_hag_x_l = -1.3f;
				float m_okama_run_hag_x_l_r = -2.1f;
				float m_okama_run_hag_y = 0.8f;
				// �����i�[�ɉ΂����Ă�����ړ��ʂ�{�ɂ��Ē�������
				if (runner->GetStickFire() == true)
				{
					m_okama_run_hag_x_r *= 2.0f;
					m_okama_run_hag_x_l *= 1.8f;
					m_okama_run_hag_x_l_r *= 1.85f;
					m_okama_run_hag_y = 1.6f;
				}

				//���E�㉺�������ƃJ�E���g���P������
				if (Input::GetVKey('D') == true && Input::GetVKey('A') == true)  //���E���������i�o�O������̂ŉ��}���u�j
				{
					runner->SetVX(m_okama_run_hag_x_l_r);//�����i�[�̈ړ��ʂ�-1.5�ɂ���
					if (m_rebagacha_cotrol_r == false && m_rebagacha_cotrol_l == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_r = true;
						m_rebagacha_cotrol_l = true;
					}
				}

				else if (Input::GetVKey('D') == true)  //�E
				{
					runner->SetVX(m_okama_run_hag_x_r);//�����i�[�̈ړ��ʂ�-3.0�ɂ���
					if (m_rebagacha_cotrol_r == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_r = true;
					}
				}

				else if (Input::GetVKey('A') == true)  //��
				{
					runner->SetVX(m_okama_run_hag_x_l);//�����i�[�̈ړ��ʂ�-1.5�ɂ���
					if (m_rebagacha_cotrol_l == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_l = true;
					}
				}

				if (Input::GetVKey('D') == false)  //�E
					m_rebagacha_cotrol_r = false;

				if (Input::GetVKey('A') == false)
					m_rebagacha_cotrol_l = false;

				if (Input::GetVKey('W') == true && Input::GetVKey('S') == true)//�㉺
				{
					runner->SetVY(0.0f);//�����i�[�̈ړ��ʂ��O�ɂ���
					if (m_rebagacha_cotrol_u == false && m_rebagacha_cotrol_d == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_u = true;
						m_rebagacha_cotrol_d = true;
					}
				}

				else if (Input::GetVKey('W') == true)//��
				{
					runner->SetVY(m_okama_run_hag_y);//�����i�[�̈ړ��ʂ��O.8�ɂ���
					if (m_rebagacha_cotrol_u == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_u = true;
					}
				}

				else if (Input::GetVKey('S') == true)//��
				{
					runner->SetVY(-m_okama_run_hag_y);//�����i�[�̈ړ��ʂ�-�O.8�ɂ���
					if (m_rebagacha_cotrol_d == false)
					{
						m_rebagacha++;
						m_rebagacha_cotrol_d = true;
					}
				}

				if (Input::GetVKey('W') == false)
					m_rebagacha_cotrol_u = false;

				if (Input::GetVKey('S') == false)
					m_rebagacha_cotrol_d = false;
			}
		}
	}
}