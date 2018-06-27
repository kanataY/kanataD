//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGauge.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGauge::CObjGauge()
{

}

//�C�j�V�����C�Y
void CObjGauge::Init()
{
	m_px = 10.0f;
	m_py = 10.0f;	//�ʒu
	m_time = 0;
	m_gauge_decrease = 0.0f;
}

//�A�N�V����
void CObjGauge::Action()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�`�F�b�N�|�C���g�ɓ��B���Ă���Ƃ��̓Q�[�W�����炳�Ȃ��B
	if (runner->GetCheckPoint() == false)
	{
		m_time++;
		if (m_time % 27 == 0) //27�t���[�����ƂɃQ�[�W������悤�ɂ���
		{
			m_gauge_decrease++;
		}
		if (m_gauge_decrease > 192.0f)
		{
			m_gauge_decrease = 192.0f;
		}
	}
}

//�`��
void CObjGauge::Draw()
{
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 192.0f;
	src.m_bottom = 32.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 192.0f + m_px - m_gauge_decrease;  //�Q�[�W�����炷
	dst.m_bottom = 32.0f + m_py;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);
}