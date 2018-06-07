//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain()
{

}


//�f�X�g���N�^
CSceneMain::~CSceneMain()
{

}

//���������\�b�h
void CSceneMain::InitScene()
{
	//�}�b�v�쐻
	int map[MAP_Y][MAP_X];
	MapCreate(map);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\runner.png", 0, TEX_SIZE_256);    //��ꑖ��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\back1.png", 1, TEX_SIZE_1024); //�w�i��  1
	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\back2.png", 2, TEX_SIZE_1024); //�w�i��   2
	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(192�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 3, TEX_SIZE_192);    //�Q�[�W
	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 4, TEX_SIZE_64);    //�ؔ�
	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 5, TEX_SIZE_256);    //�X�}�z���N
	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(320�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Fire.png", 6, TEX_SIZE_320);    //��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���7�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Puddle.png", 7, TEX_SIZE_64);    //�����܂�
	//�O���O���t�B�b�N�t�@�C����ǂݍ���8�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\runner_transfer.png", 8, TEX_SIZE_256);    //�ꑖ�҂̉΂��������[�V����
	//�O���O���t�B�b�N�t�@�C����ǂݍ���9�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\torch.png", 9, TEX_SIZE_64);    //���΂̎��Ƃ�
	//�O���O���t�B�b�N�t�@�C����ǂݍ���10�Ԃɓo�^(800�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Rain\\rain1.png", 10, TEX_SIZE_800);    //�J�P
	//�O���O���t�B�b�N�t�@�C����ǂݍ���11�Ԃɓo�^(800�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Rain\\a3.png", 11, TEX_SIZE_800);    //�J�Q
	//�O���O���t�B�b�N�t�@�C����ǂݍ���12�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\okama.png", 12, TEX_SIZE_512);    //�I�J�}
	//�O���O���t�B�b�N�t�@�C����ǂݍ���13�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\okama2.png", 13, TEX_SIZE_512);    //�I�J�}(�ڂ��n�[�g)
	//�O���O���t�B�b�N�t�@�C����ǂݍ���14�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\okama_hug.png", 14, TEX_SIZE_512);    //�I�J�}�n�O
	//�O���O���t�B�b�N�t�@�C����ǂݍ���15�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\hole.png", 15, TEX_SIZE_64);    //��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���16�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\characterkey.png", 16, TEX_SIZE_256);    //�����L�[
    //�O���O���t�B�b�N�t�@�C����ǂݍ���17�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\battered.png", 17, TEX_SIZE_256);    //�����I�I�I�̕���
	//�O���O���t�B�b�N�t�@�C����ǂݍ���18�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\checkpoint.png", 18, TEX_SIZE_256);    //�`�F�b�N�|�C���g
	//�O���O���t�B�b�N�t�@�C����ǂݍ���19�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\youtuber.png", 19, TEX_SIZE_256);    //YouTube��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���20�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 20, TEX_SIZE_256);    //YouTube���̐U�肩����
	//�O���O���t�B�b�N�t�@�C����ǂݍ���21�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Track.png", 21, TEX_SIZE_512);    //�g���b�N
	//�O���O���t�B�b�N�t�@�C����ǂݍ���22�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\runner_invincible.png", 22, TEX_SIZE_256);    //��ꑖ�҂̓_��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���23�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\youtuber_invincible.png", 23, TEX_SIZE_256);    //YouTuber�̓_��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���24�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\warning.png", 24, TEX_SIZE_128);    //�x��
																	  
	//��l���I�u�W�F�N�g�쐬
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//�Q�[�W�I�u�W�F�N�g�쐬
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

	//�␳�I�u�W�F�N�g�쐬
	CObjCorrection* cor = new CObjCorrection();
	Objs::InsertObj(cor, CORRECTION, 13);

	//�I�J�}�o�Y�[�J
	/*CObjOkama* o = new CObjOkama(800.0f, 450.0f);
	Objs::InsertObj(o, OBJ_OKAMA, 13);
*/
	/*CObjOkama* o2 = new CObjOkama(800.0f, 500.0f);
	Objs::InsertObj(o2, OBJ_OKAMA, 13);

	CObjOkama* o3 = new CObjOkama(800.0f, 550.0f);
	Objs::InsertObj(o3, OBJ_OKAMA, 13);

	CObjOkama* o4 = new CObjOkama(800.0f, 600.0f);
	Objs::InsertObj(o4, OBJ_OKAMA, 13);

	CObjOkama* o5 = new CObjOkama(800.0f, 350.0f);
	Objs::InsertObj(o5, OBJ_OKAMA, 13);

	CObjOkama* o6 = new CObjOkama(800.0f, 300.0f);
	Objs::InsertObj(o6, OBJ_OKAMA, 13);*/

	/*
	CObjRain* r = new CObjRain(0.0f, 0.0f);
	Objs::InsertObj(r, OBJ_RAIN, 1300);*/

	//CObjTrack* t = new CObjTrack(600, 400);
	//Objs::InsertObj(t, OBJ_TRACK, 30);

	//CObjWarning* war = new CObjWarning(500, 400);
	//Objs::InsertObj(war, OBJ_WARNING, 20);
}

//���s�����\�b�h
void CSceneMain::Scene()
{

}

//�X�e�[�W���Ƃ̃}�b�v�쐬
void CSceneMain::MapCreate(int map[][MAP_X])
{
	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p; //�X�e�[�W���|�C���^�[
	int size;			   //�X�e�[�W���̑傫��

	//�X�e�[�W���ƂɃX�e�[�W�̖��O���i�[
	switch (((UserData*)Save::GetData())->m_stage_count = 1)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage1.csv", &size);//�O���f�[�^�ǂݍ���
		break;

		break;
	default:
		MessageBox(0, L"�X�e�[�W�ԍ�������������܂���B", NULL, MB_OK);
		break;
	}

	//�O���f�[�^���ǂݍ��߂Ȃ�������G���[���b�Z�[�W���o���B
	if (p == NULL)
	{
		MessageBox(0, L"�O���f�[�^���ǂݍ��߂܂���ł����B", NULL, MB_OK);
	}
	int count = 1;
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if (w > 9)//10�𒴂����ꍇ
				count += 3;//���炷���𑝂₷
			else
				count += 2;
		}
	}
}