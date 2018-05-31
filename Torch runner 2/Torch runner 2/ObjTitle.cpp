//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;
	
	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{
		//ランキング初期化
		for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
		{
			((UserData*)Save::GetData())->m_ranking[i] = 0;
		}
		init_point = true;
	}

	//スコアを0にする
	((UserData*)Save::GetData())->m_point = 0;
}

//アクション
void CObjTitle::Action()
{
	if (Input::GetVKey('Z') == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneMenu());
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjTitle::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//タイトル画面--------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//描画位置設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録しているsrc・dst・cで描画する
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//タイトル画面--------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置設定
	dst.m_top = 20.0f;
	dst.m_left = 120.0f;
	dst.m_right = dst.m_left+512.0f;
	dst.m_bottom = dst.m_top+140.0f;

	//1番目に登録しているsrc・dst・cで描画する
	Draw::Draw(1, &src, &dst, c, 0.0f);
	
}