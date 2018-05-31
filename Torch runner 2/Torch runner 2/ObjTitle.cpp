//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
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

	m_key_flag = 0;
	m_key_control = false;
	m_key_control_time = 0;
	m_enter_flag = false;
	m_enter_flag_time = 0;
}

//アクション
void CObjTitle::Action()
{

	//十字キーの上か下を押したとき
	if (Input::GetVKey(VK_UP) == true || Input::GetVKey(VK_DOWN) == true)
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
		}
	}
	else
	{
		if (m_key_control_time>5)
		{
			m_key_control = false;
			m_key_control_time = 0;
		}
	}
	if (m_key_control == true)
	{
		m_key_control_time++;
	}

	if (Input::GetVKey(VK_RETURN) == true && m_key_flag == 0)
	{
		Scene::SetScene(new CSceneMenu());
	}
	if (Input::GetVKey(VK_RETURN) == true && m_key_flag == 1)
	{
		CMultiThread::End();
	}
}

//ドロー
void CObjTitle::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//タイトル画面---------------------------------------
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
	//---------------------------------------------------------

	//タイトルの文字-------------------------------------------
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
	///-------------------------------------------------------------

	//メニューの文字-------------------------------------------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置設定
	dst.m_top = 290.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 512.0f;
	dst.m_bottom = dst.m_top + 120.0f;

	//2番目に登録しているsrc・dst・cで描画する
	Draw::Draw(2, &src, &dst, c, 0.0f);
	///-------------------------------------------------------------

	//終了の文字-------------------------------------------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置設定
	dst.m_top = 420.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 512.0f;
	dst.m_bottom = dst.m_top + 120.0f;

	//3番目に登録しているsrc・dst・cで描画する
	Draw::Draw(3, &src, &dst, c, 0.0f);
	///-------------------------------------------------------------

	//枠の描画-------------------------------------------
	if (m_key_flag == 0)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		//描画位置設定
		dst.m_top = 282.0f;
		dst.m_left = 130.0f;
		dst.m_right = dst.m_left + 520.0f;
		dst.m_bottom = dst.m_top + 130.0f;

		//4番目に登録しているsrc・dst・cで描画する
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		//描画位置設定
		dst.m_top = 412.0f;
		dst.m_left = 130.0f;
		dst.m_right = dst.m_left + 520.0f;
		dst.m_bottom = dst.m_top + 130.0f;

		//4番目に登録しているsrc・dst・cで描画する
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
}