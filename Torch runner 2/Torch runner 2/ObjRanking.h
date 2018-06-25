#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ランキング
class CObjRanking : public CObj
{
public:
	CObjRanking() {};
	~CObjRanking() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void DrawNumber(float dst_top, float dst_left, float dst_size, int num, float interval, float c[4]);//数字を描画関数
private:
	float m_interval;//値と値の間隔幅をせばめる値
};