#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N���@
#define MAP_X_MAX 200

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][MAP_X_MAX]);
	~CObjBlock() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	int  GetMap(int x, int y);//�}�b�v���̎擾
	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }
	

private:
	float m_px;		//�ʒu
	float m_py;
	int m_map[10][MAP_X_MAX];//�}�b�v���
	int m_map_Record[10][MAP_X_MAX];//�}�b�v���L�^��
};