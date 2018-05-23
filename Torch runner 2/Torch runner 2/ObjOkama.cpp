//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjOkama.h"
#include "Correction.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjOkama::CObjOkama(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//イニシャライズ
void CObjOkama::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_hug = false;
	m_rebagacha = 0;
	m_time = 0;
	m_time_fire = 0;
	m_r_time = 0;
	m_fire_control = false;
	m_homing = false;
	m_rebagacha_cotrol_r = false;
	m_rebagacha_cotrol_l = false;
	m_rebagacha_cotrol_u = false;
	m_rebagacha_cotrol_d = false;
	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅

	//十字キーのアニメーション変数
	m_ani_crosskey_time = 0;
	m_ani_crosskey_frame = 0;  //静止フレームを初期にする
	m_ani_crosskey_max_time = 5; //アニメーション間隔幅
						 //HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_OKAMA, 1);
}

//アクション
void CObjOkama::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	//移動ーーーーーーーーーーーーーーーーーーーーーーーーー
	if (m_homing == false)
		m_vx = -2.f;
	m_time++;

	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//アニメーション---------------------
	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 7)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}
	
	//十字キー用アニメーション
	m_ani_crosskey_time++;//フレーム動作感覚タイムを進める
	if (m_ani_crosskey_time > m_ani_crosskey_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_crosskey_frame++;//フレームを進める
		m_ani_crosskey_time = 0;
	}
	if (m_ani_crosskey_frame == 4)//フレームが最後まで進んだら戻す
	{
		m_ani_crosskey_frame = 0;
	}

	//しばらく進んでからホーミングする------------------------------------------------------------
	if (m_time > 50)
	{
		float okax = runner->GetX() - (m_px + block->GetScroll());
		float okay = runner->GetY() - m_py;

		//atan2で角度を求める
		float r2 = atan2(okay, okax)*180.0f / 3.14f;

		//-180～-0を180～360に変換
		if (r2 < 0)
		{
			r2 = 360 - abs(r2);
		};

		float ar = r2;

		if (ar < 0)
		{
			ar = 360 - abs(ar);
		}

		//オカマの現在の向いてる角度を取る
		float bor = atan2(m_vy, m_vx)*180.0f / 3.14f;

		//-180～-0を180～360に変換
		if (bor < 0)
		{
			bor = 360 - abs(bor);
		};
		float br = bor;

		//ランナーのほうにホーミングする
		if (m_homing == false)
		{
			//移動方向をランナーの方向にする
			m_vx = cos(3.14 / 180 * ar);
			m_vy = sin(3.14 / 180 * ar);
			m_vx *= 10; // 移動速度を10べぇにする
			m_vy *= 10;
			m_homing = true;
			//ランナーの方にホーミングしたらアニメーション感覚を1にする
			m_ani_max_time = 1;
		}
	}

	//ホーミング終了ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー

	//補正の情報を持ってくる--------------------------------------------
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeY(m_py); //Yの位置がおかしかったら調整する

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr) //ランナーと当たっている
	{
		m_vx = 0; m_vy = 0;  //動けないようにする
		m_hug = true;        //抱きついている
	}

	//レバガチャーーーーーーーーーーーーーーーーーー
	if (m_hug == true) // 抱きついている
	{
		m_px = runner->GetX() + 20.0f - block->GetScroll(); //オカマの位置を調整
		m_py = runner->GetY(); //Yの位置をランナーに合わせる

		//左右上下を押すとカウントが１増える
		if (Input::GetVKey(VK_RIGHT) == true && Input::GetVKey(VK_LEFT) == true)  //左右同時押し（バグがあるので応急処置）
		{
			runner->SetVX(-0.0f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_r == false && m_rebagacha_cotrol_l == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_r = true;
				m_rebagacha_cotrol_l = true;
			}
		}

		else if (Input::GetVKey(VK_RIGHT) == true)  //右
		{
			runner->SetVX(-0.8f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_r == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_r = true;
			}
		}

		else if (Input::GetVKey(VK_LEFT) == true)  //左
		{
			runner->SetVX(0.8f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_l == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_l = true;
			}
		}

		if (Input::GetVKey(VK_RIGHT) == false)  //右
			m_rebagacha_cotrol_r = false;

		if (Input::GetVKey(VK_LEFT) == false) 
			m_rebagacha_cotrol_l = false;

		if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_DOWN) == true)//上下
		{
			runner->SetVY(0.0f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_u == false && m_rebagacha_cotrol_d == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_u = true;
				m_rebagacha_cotrol_d = true;
			}
		}

		else if (Input::GetVKey(VK_UP) == true)//上
		{
			runner->SetVY(0.8f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_u == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_u = true;
			}
		}

		else if (Input::GetVKey(VK_DOWN) == true)//下
		{
			runner->SetVY(-0.8f);//ランナーの移動量を０にする
			if (m_rebagacha_cotrol_d == false)
			{
				m_rebagacha++;
				m_rebagacha_cotrol_d = true;
			}
		}

		if (Input::GetVKey(VK_UP) == false)
			m_rebagacha_cotrol_u = false;

		if (Input::GetVKey(VK_DOWN) == false)
			m_rebagacha_cotrol_d = false;
	}

	

	if (m_rebagacha > 25) //レバガチャ50回したら
	{
		m_hug = false;
		m_vx = 100.f; //後ろにぶっ飛ぶ
		m_r_time++;
		if (m_r_time > 5) //しばらくしたら消える
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}
	}

	//画面外に行くと死ぬ
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
	HitBox(); //HitBox関連
	CObj::SetPrio((int)m_py); //描画優先順位変更
}

//描画
void CObjOkama::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	if (m_hug == false)
	{
		if (m_homing == false)
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 512.0f;

			//ブロック情報を持ってくる
			CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + block->GetScroll();
			dst.m_right = 64.0f + m_px + block->GetScroll();
			dst.m_bottom = 64.0f + m_py;

			//描画
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
		
		else
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 512.0f;

			//ブロック情報を持ってくる
			CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px + block->GetScroll();
			dst.m_right = 64.0f + m_px + block->GetScroll();
			dst.m_bottom = 64.0f + m_py;

			//描画
			Draw::Draw(13, &src, &dst, c, 0.0f);
		}
	}
	//おかまが抱きついているときの描画-------------------------------------------------------------
	if (m_hug == true)
	{
		//抱きついているおかまちゃんの-----------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 512.0f;

		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 64.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;

		//描画
		Draw::Draw(14, &src, &dst, c, 0.0f);

		//十字キーの描画-------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_crosskey_frame * 64;
		src.m_right = 64.0f + m_ani_crosskey_frame * 64;
		src.m_bottom = 256.0f;

		//表示位置の設定
		dst.m_top = -100.0f + m_py;
		dst.m_left = 0.0f + m_px + block->GetScroll();
		dst.m_right = 64.0f + m_px + block->GetScroll();
		dst.m_bottom =-44.0f + m_py;

		//十字キーの描画
		Draw::Draw(16, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------------

		//連打！！！の描画------------------------------------------------------------------
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//表示位置の設定
		dst.m_top = -256.0f + m_py;
		dst.m_left = -100.0f + m_px + block->GetScroll();
		dst.m_right = 156.0f + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//連打！！の画像描画
		Draw::Draw(17, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------------------
	}
	//-----------------------------------------------------------------------------------------------------
}

void CObjOkama::HitBox()
{
	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//炎の情報を取得
	CObjFire* fire = (CObjFire*)Objs::GetObj(OBJ_FIRE);

	if (m_hug == true) //抱きついている
	{
		//まだ炎がついてない状態
		if (m_fire_control == false)
		{
			//聖火と当たっている場合
			if (hit->CheckObjNameHit(OBJ_TORCH) != nullptr)
			{
				cor->FireDisplay(m_px, m_py); //炎を発生させる
				m_fire_control = true;
			}
		}
	
	}
	//炎がついてる状態
	if (m_fire_control == true)
	{
		if (fire != nullptr)
		{	
			m_time_fire++; //一定時間たったらオカマを消す。
		}
		if (fire == nullptr && m_time_fire > 9) //炎が消えたらオカマも消えるようにする
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}

	}
}