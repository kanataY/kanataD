//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneRanking.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneRanking::CSceneRanking()
{

}

//�f�X�g���N�^
CSceneRanking::~CSceneRanking()
{

}

//�����L���O���������\�b�h
void CSceneRanking::InitScene()
{
	Draw::LoadImageW(L"Image\\back\\Numeric.png", 0, TEX_SIZE_256);

	Draw::LoadImageW(L"Image\\back\\ranking_mozi.png", 1, TEX_SIZE_1024);

	Draw::LoadImageW(L"Image\\back\\Bit.png", 2, TEX_SIZE_64);

	//�����L���O�I�u�W�F�N�g�쐬
	CObjRanking* obj = new CObjRanking();		//�����L���O�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_RANKING, 10);		//�����L���O�I�u�W�F�N�g�o�^
}

//�����L���O���s�����\�b�h
void CSceneRanking::Scene()
{

}