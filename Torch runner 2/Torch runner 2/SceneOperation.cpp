//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneOperation.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneOperation::CSceneOperation()
{

}

//�f�X�g���N�^
CSceneOperation::~CSceneOperation()
{

}

//�Q�[�����C�����������\�b�h
void CSceneOperation::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_key.png", 0, TEX_SIZE_1024);//�������
	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_object.png", 1, TEX_SIZE_1024);//�ڂ��̐���

	//�����I�u�W�F�N�g�쐬
	CObjOperation* obj = new CObjOperation();
	Objs::InsertObj(obj, OBJ_OPERATION, 10);
}

//�Q�[�����C�����s�����\�b�h
void CSceneOperation::Scene()
{

}