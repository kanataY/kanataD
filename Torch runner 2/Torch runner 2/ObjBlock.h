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
	
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }


private:
	float m_px;		//�ʒu
	float m_py;
	float m_bx1;     //�w�i�̓����l
	float m_bx2;     //�w�i�̓����l2
	
	float m_scroll; //�X�N���[���ʒu

	int m_map[10][MAP_X_MAX];//�}�b�v���
};