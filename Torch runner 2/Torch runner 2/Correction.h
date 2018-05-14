#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define OUTOFRANGE_UP 277.0f
#define OUTOFRANGE_DOWN 536.0f

//オブジェクト：ゲージ
class CObjCorrection : public CObj
{
public:

	~CObjCorrection() {};
	void Init();	//イニシャライズ
	float RangeY(float y); //範囲外にいるときにただす
	void FireDisplay(float x, float y);   //炎を複数表示させる

private:
	float m_px;		//位置
	float m_py;
	
};