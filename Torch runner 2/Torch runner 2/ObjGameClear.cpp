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
	m_time = 0;
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 5;
	m_o_tap_flag = false;
}

//アクション
void CObjGameClear::Action()
{
	
	m_time++;

	//タイムが100を超えるとき
	if (m_time > 100)
	{
		//oを押すと
		if (Input::GetVKey('O') == true)
		{
			//oを押したというフラグを立てる
			m_o_tap_flag = true;
		}
	}

	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}
	//アニメーション終了−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

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
	float color[4] = { 1.0f,1.0f,1.0f,0.5f };
	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 800.0f;

	if (m_time <= 40)
	{
		
		//表示位置
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//背景描画
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	else if (m_time > 40 && m_time <= 80)
	{
	
		//表示位置
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//背景描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	else if (m_time > 80)
	{
		//表示位置
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//背景描画
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}

	if (m_time > 100)
	{
		//oが押されていないとき
		if (m_o_tap_flag == false)
		{
			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 512.0f;
			src.m_bottom = 512.0f;

			//表示位置
			dst.m_top = 20.0f;
			dst.m_left = 140.0f;
			dst.m_right = dst.m_left + 512.0f;
			dst.m_bottom = dst.m_top + 512.0f;

			//背景描画
			Draw::Draw(4, &src, &dst, c, 0.0f);


			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//表示位置
			dst.m_top = 350.0f;
			dst.m_left = 320.0f;
			dst.m_right = dst.m_left + 128.0f;
			dst.m_bottom = dst.m_top + 128.0f;
			//背景描画
			Draw::Draw(5, &src, &dst, c, 0.0f);
		}
		else
		{
			//背景の描画--------------------------------------------------------------------
			//切り取り位置
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 800.0f;
			src.m_bottom = 800.0f;
			//表示位置
			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 600.0f;

			//背景描画
			Draw::Draw(1, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//火の描画-------------------------------------------------------
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 320.0f;

			//表示位置の設定
			dst.m_top = -105.0f;
			dst.m_left = 128.0f;
			dst.m_right = dst.m_left + 512.0f;
			dst.m_bottom = dst.m_top + 192.0f;
			//火の描画
			Draw::Draw(0, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//文字の描画------------------------------------------------------------------
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1024.0f;
			src.m_bottom = 1024.0f;

			//表示位置の設定
			dst.m_top = 30.0f;
			dst.m_left = 0.0f;
			dst.m_right = dst.m_left + 810.0f;
			dst.m_bottom = dst.m_top + 290.0f;
			//火の描画
			Draw::Draw(6, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//スコア
			//得点の描画ーーーーーーーーーーーーーーーーーーーーーーーーーーー
			wchar_t str[128];
			swprintf_s(str, L"スコア：%d点", ((UserData*)Save::GetData())->m_point);
			Font::StrDraw(str, 220, 380, 38, c);
			//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
			//メニュー遷移説明
			Font::StrDraw(L"Aでメニューへ", 180, 490, 24, c);

			//ランキング遷移説明
			Font::StrDraw(L"Sでランキングへ", 500, 490, 24, c);
		}
	}
	

}