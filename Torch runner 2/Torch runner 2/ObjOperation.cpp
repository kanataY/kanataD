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
	m_scene_start_control_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 5;

	m_okam_ani_time = 0;
	m_okam_ani_frame = 0;
	m_okam_ani_max_time = 5;
}

//アクション
void CObjOperation::Action()
{
	m_scene_start_control_time++;
	////エンターキーを押したときにコントロールタイムが2より下の時
	if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control_time<2)
	{
		//エンターを押していない判定なら
		if (m_enter_control == false)
		{
			m_scene_flag = 0;
			m_enter_control = true;
		}
	}
	
	//エンターキーを押したときにコントロールタイムが2以上の時
	else if (Input::GetVKey(VK_RETURN) == true&&m_scene_start_control_time>=2)
	{
		//エンターキーを押してない状態であれば
		if (m_enter_control == false)
		{
			//シーンフラグの数値が3じゃない時
			if (m_scene_flag!=3)
			{
				//エンターキーを押してない時
				if (m_enter_control == false)
				{
					//エンターキーを押した状態と判定する
					m_enter_control = true;
					m_scene_flag++;
				}
			}

			//シーンフラグの数値が３の時
			else
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
			//シーンフラグの数値が0じゃない時
			if (m_scene_flag !=0)
			{

				//Zキーを押してないなら
				if (m_zkey_control == false)
				{
					//Zキーを押した状態と判定する
					m_zkey_control = true;
					m_scene_flag --;
				}

			}
			//シーンフラグの数値が0の時
			else
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

	m_okam_ani_time++;//フレーム動作感覚タイムを進める
	if (m_okam_ani_time > m_okam_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_okam_ani_frame++;//フレームを進める
		m_okam_ani_time = 0;
	}
	if (m_okam_ani_frame == 7)//フレームが最後まで進んだら戻す
	{
		m_okam_ani_frame = 0;
	}
	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	
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
		Font::StrDraw(str, 655, 580, 20, c);

		//戻るときに使う文字設定
		swprintf_s(str, L"ZkeyでMenuへ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, 20, c);
	}
	//シーン2の時
	if (m_scene_flag == 1)
	{
		//背景----------------------------------------------------------------------------------------
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
		//1番目に登録しているsrc・dst・cで描画する
		Draw::Draw(1, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------------------
		//スマホ-----------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 256.0f;

		//表示位置の設定
		dst.m_top = 280.0f;
		dst.m_left = 90.0f;
		dst.m_right = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//描画
		Draw::Draw(3, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------

		//おかま-------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_okam_ani_frame * 64;
		src.m_right = 64.0f + m_okam_ani_frame * 64;
		src.m_bottom = 512.0f;

		//表示位置の設定
		dst.m_top = 380.0f;
		dst.m_right = 90.0f;
		dst.m_left = dst.m_right + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//4番目に登録しているsrc・dst・cで描画する
		Draw::Draw(4, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------
		//トラック-----------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 128;
		src.m_right = 128.0f + m_ani_frame * 128;
		src.m_bottom = 512.0f;

		//表示位置の設定
		dst.m_top = 480.0f;
		dst.m_right = 90.0f;
		dst.m_left = 90.0f + dst.m_right;
		dst.m_bottom = dst.m_top + 70.0f;

		//描画
		Draw::Draw(5, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------------------


		//進ときに使う文字設定
		swprintf_s(str, L"Enterkeyで次へ");
		//進ときに使う文字を描画
		Font::StrDraw(str, 655, 580, 20, c);
		//戻るときに使う文字設定
		swprintf_s(str, L"Zkeyで前へ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, 20, c);
	}

	//シーン3の時
	if (m_scene_flag == 2)
	{
		//背景--------------------------------------------------
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
		//2番目に登録しているsrc・dst・cで描画する
		Draw::Draw(2, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------

		//スマホ-----------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 256.0f;

		//表示位置の設定
		dst.m_top = 200.0f;
		dst.m_left = 90.0f;
		dst.m_right = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//描画
		Draw::Draw(3, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------

		//おかま-------------------------------------------------------------
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_okam_ani_frame * 64;
		src.m_right = 64.0f + m_okam_ani_frame * 64;
		src.m_bottom = 512.0f;

		//表示位置の設定
		dst.m_top = 330.0f;
		dst.m_right = 90.0f;
		dst.m_left = dst.m_right + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//4番目に登録しているsrc・dst・cで描画する
		Draw::Draw(4, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------
		//トラック-----------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 128;
		src.m_right = 128.0f + m_ani_frame * 128;
		src.m_bottom = 512.0f;

		//表示位置の設定
		dst.m_top = 450.0f;
		dst.m_right = 90.0f;
		dst.m_left = 90.0f+ dst.m_right;
		dst.m_bottom = dst.m_top+90.0f;

		//描画
		Draw::Draw(5, &src, &dst, c, 0.0f);

		//----------------------------------------------------------------------------------------

		//進ときに使う文字設定
		swprintf_s(str, L"Enterkeyで次へ");
		//進ときに使う文字を描画
		Font::StrDraw(str, 655, 580, 20, c);
		//戻るときに使う文字設定
		swprintf_s(str, L"Zkeyで前へ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, 20, c);
	}
	//---------------------------------------------------------
	if (m_scene_flag == 3)
	{
		//背景--------------------------------------------------
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
		//2番目に登録しているsrc・dst・cで描画する
		Draw::Draw(6, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------

		//進ときに使う文字設定
		swprintf_s(str, L"EnterkeyでMenuへ");
		//進ときに使う文字を描画
		Font::StrDraw(str, 635, 580, 20, c);
		//戻るときに使う文字設定
		swprintf_s(str, L"Zkeyで前へ");
		//戻るときに使う文字を描画
		Font::StrDraw(str, 5, 580, 20, c);
	}
}