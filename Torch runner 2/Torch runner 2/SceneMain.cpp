//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"

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
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\run.png", 0, TEX_SIZE_64);    //�l�ԉ�

	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\back1.png", 1, TEX_SIZE_1024); //�w�i��  1

	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\back2.png", 2, TEX_SIZE_1024); //�w�i��   2

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(192�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 3, TEX_SIZE_192);    //�Q�[�W

	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(128�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 4, TEX_SIZE_64);    //�ؔ�

	//��l���I�u�W�F�N�g�쐬
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock();
	Objs::InsertObj(block, OBJ_BLOCK, 12);

	//�Q�[�W�I�u�W�F�N�g�쐬
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

	//�ؔ�
	CObjCrates* crates = new CObjCrates();
	Objs::InsertObj(crates, OBJ_CRATES, 13);
}

//���s�����\�b�h
void CSceneMain::Scene()
{

}

