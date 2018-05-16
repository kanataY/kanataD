#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_RUNNER,				//�����i�[
	OBJ_BLOCK,				//�u���b�N
	OBJ_GAUGE,				//�Q�[�W
	OBJ_CRATES,				//�ؔ�
	OBJ_SMARTPHONE,			//�X�}�z���N
	OBJ_FIRE,				//��
	OBJ_TORCH,				//����
	OBJ_PUDDLE,				//�����܂�
	OBJ_RAIN,               //�J
	OBJ_OKAMA,              //�I�J�}

	//�␳
	CORRECTION,				//�␳
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_RUNNER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	int m_stage_count;//�X�e�[�W�̎��
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--


//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjRunner.h"			//�����i�[
#include "ObjBlock.h"			//�u���b�N
#include "ObjGauge.h"			//�Q�[�W	
#include "ObjTitle.h"			//�^�C�g��
#include "ObjCrates.h"			//�ؔ�
#include "ObjSmartPhone.h"		//�X�}�z���N
#include "ObjFire.h"			//��
#include "ObjTorch.h"			//����
#include "ObjPuddle.h"			//�����܂�
#include "ObjRain.h"			//�J
#include "ObjOkama.h"			//�I�J�}

//�⏕�n
#include "Correction.h"			//�␳
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"			//�V�[���^�C�g��
#include "SceneTitle.h"			//�V�[�����C��
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneMain
//-----------------------------------------------