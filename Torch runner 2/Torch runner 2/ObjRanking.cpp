//�g�p����w�b�_�[�t�@�C��
#include <string.h>
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include <mbstring.h>

#include "ObjRanking.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjRanking::Init()
{
	//�l�����p�ϐ�
	int w;

	//�o�u���\�[�g
	for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	{
		for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
		{
			if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
			{
				//�l�̕ύX
				w = ((UserData*)Save::GetData())->m_ranking[i];
				((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
				((UserData*)Save::GetData())->m_ranking[j] = w;
			}
		}
	}

	//�߂�Ƃ��̕����̃T�C�Y
	//�o�C�g�����P�̂Ƃ�0.5	�Q�̂Ƃ�1.0�Ƃ���
	m_return_size = 0;
}

//�A�N�V����
void CObjRanking::Action()
{
	//Z�L�[�������ꂽ��V�[�����j���[��
	if (Input::GetVKey('Z') == true)
	{
		Scene::SetScene(new CSceneMenu());
	}
}

//�h���[
void CObjRanking::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�����L���O��p�w�i�`��
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	wchar_t str[128];

	//�����L���O�𕶎���
	for (int ranking_count = 0; ranking_count < 3; ranking_count++)
	{
		//�����j���O��ranking_count�Ԃ̐��l���i�[
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];

	

		//���ʕ`��
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 64.0f, 64.0f, ranking_count + 1);
		
		//�����L���O�̒l�`�揈��
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 164.0f, 64.f, ranking);
	}

	//�߂�Ƃ��Ɏg�������ݒ�
	swprintf_s(str, L"Zkey��Menu��");
	
	//�߂�Ƃ��Ɏg��������`��
	Font::StrDraw(str, 5, 580, RETURN_SIZE, c);

	//�ʂ̕`��
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 138.0f;
	dst.m_left =175.0f;
	dst.m_right =dst.m_left+56.0f;
	dst.m_bottom =dst.m_top+56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 265.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 392.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);
}

//������̃T�C�Y��Ԃ��֐�
//�����P�@wchar_t *str	:���C���h������
//�߂�l	�����Ŏ�������C���h��������}���`������ɕϊ����ă}���`������ɂ����Ƃ��̃���������Ԃ�
//�}���`������̒�����1�̂Ƃ�0.5�@�Q�̂Ƃ�1�����Z���Ă�����������Ԃ�	
float CObjRanking::StringSize(wchar_t *str)
{
	//�}���`������̕ϐ����쐬
	char wcs[100];
	//�ϊ����ꂽ���������L�^����ϐ�(wcstombs_s�֐��ł����g��Ȃ�)
	size_t ret;

	//�����킩��Ȃ�
	setlocale(LC_CTYPE, "jpn");

	//���C���h��������}���`������ɕϊ�
	wcstombs_s(&ret, wcs, 100, str, _TRUNCATE);

	//*p��wcs�̐擪�|�C���^��n��
	char *p = wcs;

	//�o�C�g��
	float bytes_count = 0.0000f;

	//�����������[�v
	while (*p != '\0')
	{
		//�o�C�g�����m�F
		switch (_mbclen((BYTE*)p))
		{
			//�o�C�g�����P�̂Ƃ�bytes_count��0.5�����Z
		case 1:
			*(p++);
			bytes_count += 0.5;
			break;
			//�o�C�g�����Q�̂Ƃ�bytes_count��1.0�����Z
		case 2:
			*(p++);
			*(p++);
			bytes_count += 1.0;
			break;
		default:
			//error
			break;
		}
	}

	return bytes_count;
}

void CObjRanking::DrawNumber(float dst_top, float dst_left, float dst_size, int num)
{
	//�����̐��@�@��j1568�Ȃ琔���̐���4
	int numeric_number = 0;

	//�����𕪉��������i�[�p & ������
	int num_decomposition[100] = { 0 };

	//�ꌅ�łȂ����ǂ���	false=�ꌅ�@true=�ꌅ�ł͖����@
	bool not_one_digits = false;

	//����num��9���`1���̊Ԃŉ������邩�Ȃǂ𒲂ׂ�
	for (int num_max = 100000000; num_max >= 1; num_max /= 10)
	{
		//
		if (num / num_max >= 1 || not_one_digits == true)
		{
			//
			num_decomposition[numeric_number] = num / num_max;
			//
			num %= num_max;

			numeric_number++;
			not_one_digits = true;
		}
	}
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//����num�̌������O��������
	if (numeric_number == 0)
	{
		//�������P���₷
		numeric_number++;
		//�ꌅ�ڂ��O�ɂ���
		num_decomposition[0] = 0;
	}
	//���������[�v����
	for (int i = 0; i < numeric_number; i++)
	{
		//�����Ƃɐ������ׂ�
		switch (num_decomposition[i])
		{
		case 0://0�̎�0�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 1://1�̎�1�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 2://2�̎�2�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 3://3�̎�3�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 4://4�̎�4�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 5://5�̎�5�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 6://6�̎�6�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 7://7�̎�7�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 8://8�̎�8�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 9://9�̎�9�̉摜�`��
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 3;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		}

		//�\���ʒu�̐ݒ�
		dst.m_top = dst_top;
		dst.m_left = i * dst_size + dst_left;
		dst.m_right = dst.m_left + dst_size;
		dst.m_bottom = dst.m_top + dst_size;

		//�`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
}
