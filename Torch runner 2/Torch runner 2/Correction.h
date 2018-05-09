#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲージ
class CObjCorrection : public CObj
{
public:

	~CObjCorrection() {};
	void Init();	//イニシャライズ
	float RangeY(float y); //範囲外にいるときにただす

private:
	float m_px;		//位置
	float m_py;
};