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
	m_py = 0.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��

}

//�A�N�V����
void CObjRunner::Action()
{
	if (Input::GetVKey('D') == true)
	{
		m_vx = 10;
	}
	else
		m_vx = 0;

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