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
	jamp_memo = 0.0f;
	m_jamp_control = false;
	qaajamp_memo = 10;
	m_time = 0;
}

//�A�N�V����
void CObjRunner::Action()
{
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
	
	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);
	//�ړ��I��---------------------------------------------------

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

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�`��
void CObjRunner::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right =  64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f+ m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}