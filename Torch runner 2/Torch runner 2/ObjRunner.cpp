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

	m_torch_control = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	qaajamp_memo = 10;
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅
	m_ani_change = 0;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 18, 64, ELEMENT_RUNNER, OBJ_RUNNER, 1);
}

//アクション
void CObjRunner::Action()
{
	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

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

	//聖火をかざす（火をうつす）---------------------------------------------

	if (Input::GetVKey('C') == true)  
	{
		if (m_torch_control == false)
		{
			m_ani_change = 8;
			m_torch_control = true;
			//聖火を出現させる
			CObjTorch* torch = new CObjTorch(m_px + 64.0f, m_py + 28.0f);
			Objs::InsertObj(torch, OBJ_TORCH, 20);
		}
	}
	else
	{
		m_torch_control = false;
		m_ani_change = 0;
	}

	//聖火をかざす終了-----------------------------------------------------------------------------

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

	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
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
	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 25.0f, m_py);

	//当たり判定関連
	HitBox();

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	CObj::SetPrio((int)m_py); //描画優先順位変更
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
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right =  64.0f + m_ani_frame * 64;
	src.m_bottom = 256.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f+ m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);
}

void CObjRunner::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//スマホ少年の位置を取得
	CObjSmartphone* sumaho = (CObjSmartphone*)Objs::GetObj(OBJ_SMARTPHONE);

	//スマホ少年と当たった場合
	if (hit->CheckObjNameHit(OBJ_SMARTPHONE) != nullptr)
	{
		if ((sumaho->GetX() + block->GetScroll()) < m_px)
		{
			m_vx = 3.6f;//ランナーをずらす
		}
		else
		{
			m_vx = -5.6f;//ランナーをずらす
		}

		//ゲージを減らすPを書く------

		//----------------------
	}

	//水たまりと当たった場合
	if (hit->CheckObjNameHit(OBJ_PUDDLE) != nullptr)
	{
		//ゲージが減る
		;
	}
}