#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��
class CObjHole : public CObj
{
public:
	CObjHole(int x, int y);
	~CObjHole() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //�����蔻��֘A
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	int   GetDrowDown() { return m_drow_down; } //���������L�����Ă��邩���ׂ�
	bool  GetHoleFall() { return m_hole_fall; } //���Ƀ����i�[�������Ă��邩�ǂ�����Ԃ�
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }

private:
	float m_px;		//�ʒu
	float m_py;
	int m_rx;		//�ŏ��̈ʒu���L������
	int m_ry;
	bool m_hole_fall;

	bool m_map_con;  //�}�b�v�ǂݍ��݂���񂾂��ɂ���
	int m_drow_down; //�摜�̉���L�΂��B
};