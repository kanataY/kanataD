//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjOperation.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjOperation::Init()
{
	m_scene_flag = 0;
	m_enter_control = false;
	m_zkey_control = false;
	m_scene_start_control = false;
}

//�A�N�V����
void CObjOperation::Action()
{
	////�G���^�[�L�[���������Ƃ���m_scene_start_control��false�̎�
	if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control ==false)
	{
		if (m_enter_control == false)
		{
			m_scene_flag = 0;
			m_enter_control = true;
			m_scene_start_control = true;
		}
	}
	
	//�G���^�[�L�[���������Ƃ���m_scene_start_control��true�̎�
	else if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control ==true)
	{
		//�G���^�[�L�[�������ĂȂ���Ԃł����
		if (m_enter_control == false)
		{
			//�V�[���t���O�̐��l��1�܂���2�̎�
			if (m_scene_flag == 0)
			{

				//�G���^�[�L�[����������ԂƔ��肷��
				m_enter_control = true;
				m_scene_flag++;
			}

			//�V�[���t���O�̐��l��2�̎�
			if(m_scene_flag == 1)
			{
				//�G���^�[�L�[�������ĂȂ���
				if (m_enter_control == false)
				{
					//�G���^�[�L�[����������ԂƔ��肷��
					m_enter_control = true;

					//�V�[�������j���[�ɐ؂�ւ���
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//�G���^�[�L�[�������Ă��Ȃ���
	else
	{
		//�G���^�[�L�[�͉����Ă��Ȃ��Ɣ��肷��B
		m_enter_control = false;
	}
	
	//Z�L�[���������Ƃ�
	if (Input::GetVKey('Z') == true)
	{
		//Z�L�[�������ĂȂ���Ԃł����
		if (m_zkey_control == false)
		{
			//�V�[���t���O�̐��l��1�̎�
			if (m_scene_flag == 1)
			{
				
				//Z�L�[�������ĂȂ��Ȃ�
				if (m_zkey_control == false)
				{
					//Z�L�[����������ԂƔ��肷��
					m_zkey_control = true;
					m_scene_flag = 0;
				}

			}
			//�V�[���t���O�̐��l��1�̎�
			if (m_scene_flag == 0)
			{
				//Z�L�[�������ĂȂ���
				if (m_zkey_control == false)
				{
					//Z�L�[����������ԂƔ��肷��
					m_zkey_control = true;

					//�V�[�������j���[�ɐ؂�ւ���
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//Z�L�[�������Ă��Ȃ���
	else
	{
		//Z�L�[�͉����Ă��Ȃ��Ɣ��肷��B
		m_zkey_control = false;
	}

	
}

//�h���[
void CObjOperation::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	wchar_t str[128];

	//����������------------------------------------
	//�V�[��1�̎�
	if (m_scene_flag == 0)
	{
		
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 1024.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		//0�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(0, &src, &dst, c, 0.0f);

		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey�Ŏ���");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 655, 580, RETURN_SIZE, c);

		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey��Menu��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, RETURN_SIZE, c);
	}
	//�V�[��2�̎�
	if (m_scene_flag == 1)
	{

		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 1024.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;
		//0�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey��Menu��");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 635, 580, RETURN_SIZE, c);
		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey�őO��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, RETURN_SIZE, c);
	}
	//---------------------------------------------------------

}