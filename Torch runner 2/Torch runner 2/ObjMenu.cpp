//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "GameL\WinInputs.h"
#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	m_key_flag = 0;
	m_key_control = false;

	((UserData*)Save::GetData())->m_stage_count = 1;
}

//アクション
void CObjMenu::Action()
{
	//十字キーの右か左を押したとき
	if (Input::GetVKey(VK_LEFT) == true|| Input::GetVKey(VK_RIGHT) == true)
	{
		if (m_key_control == false)
		{
			m_key_control = true;
			//フラグが0の時
			if (m_key_flag == 0)
				//フラグを1に
				m_key_flag = 1;

			//フラグが１の時
			else if (m_key_flag == 1)
				//フラグを0に
				m_key_flag = 0;

			//フラグが2の時
			else if (m_key_flag == 2)
				//フラグを3に
				m_key_flag = 3;

			//フラグが3の時
			else if (m_key_flag == 3)
				//フラグを2に
				m_key_flag = 2;
		}
		
	}
	//十字キーの上か下を押したとき
	else if (Input::GetVKey(VK_UP) == true|| Input::GetVKey(VK_DOWN) == true)
	{
		if (m_key_control == false)
		{
			m_key_control = true;
			//フラグが0の時
			if (m_key_flag == 0)
				//フラグを2に
				m_key_flag = 2;

			//フラグが１の時
			else if (m_key_flag == 1)
				//フラグを3に
				m_key_flag = 3;

			//フラグが2の時
			else if (m_key_flag == 2)
				//フラグを0に
				m_key_flag = 0;

			//フラグが3の時
			else if (m_key_flag == 3)
				//フラグを1に
				m_key_flag = 1;
		}
	}
	else
	{
		
		m_key_control = false;
		
	}

	//エンターキーを押したとき
	if (Input::GetVKey(VK_RETURN) == true)
	{
		//エンターキーを押してない状態であれば
		if (m_enter_control == false)
		{
			if (m_key_flag == 0)
			{
				Scene::SetScene(new CSceneMain(3));
			}
			if (m_key_flag == 1)
			{
				Scene::SetScene(new CSceneRanking());
			}
			if (m_key_flag == 2)
			{
				Scene::SetScene(new CSceneTitle());
			}
			if (m_key_flag == 3)
			{
				Scene::SetScene(new CSceneOperation());
			}

			//エンターキーを押した状態と判定する
			m_enter_control = true;
		}
	}
	//エンターキーを押していない時
	else
	{
		//エンターキーは押していないと判定する。
		m_enter_control = false;
	}
}

//ドロー
void CObjMenu::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"Menu", 10, 10, 100, c);

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//背景描画----------------------------------------
	
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//表示位置
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	
	//背景のロゴ(ステージセレクト)---------------------------------------
	if (m_key_flag != 0)
	{
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 140.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	else
	{
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 140.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//背景のロゴ(ランキング)---------------------------------------
	//切り取り位置
	if (m_key_flag != 1)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 140.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 140.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//背景のロゴ(タイトルに戻る)---------------------------------------
	//切り取り位置
	if (m_key_flag != 2)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 260.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 260.0f;
		dst.m_left = 120.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------

	//背景のロゴ(操作説明)---------------------------------------
	//切り取り位置
	if (m_key_flag != 3)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 260.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0;
		src.m_bottom = 512.0f;
		//表示位置
		dst.m_top = 260.0f;
		dst.m_left = 430.0f;
		dst.m_right = dst.m_left + 300.0f;
		dst.m_bottom = dst.m_top + 100.0f;
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------
}