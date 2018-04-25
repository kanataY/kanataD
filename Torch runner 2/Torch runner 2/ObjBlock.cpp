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
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;

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
		m_bx1 -= runner->GetVX();
		if (m_bx1 < -800.0f)
			m_bx1 = 800.0f;

		//�w�i2�̓���
		m_bx2 -= runner->GetVX();
		if (m_bx2 < -800.0f)
			m_bx2 = 800.0f;
	}

	//���
	if (m_scroll > -1)//�X�N���[���̏ꏊ�ɂ���ăX�N���[���̓���ꏊ��ς���
	{
		if (m_scroll > -1.0f && rx < 50)//�����ʒu�������ɂ����Ȃ�
		{
			runner->SetX(50.0f);//�����ʒu�ɖ߂�
		}
		else if (rx < 50)
		{
			runner->SetX(50);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scroll -= runner->GetVX();//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

									  //�w�i1�̓���
			m_bx1 -= runner->GetVX();
			if (m_bx1 > 800.0f)
				m_bx1 = -800.0f;

			//�w�i2�̓���
			m_bx2 -= runner->GetVX();
			if (m_bx2 > 800.0f)
				m_bx2 = -800.0f;
		}
	}
	else
	{
		if (rx < 200)
		{
			runner->SetX(200);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scroll -= runner->GetVX();//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

			//�w�i1�̓���
			m_bx1 -= runner->GetVX();
			if (m_bx1 > 800.0f)
				m_bx1 = -800.0f;

			//�w�i2�̓���
			m_bx2 -= runner->GetVX();
			if (m_bx2 > 800.0f)
				m_bx2 = -800.0f;
		}
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
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�̐ݒ�
	//�w�i�P
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f + m_bx1;
	dst.m_right = 800.0f + m_bx1;
	dst.m_bottom = 700.0f ;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�w�i�Q
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_bx2;
	dst.m_right = 805.0f + m_bx2;
	dst.m_bottom = 700.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}