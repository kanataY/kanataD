#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�Q�[�W
class CObjGauge : public CObj
{
public:
	CObjGauge();
	~CObjGauge() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }
	void  SetGauge(float g) { m_gauge_decrease += g; }

private:
	float m_px;		//�ʒu
	float m_py;
	int m_time;
	float m_gauge_decrease;
};