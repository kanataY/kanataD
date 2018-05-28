//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "ObjGameClear.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameClear::Init()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_vx = 1.0f;
	m_vy = 1.0f;
	m_sppde_power = 100;

	m_time = 0;
}

//アクション
void CObjGameClear::Action()
{
	m_time++;

	//float x = m_x + m_vx;
	//float y = m_y + m_vy;

	//if (x <= 0)
	//{
	//	m_vx = m_sppde_power;
	//}
	//if (x + 328 > 800)
	//{
	//	m_vx = -m_sppde_power;
	//}
	//if (y <= 0)
	//{
	//	m_vy = m_sppde_power;
	//}
	//if (y + 46 > 600)
	//{
	//	m_vy = -m_sppde_power;
	//}

	//m_x += m_vx;
	//m_y += m_vy;

	//メニュー画面へ
	if (Input::GetVKey('A') == true)
	{
		Scene::SetScene(new CSceneMenu());
	}

	//ランキング画面へ
	if (Input::GetVKey('S') == true)
	{
		Scene::SetScene(new CSceneRanking());
	}
}

//ドロー
void CObjGameClear::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

				//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//切り取り位置
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//背景描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 328.0f;
	src.m_bottom = 46.0f;

	//描画位置
	if (m_time <= 50)
	{
		dst.m_top = 105.0f - m_time * 0.7f;
		dst.m_left = 400.0f - m_time * 5;
		dst.m_right = 400.0f + m_time * 5;
		dst.m_bottom = 105.0f + m_time * 0.7f;

		//ゲームクリア文字描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else
	{
		dst.m_top = 70.0f;
		dst.m_left = 150.0f;
		dst.m_right = 650.0f;
		dst.m_bottom = 140.0f;

		//ゲームクリア文字描画
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

	if (m_time >= 80)
	{
		//スコア
		Font::StrDraw(L"score", 350, 200, 38, c);
	}

	if (m_time >= 120)
	{
		//メニュー遷移ボタン描画
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 380.0f;
		dst.m_left = 120.0f;
		dst.m_right = 320.0f;
		dst.m_bottom = 580.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);

		//ランキング画面への遷移ボタン描画
		src.m_top = 0.0f;
		src.m_left = 256.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		dst.m_top = 420.0f;
		dst.m_left = 400.0f;
		dst.m_right = 700.0f;
		dst.m_bottom = 570.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);

		//メニュー遷移説明
		//Font::StrDraw(L"Aでメニューへ", 200, 500, 24, c);

		//ランキング遷移説明
		//Font::StrDraw(L"Sでランキングへ", 500, 500, 24, c);
	}
}