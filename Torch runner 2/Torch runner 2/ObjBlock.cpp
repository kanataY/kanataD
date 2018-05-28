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
CObjBlock::CObjBlock(int map[10][MAP_X_MAX])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(10 * MAP_X_MAX));
	//�}�b�v�f�[�^���L�^����ق��ɃR�s�[
	memcpy(m_map_Record, map, sizeof(int)*(10 * MAP_X_MAX));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//�ʒu
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;

	m_scroll = 0.0f;
	m_scroll_run = 800.0f;
	((UserData*)Save::GetData())->m_stage_count = 1; // ��
}

//�A�N�V����
void CObjBlock::Action()
{
	//�w�i�֘A�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	float rx = runner->GetX();
	float ry = runner->GetY();

	
	//���
	if (runner->GetCheckPoint() == true && rx < 500)
	{
		//�w�i1�̓���
		m_bx1 -= 0.0f;

		//�w�i2�̓���
		m_bx2 -= 0.0f;
	}

	else if (rx < -50 || runner->GetHoleFallCon() == true) //��ʂ�荶���ɍs���Ȃ��悤�ɂ���
	{
		//�w�i1�̓���
		m_bx1 -= 0.0f;

		//�w�i2�̓���
		m_bx2 -= 0.0f;
	}
	//�O���X�N���[�����C��
	else if (rx > -50 && runner->GetHoleFallCon() == false)
	{
		m_scroll -= 2.0f;//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

		//�w�i1�̓���
		m_bx1 -= 2.0f;
		if (m_bx1 < -800.0f)
			m_bx1 = 800.0f;

		//�w�i2�̓���
		m_bx2 -= 2.0f;
		if (m_bx2 < -800.0f)
			m_bx2 = 800.0f;
	}

	

	//�}�b�v�֘A�[�[�[�[�[�[�[�[�[�[
	float line = 0.0f;

	//�G�o�����C��
	//��l���̈ʒu+800 - �����i�[�̈ʒu��G�o�����C���ɂ���
	line = rx + (-m_scroll) + (800 - rx);

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;

	//�G�o�����C���̗������
	for (int i = 0; i < 10; i++)
	{
		//��̒�����P��T��
		if (m_map[i][ex] == 1)
		{
			//�ؔ��𐶐�
			CObjCrates* crates = new CObjCrates(ex*64, i*64);
			Objs::InsertObj(crates, OBJ_CRATES, 19);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}
		//��̒�����Q��T��
		if (m_map[i][ex] == 2)
		{
			//�X�}�z���N�𐶐�
			CObjSmartphone* sma = new CObjSmartphone(ex * 64, i * 64);
			Objs::InsertObj(sma, OBJ_SMARTPHONE, 15);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}

		//��̒�����3��T��
		if (m_map[i][ex] == 3)
		{
			//���𐶐�
			CObjHole* hole = new CObjHole(ex * 64, i * 64);
			Objs::InsertObj(hole, OBJ_HOLE, 15);


			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}

		//��̒�����4��T��
		if (m_map[i][ex] == 4)
		{
			//�I�J�}�𐶐�
			CObjOkama* sma = new CObjOkama(ex * 64, i * 64);
			Objs::InsertObj(sma, OBJ_OKAMA, 16);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}

		//��̒�����5��T��
		if (m_map[i][ex] == 5)
		{
			//�����܂�𐶐�
			CObjPuddle* pu = new CObjPuddle(ex * 64, i * 64);
			Objs::InsertObj(pu, OBJ_PUDDLE, 15);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
		}

		//��̒�����6��T��
		if (m_map[i][ex] == 6)
		{
			//�`�F�b�N�|�C���g�𐶐�
			CObjCheckPoint* che = new CObjCheckPoint(ex * 64, i * 64);
			Objs::InsertObj(che, OBJ_CHECK_POINT, 1600);

			//�G�o���ꏊ�̒l��0�ɂ���
			m_map[i][ex] = 0;
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
	src.m_top =0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�̐ݒ�
	//�w�i�P
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f + m_bx1;
	dst.m_right = 805.0f + m_bx1;
	dst.m_bottom = 700.0f ;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�w�i�Q
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_bx2;
	dst.m_right = 805.0f + m_bx2;
	dst.m_bottom = 700.0f;

	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);
}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map_Record[y][x];

	return -99999;//���������ꍇ
}