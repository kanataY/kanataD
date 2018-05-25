//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjCrates.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCrates::CObjCrates(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//�C�j�V�����C�Y
void CObjCrates::Init()
{
	m_time = 0;
	m_fire_control = false;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ITEM, OBJ_CRATES, 1);
}

//�A�N�V����
void CObjCrates::Action()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py); //Y�̈ʒu���������������璲������

	CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	//�����蔻��֌W
	HitBox();

	//��ʊO�ɍs���Ǝ���
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	}
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
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left =0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);
}

void CObjCrates::HitBox()
{
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//���΂̏����擾
	CObjTorch* torch = (CObjTorch*)Objs::GetObj(OBJ_TORCH);

	//���̏����擾
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//Hitbox�̏��𒲂ׂ�
	CHitBox* hit = Hits::GetHitBox(this);

	//�܂��������ĂȂ����
	if (m_fire_control == false)
	{
		//���΂Ɠ������Ă���ꍇ
		if (hit->CheckObjNameHit(OBJ_TORCH) != nullptr)
		{
			cor->FireDisplay(m_px, m_py); //���𔭐�������
			m_fire_control = true;
		}
	}
	//�������Ă���
	if (m_fire_control == true)
	{
		if (fire != nullptr)
		{
			m_time++; //��莞�Ԃ�������ؔ��������B
			if (m_time > 99)
			{
				this->SetStatus(false);		//���g�ɍ폜���߂��o��
				Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
			}
		}
	}

	//�I�J�}�Ɠ������Ă���ꍇ
	//if (hit->CheckObjNameHit(OBJ_OKAMA) != nullptr)
	//{
	//	this->SetStatus(false);		//���g�ɍ폜���߂��o��
	//	Hits::DeleteHitBox(this);	//���L����HitBox�ɍ폜����
	//}

	//�����i�[�Ɠ������Ă���ꍇ
	if (runner->GetInvincible() < 0) //���G���ԂłȂ���Δ����݂���B
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//�ؔ��ƃ����i�[���ǂ̊p�x�œ������Ă��邩���m�F
			HIT_DATA** hit_data;						//���������Ƃ��ׂ̍��ȏ������邽�߂̍\����
			hit_data = hit->SearchObjNameHit(OBJ_RUNNER);	//hit_data�ɖؔ��Ɠ������Ă���ق��S�Ă�HitBox�Ƃ̏�������

			for (int i = 0; i < hit->GetCount(); i++)
			{
				//hit_data[i]�ɏ�񂪓����Ă����珈��
				if (hit_data[i] != NULL)
				{
					//���E�ɓ���������
					float r = hit_data[i]->r;

					//�ʂ蔲���Ȃ��悤�ɂ���       ���v����
					//�����i�[����ɓ������Ă�����
					if (r >= 45 && r < 135)
					{
						if (runner->GetY() > m_py - 35.0f)	//�㑤��ʂ蔲�����悤�ɂ���
							runner->SetVY(-0.8f);
					}

					if ((r < 45 && r >= 0) || r >= 315)
					{
						//�E
						if (runner->GetY() < m_py - 35.0f)//�㑤��ʂ蔲�����悤�ɂ���
							;
						else if (runner->GetY() > m_py + 32.0f)//������ʂ蔲�����悤�ɂ���
							;
						else
							runner->SetVX(0.8f);//�^�񒆂�����ʂ蔲����Ȃ��悤�ɂ���
					}

					if (r >= 135 && r < 220)
					{
						//��
						if (runner->GetY() < m_py - 35.0f)//�㑤��ʂ蔲�����悤�ɂ���
							;
						else if (runner->GetY() > m_py + 32.0f)//������ʂ蔲�����悤�ɂ���
							;
						else
							runner->SetVX(-3.0f);//�^�񒆂�����ʂ蔲����Ȃ��悤�ɂ���
					}
					if (r >= 220 && r < 315)
					{
						//��
						if (runner->GetY() < m_py + 32.0f)//������ʂ蔲�����悤�ɂ���
							runner->SetVY(0.8f);
					}
				}
			}
		}
	}
}