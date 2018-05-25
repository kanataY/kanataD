//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "ObjGameClear.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_vx = 1.0f;
	m_vy = 1.0f;
	m_sppde_power = 100;

	m_time = 0;
}

//�A�N�V����
void CObjGameClear::Action()
{
	m_time++;

	//float x = m_x + m_vx;
	//float y = m_y + m_vy;

	//if (x <= 0)
	//{
	//	m_vx = m_sppde_power;
	//}
	//if (x + 328 > 800)
	//{
	//	m_vx = -m_sppde_power;
	//}
	//if (y <= 0)
	//{
	//	m_vy = m_sppde_power;
	//}
	//if (y + 46 > 600)
	//{
	//	m_vy = -m_sppde_power;
	//}

	//m_x += m_vx;
	//m_y += m_vy;

	//���j���[��ʂ�
	if (Input::GetVKey('A') == true)
	{
		Scene::SetScene(new CSceneMenu());
	}

	//�����L���O��ʂ�
	if (Input::GetVKey('S') == true)
	{
		Scene::SetScene(new CSceneRanking());
	}
}

//�h���[
void CObjGameClear::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

				//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�؂���ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�w�i�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 328.0f;
	src.m_bottom = 46.0f;

	//�`��ʒu
	if (m_time <= 50)
	{
		dst.m_top = 105.0f - m_time * 0.7f;
		dst.m_left = 400.0f - m_time * 5;
		dst.m_right = 400.0f + m_time * 5;
		dst.m_bottom = 105.0f + m_time * 0.7f;

		//�Q�[���N���A�����`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else
	{
		dst.m_top = 70.0f;
		dst.m_left = 150.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 140.0f;

		//�Q�[���N���A�����`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

	if (m_time >= 80)
	{
		//�X�R�A
		Font::StrDraw(L"score", 350, 200, 38, c);
	}

	if (m_time >= 120)
	{
		//���j���[�J�ڃ{�^���`��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 380.0f;
		dst.m_left = 120.0f;
		dst.m_right = 320.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);

		//�����L���O��ʂւ̑J�ڃ{�^���`��
		src.m_top = 0.0f;
		src.m_left = 256.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 420.0f;
		dst.m_left = 400.0f;
		dst.m_right = 700.0f;
		dst.m_bottom = 570.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);

		//���j���[�J�ڐ���
		//Font::StrDraw(L"A�Ń��j���[��", 200, 500, 24, c);

		//�����L���O�J�ڐ���
		//Font::StrDraw(L"S�Ń����L���O��", 500, 500, 24, c);
	}
}