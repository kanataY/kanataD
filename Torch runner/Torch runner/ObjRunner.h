#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ランナー
class CObjRunner : public CObj
{
public:
	CObjRunner();
	~CObjRunner(){};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
	float m_vx;
	float m_vy;
};