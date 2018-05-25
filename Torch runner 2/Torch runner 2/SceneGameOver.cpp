//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//���������\�b�h
void CSceneGameOver::InitScene()
{
	//���y�ǂݍ���
	/*Audio::LoadAudio(0, L"gameover.wav", BACK_MUSIC);

	//�{�����[����1.0f�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((1.0 - v));

	//���y�X�^�[�g
	Audio::Start(0);*/

	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER4.png", 1, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER1_Font.png", 2, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER2_Font.png", 3, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER3_Font.png", 4, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER4_Font.png", 5, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\Menutransfer.png", 6, TEX_SIZE_512);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���7�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\GameOver.png", 7, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���8�Ԃɓo�^(512�~512�s�N�Z��)
	Draw::LoadImageW(L"Image\\GameOver\\retry.png", 8, TEX_SIZE_512);

	//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	CObjGameOver* obj = new CObjGameOver();
	Objs::InsertObj(obj, OBJ_GAME_OVER, 10);
}

//���s�����\�b�h
void CSceneGameOver::Scene()
{

}