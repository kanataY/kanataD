//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjCrates.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCrates::CObjCrates()
{

}

//�C�j�V�����C�Y
void CObjCrates::Init()
{
	
}

//�A�N�V����
void CObjCrates::Action()
{

}

//�`��
void CObjCrates::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 296.0f;
	dst.m_left = 196.0;
	dst.m_right = 260.0f;
	dst.m_bottom = 360.0f;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);
}