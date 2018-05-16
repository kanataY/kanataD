//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRunner.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRunner::CObjRunner()
{

}

//�C�j�V�����C�Y
void CObjRunner::Init()
{
	m_px = 0.0f;
	m_py = 500.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	qaajamp_memo = 10;
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

	//�I�J�}�̏��������Ă���
	CObjOkama* okama = (CObjOkama*)Objs::GetObj(OBJ_OKAMA);

	//��ʊO�ɍs���Ȃ��悤�ɂ���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	if (m_py >= 536) //��ԉ���艺�ɍs���Ȃ��悤�ɂ���
		m_py = 536;
	if (m_jamp_control == false)          //�W�����v�����ĂȂ���
	{
		if (m_py <= 277) //���H����ɍs���Ȃ��悤�ɂ���
			m_py = 277;
	}

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	bool okama_hug = false; //�I�J�}�ɕ�������Ă��邩�ǂ������ׂ�
	if (okama == nullptr)//�I�J�}����������Ă���Ȃ璲�ׂ�
	{
		okama_hug = false;
	}
	else
		okama_hug = okama->GetHug();

	if (okama_hug == false)//��������Ă��Ȃ��Ȃ�ʏ�ǂ��蓮����
	{
		if (Input::GetVKey(VK_RIGHT) == true)  //�E�ړ�
		{
			m_vx += 0.8f;
		}
		if (Input::GetVKey(VK_LEFT) == true)  //���ړ�
		{
			m_vx += -0.8f;
		}
		if (Input::GetVKey(VK_UP) == true && m_py > 277)//��ړ�
		{
			m_vy += -0.8f;
		}
		if (Input::GetVKey(VK_DOWN) == true && m_py < 536)//���ړ�
		{
			m_vy += 0.8f;
		}
	}
	else  //��������Ă����ԂȂ瓮���Ȃ�
	{
		m_vx = 0.0f;
		m_vy = 0.0f;
	}
	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);
	//�ړ��I��---------------------------------------------------

	//���΂��������i�΂������j---------------------------------------------

	if (Input::GetVKey('C') == true)  
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

	if (m_torch_control == true) //�~�艺�낵�Ă��ԂȂ�
	{
		m_torch_time_control++;  //���Ԃ�i�߂�B
	}

	//���΂��������I��-----------------------------------------------------------------------------

	//�W�����v---------------------------
	//�W�����v���ĂȂ���
	//if (m_jamp_control == false)                
	//{
	//	if (Input::GetVKey(VK_SPACE) == true)   //�W�����v����
	//	{
 //			jamp_memo = m_py;	//�W�����v����O�̈ʒu���L������
	//		m_vy = -20;																//�I���̐��l�������邱�ƁB
	//		m_jamp_control = true;		//�W�����v���Ă���
	//	}
	//}
	//if (m_jamp_control == true)//�W�����v���Ă���
	//{
	//	if (m_py >= jamp_memo  && m_vy != -20)		//�������ʒu�ɖ߂��Ă����ꍇ�W�����v�I��
	//	{
	//		m_jamp_control = false;
	//		m_vy = 0;
	//	}
	//	else 
	//		m_vy += 9.8 / (16.0f);//���R�����^��
	//	
	//}

	if (m_jamp_control == false)
	{
		if (Input::GetVKey(VK_SPACE) == true)   //�W�����v����
		{
			//m_time++;
			m_jamp_control = true;		//�W�����v���Ă���
		}
	}
	if (m_jamp_control == true)//�W�����v���Ă���
	{
		if (m_time > 20)
		{

			m_time++;
			if (jamp_memo != 999.0f)
			{
				if (Input::GetVKey(VK_UP) == true)//��ړ�
				{
					m_vy += -0.8f;
				}
				else
					m_vy = 5.0f;//���R�����^��
			}
			else
				m_vy = 5.0f;
		}
		else
		{

			++m_time;
			if (m_py < 280)//�����M���M��
			{
				m_vy = -5.0f;
				jamp_memo = 999.0f;
			}
			else
			{
				if (Input::GetVKey(VK_UP) == true)//��ړ�
				{
					m_vy += -0.8f;
				}
				else
					m_vy = -5.0f;//���R�����^��
			}
		}
		if (m_time > 42)//���Ԃ�������W�����v���I��������
		{
			if (Input::GetVKey(VK_SPACE) == false)   //�W�����v�����Ȃ�
			{
				m_jamp_control = false;

			}
			m_vy = 0.0f;
			m_time = 0;
		}
	}


	//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
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
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 18.0f, m_py);

	//�����蔻��֘A
	HitBox();

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
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
	src.m_bottom = 257.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f+ m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���΂̂��Ƃ��[�[�[�[�[�[�[�[�[�[�[�[
	//�؂���ʒu�̐ݒ� 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	if (m_ani_change == 0) //�r��U�艺�낵�Ă��Ȃ�
	{
		dst2.m_top = 0.0f + m_py - 10.0f;
		dst2.m_left = 0.0f + m_px + 40.0f;
		dst2.m_right = 20.0f + m_px + 40.0f;
		dst2.m_bottom = 32.0f + m_py - 10.0f;

		//�`��
		Draw::Draw(9, &src2, &dst2, c, 0.0f);
	}
	else//�r��U�艺�낵�Ă���
	{
		dst2.m_top = 0.0f + m_py +18.0f;
		dst2.m_left = 0.0f + m_px + 38.0f;
		dst2.m_right = 20.0f + m_px + 38.0f;
		dst2.m_bottom = 32.0f + m_py +18.0f;

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
		//�\���ʒu�̐ݒ�
		dst3.m_top = 0.0f + m_py - 30.0f;
		dst3.m_left = 0.0f + m_px + 37.0f;
		dst3.m_right = 25.0f + m_px + 37.0f;
		dst3.m_bottom = 25.0f + m_py - 30.0f;

		//�`��
		Draw::Draw(6, &src3, &dst3, c, 0.0f);
	}
	else//�r��U�艺�낵�Ă���
	{
		//�\���ʒu�̐ݒ�
		dst3.m_top = 0.0f + m_py +26.0f;
		dst3.m_left = 0.0f + m_px + 52.0f;
		dst3.m_right = 25.0f + m_px + 52.0f;
		dst3.m_bottom = 25.0f + m_py +26.0f;

		//�`��
		Draw::Draw(6, &src3, &dst3, c, -100.0f);
	}
}

void CObjRunner::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N���������Ă���
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//�X�}�z���N�̈ʒu���擾
	CObjSmartphone* sumaho = (CObjSmartphone*)Objs::GetObj(OBJ_SMARTPHONE);

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

	//�����܂�Ɠ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_PUDDLE) != nullptr)
	{
		if (m_puddle_control == false) //�܂��������ĂȂ���΃Q�[�W�����炷
		{
			//�Q�[�W������
			gauge->SetGauge(10.0f);
			m_puddle_control = true;
		}
	}
	else
		m_puddle_control = false;//�������ĂȂ���ԂȂ�Q�[�W�����点���Ԃɖ߂�
}