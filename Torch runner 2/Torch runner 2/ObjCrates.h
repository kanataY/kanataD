#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：木箱
class CObjCrates : public CObj
{
public:
	CObjCrates(int x,int y);
	~CObjCrates() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //HitBox関連
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }

private:
	float m_px;		//位置
	float m_py;
	int m_time;     //タイム

	//制御系
	bool m_fire_control; //火が付いた時の制御
}; 
