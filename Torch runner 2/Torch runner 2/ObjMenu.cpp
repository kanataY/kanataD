//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "GameL\WinInputs.h"
#include "ObjMenu.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	m_key_flag = 0;
	m_key_control = false;
	m_key_control_time = 0;
	((UserData*)Save::GetData())->m_stage_count = 1;
}

//�A�N�V����
void CObjMenu::Action()
{
	//�\���L�[�̉E�������������Ƃ�
	if (Input::GetVKey(VK_LEFT) == true|| Input::GetVKey(VK_RIGHT) == true)
	{
		if (m_key_control == false)
		{
			m_key_control = true;
			//�t���O��0�̎�
			if (m_key_flag == 0)
				//�t���O��1��
				m_key_flag = 1;

			//�t���O���P�̎�
			else if (m_key_flag == 1)
				//�t���O��0��
				m_key_flag = 0;

			//�t���O��2�̎�
			else if (m_key_flag == 2)
				//�t���O��3��
				m_key_flag = 3;

			//�t���O��3�̎�
			else if (m_key_flag == 3)
				//�t���O��2��
				m_key_flag = 2;
		}
		
	}
	//�\���L�[�̏ォ�����������Ƃ�
	else if (Input::GetVKey(VK_UP) == true|| Input::GetVKey(VK_DOWN) == true)
	{
		if (m_key_control == false)
		{
			m_key_control = true;
			//�t���O��0�̎�
			if (m_key_flag == 0)
				//�t���O��2��
				m_key_flag = 2;

			//�t���O���P�̎�
			else if (m_key_flag == 1)
				//�t���O��3��
				m_key_flag = 3;

			//�t���O��2�̎�
			else if (m_key_flag == 2)
				//�t���O��0��
				m_key_flag = 0;

			//�t���O��3�̎�
			else if (m_key_flag == 3)
				//�t���O��1��
				m_key_flag = 1;
		}
	}
	else
	{
		if (m_key_control_time>5)
		{
			m_key_control = false;
			m_key_control_time = 0;
		}
	}
	if (m_key_control == true)
	{
		m_key_control_time++;
	}



	if (Input::GetVKey(VK_RETURN) == true&&m_key_flag==0)
	{
		Scene::SetScene(new CSceneMain());
	}
	if (Input::GetVKey(VK_RETURN) == true && m_key_flag == 1)
	{
		Scene::SetScene(new CSceneRanking());
	}
	if (Input::GetVKey(VK_RETURN) == true && m_key_flag == 2)
	{
		Scene::SetScene(new CSceneTitle());
	}
	if (Input::GetVKey(VK_RETURN) == true && m_key_flag == 3)
	{
		Scene::SetScene(new CSceneMain());
	}

}

//�h���[
void CObjMenu::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"Menu", 10, 10, 100, c);

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�w�i�`��----------------------------------------
	
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	
	//�w�i�̃��S(�X�e�[�W�Z���N�g)---------------------------------------
	if (m_key_flag != 0)
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 140.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	else
	{
		//�؂���ʒu
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 140.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//�w�i�̃��S(�����L���O)---------------------------------------
	//�؂���ʒu
	if (m_key_flag != 1)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 140.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 140.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//�w�i�̃��S(�^�C�g���ɖ߂�)---------------------------------------
	//�؂���ʒu
	if (m_key_flag != 2)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 260.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 260.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//�w�i�̃��S(�������)---------------------------------------
	//�؂���ʒu
	if (m_key_flag != 3)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 260.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//�\���ʒu
		dst.m_top = 260.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------
}