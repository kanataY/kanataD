#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：スマホ少年
class CObjSmartphone : public CObj
{
public:
	CObjSmartphone(int x, int y);
	~CObjSmartphone() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
	float m_vx;		//移動量
	float m_vy;
	int   m_time;     //タイム
	bool  m_middle;  //真ん中にいないかしらべる変数
};
