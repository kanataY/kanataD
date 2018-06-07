//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRunner.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRunner::CObjRunner(int r)
{
	m_remaining = r; //�c�@
}

//�C�j�V�����C�Y
void CObjRunner::Init()
{
	m_px = 250.0f;
	m_py = 500.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��
	m_invincible = 0;
	m_speed = 0.8f;

	m_hole_fall = 0.0f;

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;
	m_hole_control = false;
	m_check_control = false;
	m_check_control_x = false;
	m_homing = false;
	m_check_time = 0;
	m_check_transfer = false;
	m_check_s1 = false;
	m_death = false;
	m_stick_fire = false;
	m_check_vx = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	m_jamp_control_2 = false;
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��
	m_ani_change = 0;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 18, 64, ELEMENT_RUNNER, OBJ_RUNNER, 1);
}

//�A�N�V����
void CObjRunner::Action()
{
	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//�����������Ă���
	CObjHole* hole = (CObjHole*)Objs::GetObj(OBJ_HOLE);

	//�I�J�}�̏��������Ă���
	CObjOkama* okama = (CObjOkama*)Objs::GetObj(OBJ_OKAMA);

	//�Q�[�W�̏��������Ă���
	CObjGauge* gau = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//�`�F�b�N�|�C���g���擾
	CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);

	//�Q�[�W���Ȃ��Ȃ�����----------------------------------------------------------------------
	if (gau->GetGauge() == 192)
	{
		m_remaining -= 1;
		if (m_remaining <= 0)
		{
			Scene::SetScene(new CSceneGameOver());
		}
		else
			Scene::SetScene(new CSceneMain(m_remaining));
	}

	//----------------------------------------------------------------------------------------

	//���񂾂Ƃ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	if (m_death == true)//���񂾂Ƃ�
	{
		//�W�����v�����Ƃ��ɂ��̂܂܍s���Ă��܂��̂Ŗ߂��B
		if (m_py <= 277) //���H����ɍs���Ȃ��悤�ɂ���
			m_py = 277;

		m_stick_fire = false;
		m_hole_fall = 0.0;    //�����i�[�̕`������Ƃɖ߂�
		m_ani_max_time = 3;   //�A�j���[�V�����̑��x���グ��

		if(m_px  < 300.0f)//�R�O�O�̒n�_�܂Ői��
			m_px += 2;
		else
		{
			m_death = false; //��������悤�ɂ���
			m_ani_max_time = 5;//�^�C����߂�
			m_invincible = 50; //���΂炭�̊Ԗ��G���Ԃ�݂���
		}
	}

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	if (m_check_transfer == false)
	{
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
	}
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//�`�F�b�N�|�C���g�ɓ����ĂȂ���΃��C���̍s�����ł���@�@����łȂ����
	if (m_check_control == false && m_death == false)
	{
		//��ʊO�ɍs���Ȃ��悤�ɂ���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		if (m_py >= 536) //��ԉ���艺�ɍs���Ȃ��悤�ɂ���
			m_py = 536;
		if (m_jamp_control_2 == false)          //�W�����v�����ĂȂ���
		{
			if (m_py <= 277) //���H����ɍs���Ȃ��悤�ɂ���
				m_py = 277;
		}

		m_px = cor->Screen_In(m_px);  //�E�ɍs���߂��Ȃ��悤�ɂ���i�E�̉�ʊO�ɍs���Ȃ��悤�Ɂj

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		if (m_stick_fire == true)
		{
			m_speed = 1.6f;
		}
		else
			m_speed = 0.8f;

		if (Input::GetVKey('D') == true)  //�E�ړ�
		{
			m_vx += m_speed;
		}
		if (Input::GetVKey('A') == true)  //���ړ�
		{
			m_vx += -m_speed;
		}
		if (Input::GetVKey('W') == true && m_py > 277)//��ړ�
		{
			m_vy += -m_speed;
		}
		if (Input::GetVKey('S') == true && m_py < 536)//���ړ�
		{
			if (m_jamp_control_2 == false) //�W�����v���ĂȂ���Βʏ�ړ��@���Ă�Βx������
				m_vy += m_speed;
			else
				m_vy += m_speed - 0.6f;
		}

		//���C
		m_vx += -(m_vx * 0.15f);
		m_vy += -(m_vy * 0.15f);

		//�ړ��I��---------------------------------------------------

		//���΂��������i�΂������j---------------------------------------------

		if (m_hole_control == false)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			if (Input::GetVKey('O') == true)
			{
				if (m_torch_control == false)
				{
					m_ani_change = 8; //�A�j���[�V�����̊G���W�Ԃɕς���
					m_torch_control = true;
					//���΂��o�������� 
					CObjTorch* torch = new CObjTorch(m_px + 32.0f, m_py + 28.0f);
					Objs::InsertObj(torch, OBJ_TORCH, 20);
				}
			}
			else
			{
				if (m_torch_time_control > 30) //�R�O�t���[�����Ǝ����G���
				{
					m_torch_control = false;
					m_ani_change = 0;         //�����i�[�̉摜�����Ƃɖ߂�
					m_torch_time_control = 0;
				}
			}
		}

		if (m_torch_control == true) //�~�艺�낵�Ă��ԂȂ�
		{
			m_torch_time_control++;  //���Ԃ�i�߂�B
		}

		//���΂��������I��-----------------------------------------------------------------------------

		//�W�����v---------------------------
		//�X�N���[�����Ƃ܂��Ă�����W�����v�ł��Ȃ�
		if (m_check_vx == false)
		{
			bool m_hag = false;
			if (okama != nullptr)
				m_hag = okama->GetHug();

			if (m_jamp_control == false)
			{
				if (m_hag == false && m_hole_control == false) //��������ĂȂ��A���ɗ����ĂȂ����W�����v�ł���B
				{
					if (Input::GetVKey(VK_SPACE) == true)   //�W�����v����
					{
						m_jamp_control = true;		//�W�����v���Ă���
						m_jamp_control_2 = true;
					}
				}
			}

			//�W�����v��
			float m_jamp_y_1 = 1.6f;
			float m_jamp_y_2 = 0.8f;
			if (m_stick_fire == true)  //�����i�[�ɉ΂����Ă�����W�����v�ʂ𑝂₷
			{
				m_jamp_y_1 = 2.4;
				m_jamp_y_2 = 1.2f;
			}

			if (m_jamp_control == true)//�W�����v���Ă���
			{
				m_time++;
				if (m_time > 20 && m_time < 45) //�W�����v���čō��_�ɓ��B
				{
					if (jamp_memo != 999.0f)    //�W�����v����Ƃ���̂ق��ɂ��Ȃ����W�ŏ����ړ��ł���
					{
						if (Input::GetVKey('W') == true)//��ړ�
						{
							if (m_py > 280)//�����M���M��
								m_vy += m_jamp_y_1;
							else
								m_vy += -m_jamp_y_2;
						}
						else
							m_vy += m_jamp_y_1;//���R�����^��
					}
					else                     //�W�����v����Ƃ���̂ق��ɂ����ꍇ�͂����W�����v����
						m_vy += m_jamp_y_1;
				}
				else if (m_time < 20)
				{
					if (m_py < 280)//�����M���M��
					{
						m_vy += -m_jamp_y_1;
						jamp_memo = 999.0f; //�W�����v���鎞��̂ق��ɂ����ꍇ�͋L�^����
					}
					else
					{
						if (Input::GetVKey('W') == true)//��ړ�
						{
							m_vy += -m_jamp_y_2;
						}
						else
							m_vy += -m_jamp_y_1;//���R�����^��
					}
				}
				if (m_time > 45 && m_time < 57)//���Ԃ�������W�����v���I��������
				{
					m_jamp_control_2 = false;
					m_vy = 0.0f;
				}
				if (m_time > 58) //���Ԃ������玩�R�ɓ�����悤�ɂȂ�
				{
					if (Input::GetVKey(VK_SPACE) == false)   //�X�y�[�X�𗣂��Ȃ�����W�����v�����Ȃ�
					{
						m_jamp_control = false;
						m_time = 0;  //�^�C����������
					}
				}
			}
		}

		//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//���֘A�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		if (m_hole_control == true)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			m_ani_change = 0;
			m_vx = 0.0f; //�����i�[���ړ������Ȃ��悤�ɂ���B
			m_vy = 0.0f;
		}

		if (m_hole_fall > 3)
		{
			m_hole_control = true;
		}

		if (m_hole_fall > 50.0f)  //�����i�[�̕`�悪��ԏ������Ȃ�������
		{
			m_px = -80.0f;
			m_py = 410.0f;
			m_hole_control = false;
			m_death = true;
		}
		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		//���ɍs���߂������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[---

		if (m_px < -50.0f && m_death == false) //�X�N���[���ɒx�ꂽ���͐^�񒆂ŕ���
		{
			//�W�����v�֘A�����ׂčŏ��ɖ߂��B
			m_time = 0;
			m_jamp_control = false;
			m_jamp_control_2 = false;
			//-----------------------------------------------
			m_death = true; //����
		}

		m_invincible--; //���G���Ԍ���


		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 18.0f, m_py);

		//�`�F�b�N�|�C���g����������Ă�Ȃ璲�ׂ�
		if (check != nullptr)
		{
			//�`�F�b�N�|�C���g���w��̈ʒu��
			if (check->GetX() + block->GetScroll() < 400)
			{
				m_check_vx = true; //�����X�N���[�������Ȃ������Ȃ��悤�ɂ���
			}
		}
		if(m_check_vx == false)
		{
			//�΂����Ă���Ƃ��͋����X�N���[�����{�ɂ���
			if (m_stick_fire == true)
				m_vx -= 0.6f; //�����X�N���[���p�ړ���
			else
				m_vx -= 0.3f;
		}

		//�����蔻��֘A
		HitBox();

		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;

		CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
	}

	//�`�F�b�N�|�C���g�ɓ�������󂯓n�����V�[����`�������B
	else if (m_check_control == true)
	{
		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//�`�F�b�N�|�C���g���擾
		CObjCheckPoint* check = (CObjCheckPoint*)Objs::GetObj(OBJ_CHECK_POINT);

		// �`�F�b�N�|�C���g���w��̈ʒu�ɂ���ꍇ
		if (check->GetX() + block->GetScroll() < 400)
		{
			m_check_control_x = true; //�z�[�~���O��ON�ɂ���
		}
		if (m_check_control_x == true)
		{
			m_ani_change = 0;
			//�`�F�b�N�|�C���g�ɂ�����̃����i�[�̈ʒu���擾����
			float okax = ((check->GetX() + block->GetScroll()) + 170.0f) - m_px;
			float okay = (check->GetY()  * 3.0f) - m_py;

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

			//�����i�[�̌��݂̌����Ă�p�x�����
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
				m_vx *= 2; // �ړ����x��2�ׂ��ɂ���
				m_vy *= 2;
				m_homing = true;
			}

			//���̃����i�[�̖ڂ̑O�ɗ�����
			if (m_px > ((check->GetX() + block->GetScroll()) + 170.0f))
			{
				m_check_time++; //�^�C����i�߂�
				m_check_transfer = true;
				m_vx = 0.0f; //�ړ��ʂ��O�ɂ���
				m_vy = 0.0f;
				if (m_check_time < 50) //�U�艺�낷
					m_ani_change = 8;
				else
				{
					m_ani_change = 0;//�ʏ�̏�Ԃő҂�
					m_ani_frame = 1;
				}
			}

			//�ʒu�̍X�V
			m_px += m_vx;
			m_py += m_vy;

			CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
		}
		else
		{
			// �`�F�b�N�|�C���g���w��̂����ɍs���܂ł͈ړ��ʂ�0�ɂ���
			if (m_px < 499 && m_px > 490)
			{
				m_vx = 0.0f;
			}
			else
			m_vx -= 0.3f; //�����X�N���[���p�ړ���

			//���C
			m_vx += -(m_vx * 0.15f);

			//HitBox�̈ʒu�̕ύX
			CHitBox* hit = Hits::GetHitBox(this);
			hit->SetPos(m_px + 18.0f, m_py);

			//�ʒu�̍X�V
			m_px += m_vx;
			m_py += m_vy;
		}
	}
}

//�`��
void CObjRunner::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	RECT_F src2; //�`�挳�؂���ʒu
	RECT_F dst2; //�`���\���ʒu

	//�؂���ʒu�̐ݒ� //���̐悪�ォ�猩���Ă����̂łP.0������
	src.m_top = 1.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right =  64.0f + m_ani_frame * 64;
	src.m_bottom = 257.0f ;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + (m_hole_fall / 3);   //���ɗ��������͕`�������������
	dst.m_left = 0.0f+ m_px + (m_hole_fall / 3);
	dst.m_right = 64.0f + m_px - m_hole_fall;
	dst.m_bottom = 64.0f + m_py - m_hole_fall;

	//�`��
	Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);
	//--------------------------------���G�_��-----------------------------------
	if (m_invincible > 0 && m_death == false)
	{
		//�؂���ʒu�̐ݒ� //���̐悪�ォ�猩���Ă����̂łP.0������
		src.m_top = 1.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 257.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px;
		dst.m_right = 64.0f + m_px;
		dst.m_bottom = 64.0f + m_py;

		//�`��
		Draw::Draw(22, &src, &dst, c, 0.0f);
	}

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���΂̂��Ƃ��[�[�[�[�[�[�[�[�[�[�[�[
	//�؂���ʒu�̐ݒ� 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	if (m_ani_change == 0) //�r��U�艺�낵�Ă��Ȃ�
	{
		if (m_hole_control == true)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			dst2.m_top = 0.0f + m_py - 10.0f + (m_hole_fall / 2);
			dst2.m_left = 0.0f + m_px + 25.0f;
			dst2.m_right = 20.0f + m_px + 40.0f - (m_hole_fall / 2) - 10.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}
		else
		{
			dst2.m_top = 0.0f + m_py - 10.0f;
			dst2.m_left = 0.0f + m_px + 40.0f;
			dst2.m_right = 20.0f + m_px + 40.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}

		//�`��
		Draw::Draw(9, &src2, &dst2, c, 0.0f);
	}
	else //�r��U�艺�낵�Ă���
	{
		dst2.m_top = 0.0f + m_py +18.0f;
		dst2.m_left = 0.0f + m_px + 38.0f;
		dst2.m_right = 20.0f + m_px + 38.0f - m_hole_fall;
		dst2.m_bottom = 32.0f + m_py +18.0f - m_hole_fall;

		//�`��
		Draw::Draw(9, &src2, &dst2, c, -100.0f);
	}

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|���[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�`��J���[���

	RECT_F src3; //�`�挳�؂���ʒu
	RECT_F dst3; //�`���\���ʒu
	
	//�؂���ʒu�̐ݒ�
	src3.m_top = 0.0f;
	src3.m_left = 0.0f + m_ani_frame * 64;
	src3.m_right = 64.0f + m_ani_frame * 64;
	src3.m_bottom = 320.0f;

	if (m_ani_change == 0)//�r��U�艺�낵�Ă��Ȃ�
	{
		if (m_hole_control == true)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			//�\���ʒu�̐ݒ�
			dst3.m_top = 0.0f + m_py - 30.0f + (m_hole_fall);
			dst3.m_left = 0.0f + m_px + 27.0f;
			dst3.m_right = 25.0f + m_px + 37.0f - (m_hole_fall / 1.5f) - 10.0f;
			dst3.m_bottom = 25.0f + m_py - 30.0f + (m_hole_fall / 2.0f);
		}
		else
		{
			//�\���ʒu�̐ݒ�
			dst3.m_top = 0.0f + m_py - 30.0f;
			dst3.m_left = 0.0f + m_px + 37.0f;
			dst3.m_right = 25.0f + m_px + 37.0f;
			dst3.m_bottom = 25.0f + m_py - 30.0f;
		}

		//�`��
		Draw::Draw(6, &src3, &dst3, c, 0.0f);
	}
	else//�r��U�艺�낵�Ă���
	{
		//�\���ʒu�̐ݒ�
		dst3.m_top = 0.0f + m_py +26.0f;
		dst3.m_left = 0.0f + m_px + 52.0f;
		dst3.m_right = 25.0f + m_px + 52.0f - m_hole_fall;
		dst3.m_bottom = 25.0f + m_py +26.0f - m_hole_fall;

		//�`��
		Draw::Draw(6, &src3, &dst3, c, -100.0f);
	}

	//�c�@-------------------------------------------------------------------------------
	//�؂���ʒu�̐ݒ� //���̐悪�ォ�猩���Ă����̂łP.0������
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + 10.0f;
	dst.m_left = 0.0f + 680.0f;
	dst.m_right = 40.0f + 680.0f;
	dst.m_bottom = 40.0f + 10.0f;

	//�c��̐�����`�悷��
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);
	//---------------------------------------------------------------------------------
}

void CObjRunner::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�Q�[�W���������Ă���
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//�X�}�z���N�̈ʒu���擾
	CObjSmartphone* sumaho = (CObjSmartphone*)Objs::GetObj(OBJ_SMARTPHONE);

	if (m_invincible < 0 && m_death == false) //���G���Ԃ���Ȃ����
	{
		if (m_hole_control == false)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			//�X�}�z���N�Ɠ��������ꍇ
			if (hit->CheckObjNameHit(OBJ_SMARTPHONE) != nullptr)
			{
				if ((sumaho->GetX() + block->GetScroll()) < m_px)
				{
					m_vx = 3.6f;//�����i�[�����炷
				}
				else
				{
					m_vx = -5.6f;//�����i�[�����炷
				}

				//�Q�[�W�����炷�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
				if (m_smart_control == false) //�܂��������ĂȂ���΃Q�[�W�����炷
				{
					//�Q�[�W������
					gauge->SetGauge(1.0f);
					m_smart_control = true;
				}
			}
			else
				m_smart_control = false;//�������ĂȂ���ԂȂ�Q�[�W�����点���Ԃɖ߂�
		}
	}

	//�`�F�b�N�|�C���g�Ɠ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_CHECK_POINT) != nullptr)
	{
		m_check_control = true;
		m_vx = 0.0f;
		m_vy = 0.0f;
	}

	//���ɓ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
	{
		m_stick_fire = true;

		//��
		CObjFire* fi = new CObjFire(m_px, m_py, 2);
		Objs::InsertObj(fi, OBJ_FIRE, 999);
	}

	//���ɓ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_PUDDLE) != nullptr)
	{
		//�����i�[�ɉ΂����Ă�Ȃ������
		m_stick_fire = false;
	}
}