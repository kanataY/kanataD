//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjOperation.h"
//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjOperation::Init()
{
	m_scene_flag = 0;
	m_enter_control = false;
	m_zkey_control = false;
	m_scene_start_control = false;
}

//アクション
void CObjOperation::Action()
{
	////エンターキーを押したときにm_scene_start_controlがfalseの時
	if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control ==false)
	{
		if (m_enter_control == false)
		{
			m_scene_flag = 0;
			m_enter_control = true;
			m_scene_start_control = true;
		}
	}
	
	//エンターキーを押したときにm_scene_start_controlがtrueの時
	else if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control ==true)
	{
		//エンターキーを押してない状態であれば
		if (m_enter_control == false)
		{
			//シーンフラグの数値が1または2の時
			if (m_scene_flag == 0)
			{

				//エンターキーを押した状態と判定する
				m_enter_control = true;
				m_scene_flag++;
			}

			//シーンフラグの数値が2の時
			if(m_scene_flag == 1)
			{
				//エンターキーを押してない時
				if (m_enter_control == false)
				{
					//エンターキーを押した状態と判定する
					m_enter_control = true;

					//シーンをメニューに切り替える
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//エンターキーを押していない時
	else
	{
		//エンターキーは押していないと判定する。
		m_enter_control = false;
	}
	
	//Zキーを押したとき
	if (Input::GetVKey('Z') == true)
	{
		//Zキーを押してない状態であれば
		if (m_zkey_control == false)
		{
			//シーンフラグの数値が1の時
			if (m_scene_flag == 1)
			{
				
				//Zキーを押してないなら
				if (m_zkey_control == false)
				{
					//Zキーを押した状態と判定する
					m_zkey_control = true;
					m_scene_flag = 0;
				}

			}
			//シーンフラグの数値が1の時
			if (m_scene_flag == 0)
			{
				//Zキーを押してない時
				if (m_zkey_control == false)
				{
					//Zキーを押した状態と判定する
					m_zkey_control = true;

					//シーンをメニューに切り替える
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//Zキーを押していない時
	else
	{
		//Zキーは押していないと判定する。
		m_zkey_control = false;
	}

	
}

//ドロー
void CObjOperation::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	wchar_t str[128];

	//操作説明画面------------------------------------
	//シーン1の時
	if (m_scene_flag == 0)
	{
		
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

		//進ときに使う文字設定
		swprintf_s(str, L"Enterkeyで次へ");
		//進ときに使う文字を描画
		Font::StrDraw(str, 655, 580, RETURN_SIZE, c);

		//戻るときに使う文字設定
		swprintf_s(str, L"ZkeyでMenuへ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, RETURN_SIZE, c);
	}
	//シーン2の時
	if (m_scene_flag == 1)
	{

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
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//進ときに使う文字設定
		swprintf_s(str, L"EnterkeyでMenuへ");
		//進ときに使う文字を描画
		Font::StrDraw(str, 635, 580, RETURN_SIZE, c);
		//戻るときに使う文字設定
		swprintf_s(str, L"Zkeyで前へ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, RETURN_SIZE, c);
	}
	//---------------------------------------------------------

}