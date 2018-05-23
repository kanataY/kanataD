#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�����܂�
class CObjPuddle : public CObj
{
public:
	CObjPuddle(int x, int y);
	~CObjPuddle() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //�����蔻��֘A
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//�ʒu
	float m_py;
	int m_rx;		//�ŏ��̈ʒu���L������
	int m_ry;

	bool m_map_con;  //�}�b�v�ǂݍ��݂���񂾂��ɂ���
	int m_drow_down; //�摜�̉���L�΂��B
};