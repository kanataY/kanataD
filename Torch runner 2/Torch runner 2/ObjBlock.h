#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock();
	~CObjBlock() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

private:
	float m_px;		//位置
	float m_py;
	float m_bx1;     //背景の動く値
	float m_bx2;     //背景の動く値2
	
	float m_scroll; //スクロール位置
};