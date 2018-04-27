//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRunner.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRunner::CObjRunner()
{

}

//イニシャライズ
void CObjRunner::Init()
{
	m_px = 0.0f;
	m_py = 500.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	jamp_memo = 0.0f;
	m_jamp_control = false;
	qaajamp_memo = 10;
	m_time = 0;
}

//アクション
void CObjRunner::Action()
{
	//画面外に行かないようにするーーーーーーーーーーーーーーーーーー

	if (m_py >= 536) //一番下より下に行かないようにする
		m_py = 536;
	if (m_jamp_control == false)          //ジャンプをしてない時
	{
		if (m_py <= 277) //道路より上に行かないようにする
			m_py = 277;
	}

	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//移動ーーーーーーーーーーーーーーーーーーーーー
	if (Input::GetVKey(VK_RIGHT) == true)  //右移動
	{
		m_vx += 0.8f;
	}
	if (Input::GetVKey(VK_LEFT) == true)  //左移動
	{
		m_vx += -0.8f;
	}
	if (Input::GetVKey(VK_UP) == true && m_py > 277)//上移動
	{
		m_vy += -0.8f;
	}
	if (Input::GetVKey(VK_DOWN) == true && m_py < 536)//下移動
	{
		m_vy += 0.8f;
	}
	
	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);
	//移動終了---------------------------------------------------

	//ジャンプ---------------------------
	//ジャンプしてない時
	//if (m_jamp_control == false)                
	//{
	//	if (Input::GetVKey(VK_SPACE) == true)   //ジャンプする
	//	{
 //			jamp_memo = m_py;	//ジャンプする前の位置を記憶する
	//		m_vy = -20;																//終了の数値もいじること。
	//		m_jamp_control = true;		//ジャンプしている
	//	}
	//}
	//if (m_jamp_control == true)//ジャンプしている
	//{
	//	if (m_py >= jamp_memo  && m_vy != -20)		//元居た位置に戻ってきた場合ジャンプ終了
	//	{
	//		m_jamp_control = false;
	//		m_vy = 0;
	//	}
	//	else 
	//		m_vy += 9.8 / (16.0f);//自由落下運動
	//	
	//}

	if (m_jamp_control == false)
	{
		if (Input::GetVKey(VK_SPACE) == true)   //ジャンプする
		{
			//m_time++;
			m_jamp_control = true;		//ジャンプしている
		}
	}
		if (m_jamp_control == true)//ジャンプしている
		{
			if (m_time > 20)
			{
				
				m_time++; 
				if (jamp_memo != 999.0f)
				{
					if (Input::GetVKey(VK_UP) == true)//上移動
					{
						m_vy += -0.8f;
					}
					else
						m_vy = 5.0f;//自由落下運動
				}
				else
					m_vy = 5.0f;
			}
			else
			{
				
				++m_time;
				if (m_py < 280)//道幅ギリギリ
				{
					m_vy = -5.0f;
					jamp_memo = 999.0f;
				}
				else
				{
					if (Input::GetVKey(VK_UP) == true)//上移動
					{
						m_vy += -0.8f;
					}
					else
						m_vy = -5.0f;//自由落下運動
				}
			}
			if (m_time > 42)//時間が来たらジャンプを終了させる
			{
				if (Input::GetVKey(VK_SPACE) == false)   //ジャンプさせない
				{
					m_jamp_control = false;
					
				}
				m_vy = 0.0f;
				m_time = 0;
			}
		}
	

	//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//描画
void CObjRunner::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right =  64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f+ m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}