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
	Draw::LoadImageW(L"Image\\run.png", 0, TEX_SIZE_64);    //�l�ԉ�

	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back.png", 1, TEX_SIZE_512); //�w�i��

	//��l���I�u�W�F�N�g�쐬
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 12);
}

//���s�����\�b�h
void CSceneMain::Scene()
{

}

