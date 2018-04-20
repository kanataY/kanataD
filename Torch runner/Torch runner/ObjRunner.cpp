//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRunner.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjRunner::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
}
//�A�N�V����
void CObjRunner::Action()
{
	if (Input::GetVKey(VK_RIGHT) == true)
	{
		m_vx = 1.0f;
	}
	else
		m_vx = 0.0f;

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
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}