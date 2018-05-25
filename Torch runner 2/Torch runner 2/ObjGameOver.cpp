//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	m_key_flag = false;
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_l = false;
	m_time = 0;
}

//�A�N�V����
void CObjGameOver::Action()
{
	m_time++;

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_l = Input::GetMouButtonL();

	if (Input::GetVKey('A') == true || m_mou_l == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneMenu());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�X�R�A�������L���O�̍Ō�ɓ����
	((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;
}

//�h���[
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"GAMEOVER", 10, 10, 100, c);

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

				//�w�i--------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(7, &src, &dst, c, 0.0f);

	//GAMEOVER�����ړ�����-----------

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 130.0f;
	dst.m_left = 100.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 450.0f;

	//Draw::Draw(1, &src, &dst, c, 0.0f);

	//-----�_�ł���ړ�-----
	if (200 <= m_time && m_time < 330)
	{
		dst.m_top = 130.0f - m_time + 200;
		dst.m_left = 100.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 450.0f - m_time + 200;
	}
	else if (m_time >= 330)
	{
		dst.m_top = 0.0f;
		dst.m_left = 100.0f;
		dst.m_right = 690.0f;
		dst.m_bottom = 320.0f;
	}

	if (0 < m_time && m_time < 200 && m_time % 50 == 0)//GameOver�_��
		;
	else //GameOver�ړ�
		Draw::Draw(1, &src, &dst, c, 0.0f);

	if (m_time >= 350)
	{
		Font::StrDraw(L"score", 330, 270, 38, c);
	}

	if (m_time >= 400)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 380.0f;
		dst.m_left = 120.0f;
		dst.m_right = 370.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(8, &src, &dst, c, 0.0f);

		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 360.0f;
		dst.m_left = 420.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(6, &src, &dst, c, 0.0f);

		//Font::StrDraw(L"Z�Ń��j���[��ʂ�", 170, 500, 24, c);
	}

	//---------------------------------------

	/*src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 130.0f;
	dst.m_left = 100.0f;
	dst.m_right = 690.0f;
	dst.m_bottom = 450.0f;

	//---�摜�؂�ւ�---
	if (0 < m_time && m_time <= 10)		//�摜1�\������
	Draw::Draw(2, &src, &dst, c, 0.0f);
	else if (100 < m_time && m_time <= 200) //�摜2�\������
	Draw::Draw(3, &src, &dst, c, 0.0f);
	else if (200 < m_time && m_time <= 300) //�摜3�\������
	Draw::Draw(4, &src, &dst, c, 0.0f);
	else if (300 < m_time && m_time <= 400)//�摜4�\������
	Draw::Draw(5, &src, &dst, c, 0.0f);
	else if (400 < m_time)//�\�����Ԃ��z�����0�ɖ߂�
	m_time = 0;*/
}