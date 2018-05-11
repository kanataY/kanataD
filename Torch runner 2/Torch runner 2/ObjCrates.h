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

private:
	float m_px;		//位置
	float m_py;
}; 
