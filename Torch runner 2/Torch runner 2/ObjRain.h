#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：炎
class CObjRain : public CObj
{
public:
	CObjRain(float x, float y);
	~CObjRain() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
	int   m_time;   //タイム

	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
};