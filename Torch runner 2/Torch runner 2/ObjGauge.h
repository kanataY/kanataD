#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲージ
class CObjGauge : public CObj
{
public:
	CObjGauge();
	~CObjGauge() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }
	float GetY() { return m_py; }
	void  SetX(float x) { m_px = x; }
	void  SetY(float y) { m_py = y; }
	void  SetGauge(float g) { m_gauge_decrease += g; }

private:
	float m_px;		//位置
	float m_py;
	int m_time;
	float m_gauge_decrease;
};