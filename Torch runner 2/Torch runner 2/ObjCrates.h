#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ゲージ
class CObjCrates : public CObj
{
public:
	CObjCrates();
	~CObjCrates() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
}; 
