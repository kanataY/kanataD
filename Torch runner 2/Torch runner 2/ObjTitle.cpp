//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_key_flag = false;
	//key_select = 0;
	m_time = 0;
	m_mou_x = 0.0f;//�ʒu
	m_mou_y = 0.0f;
	m_mou_l = false;//�N���b�N����Ă��Ȃ���Ԃɂ���
	m_pic = 1;//�����摜�ʒu
	m_pic_f = false;

	//�Q�[�����s���Ĉ��̂�
	static bool init_point = false;
	if (init_point == false)
	{
		//�����L���O������
		for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
		{
			((UserData*)Save::GetData())->m_ranking[i] = 0;
		}
		init_point = true;
	}

	//�X�R�A��0�ɂ���
	((UserData*)Save::GetData())->m_point = 0;
}

//�A�N�V����
void CObjTitle::Action()
{
	m_time++;

	//�A�j���[�V������i�߂�
	if (m_time % 30 == 0 && m_pic < 8)
		m_pic++;

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_pic == 8)
	{
		m_pic = 1;
		m_pic_f = true;
	}

	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_l = Input::GetMouButtonL();

	if (Input::GetVKey('Z') == true || m_mou_l == true)
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
}

//�h���[
void CObjTitle::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

				//�^�C�g�����--------
				//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	if (m_pic_f == true)
	{
		//�`��ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//0�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//�^�C�g����ʕ���-----
	//�`��ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 600.0f;

	//m_pic�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(m_pic, &src, &dst, c, 0.0f);


	//Font::StrDraw(L"�^�C�g��", 10, 10, 100, c);
}