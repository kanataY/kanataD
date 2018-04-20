//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock()
{

}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//�ʒu
	m_bx = 0.0f;
	m_by = 0.0f;

	m_scroll = 0.0f;
}

//�A�N�V����
void CObjBlock::Action()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	float rx = runner->GetX();
	float ry = runner->GetY();

	//�O���X�N���[�����C��
	if (rx > 300)
	{
		runner->SetX(300);		//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scroll -= runner->GetVX();//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

		//�w�i1�̓���
		m_bx -= runner->GetVX();
		if (m_bx < -800.0f)
			m_bx = 800.0f;

	}
}

//�`��
void CObjBlock::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 512.0f + m_bx;
	dst.m_bottom = 512.0f ;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}