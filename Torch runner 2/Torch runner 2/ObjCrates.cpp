//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjCrates.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCrates::CObjCrates()
{

}

//イニシャライズ
void CObjCrates::Init()
{
	
}

//アクション
void CObjCrates::Action()
{

}

//描画
void CObjCrates::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 296.0f;
	dst.m_left = 196.0;
	dst.m_right = 260.0f;
	dst.m_bottom = 360.0f;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);
}