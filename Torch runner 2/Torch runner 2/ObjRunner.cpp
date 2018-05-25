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

	m_hole_fall = 0.0f;

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;
	m_hole_control = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	m_jamp_control_2 = false;
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

	//穴情報を持ってくる
	CObjHole* hole = (CObjHole*)Objs::GetObj(OBJ_HOLE);

	//オカマの情報を持ってくる
	CObjOkama* okama = (CObjOkama*)Objs::GetObj(OBJ_OKAMA);

	//画面外に行かないようにするーーーーーーーーーーーーーーーーーー

	if (m_py >= 536) //一番下より下に行かないようにする
		m_py = 536;
	if (m_jamp_control_2 == false)          //ジャンプをしてない時
	{
		if (m_py <= 277) //道路より上に行かないようにする
			m_py = 277;
	}

	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	//移動ーーーーーーーーーーーーーーーーーーーーー

	if (Input::GetVKey('D') == true)  //右移動
	{
		m_vx += 0.8f;
	}
	if (Input::GetVKey('A') == true)  //左移動
	{
		m_vx += -0.8f;
	}
	if (Input::GetVKey('W') == true && m_py > 277)//上移動
	{
		m_vy += -0.8f;
	}
	if (Input::GetVKey('S') == true && m_py < 536)//下移動
	{
		if (m_jamp_control_2 == false) //ジャンプしてなければ通常移動　してれば遅くする
			m_vy += 0.8f;
		else
			m_vy += 0.2f;
	}

	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//移動終了---------------------------------------------------

	//聖火をかざす（火をうつす）---------------------------------------------

	if (m_hole_control == false)  //穴に落ちている場合（当たっている）
	{
		if (Input::GetVKey('O') == true)
		{
			if (m_torch_control == false)
			{
				m_ani_change = 8; //アニメーションの絵を８番に変える
				m_torch_control = true;
				//聖火を出現させる 
				CObjTorch* torch = new CObjTorch(m_px + 32.0f, m_py + 28.0f);
				Objs::InsertObj(torch, OBJ_TORCH, 20);
			}
		}
		else
		{
			if (m_torch_time_control > 30) //３０フレームたつと次が触れる
			{
				m_torch_control = false;
				m_ani_change = 0;         //ランナーの画像をもとに戻す
				m_torch_time_control = 0;
			}
		}
	}

	if (m_torch_control == true) //降り下ろしてる状態なら
	{
		m_torch_time_control++;  //時間を進める。
	}

	//聖火をかざす終了-----------------------------------------------------------------------------

	//ジャンプ---------------------------
	bool m_hag = false;
	if(okama != nullptr)
		m_hag = okama->GetHug();

	if (m_jamp_control == false)
	{
		if (m_hag == false && m_hole_control == false) //抱きつかれてない、穴に落ちてない時ジャンプできる。
		{
			if (Input::GetVKey(VK_SPACE) == true)   //ジャンプする
			{
				m_jamp_control = true;		//ジャンプしている
				m_jamp_control_2 = true;
			}
		}
	}
	if (m_jamp_control == true)//ジャンプしている
	{
		m_time++;
		if (m_time > 20 && m_time < 45) //ジャンプして最高点に到達
		{
			if (jamp_memo != 999.0f)    //ジャンプするとき上のほうにいなければWで少し移動できる
			{
				if (Input::GetVKey('W') == true)//上移動
				{
					if (m_py > 280)//道幅ギリギリ
						m_vy += 1.6f;
					else
						m_vy += -0.8f;
				}
				else
					m_vy += 1.6f;//自由落下運動
			}
			else                     //ジャンプするとき上のほうにいた場合はただジャンプする
				m_vy += 1.6f;
		}
		else if (m_time < 20)
		{
			if (m_py < 280)//道幅ギリギリ
			{
				m_vy += -1.6f;
				jamp_memo = 999.0f; //ジャンプする時上のほうにいた場合は記録する
			}
			else
			{
				if (Input::GetVKey('W') == true)//上移動
				{
					m_vy += -0.8f;
				}
				else
					m_vy += -1.6f;//自由落下運動
			}
		}
		if (m_time > 45 && m_time < 57)//時間が来たらジャンプを終了させる
		{
			m_jamp_control_2 = false;
			m_vy = 0.0f;
		}
		if (m_time > 58) //時間が来たら自由に動けるようになる
		{
			if (Input::GetVKey(VK_SPACE) == false)   //スペースを離さない限りジャンプさせない
			{
				m_jamp_control = false;
				m_time = 0;  //タイムを初期化
			}
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

	if (m_hole_control == true)  //穴に落ちている場合（当たっている）
	{
		m_ani_change = 0;
		m_vx = 0.0f; //ランナーを移動させないようにする。
		m_vy = 0.0f;
	}

	if (m_hole_fall > 3)
	{
		m_hole_control = true;
	}

	if (m_hole_fall > 50.0f)  //ランナーの描画が一番小さくなった時に
	{
		m_ani_change = 0;
		m_hole_fall = 0.0;    //ランナーの描画をもとに戻す
		if (m_px < 200)       //ランナーの位置を穴から近い位置に移動させる
			m_px += 60.0f;
		else
			m_px -= 60.0f;
		m_py -= 10.0f;        //ランナーのYの位置をずらして穴のY軸の真ん中に近い位置で復活させる
		m_hole_control = false;
	}

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 18.0f, m_py);

	//当たり判定関連
	HitBox();

	m_vx -= 0.3f; //強制スクロール用移動量

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
	RECT_F src2; //描画元切り取り位置
	RECT_F dst2; //描画先表示位置

	//切り取り位置の設定 //足の先が上から見えていたので１.0ｆから
	src.m_top = 1.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right =  64.0f + m_ani_frame * 64;
	src.m_bottom = 257.0f ;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + (m_hole_fall / 3);   //穴に落ちた時は描画を小さくする
	dst.m_left = 0.0f+ m_px + (m_hole_fall / 3);
	dst.m_right = 64.0f + m_px - m_hole_fall;
	dst.m_bottom = 64.0f + m_py - m_hole_fall;

	//描画
	Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);

	//ーーーーーーーーーーーーーーーーー聖火のもつとこーーーーーーーーーーーー
	//切り取り位置の設定 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//表示位置の設定
	if (m_ani_change == 0) //腕を振り下ろしていない
	{
		if (m_hole_control == true)  //穴に落ちている場合（当たっている）
		{
			dst2.m_top = 0.0f + m_py - 10.0f + (m_hole_fall / 2);
			dst2.m_left = 0.0f + m_px + 25.0f;
			dst2.m_right = 20.0f + m_px + 40.0f - (m_hole_fall / 2) - 10.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}
		else
		{
			dst2.m_top = 0.0f + m_py - 10.0f;
			dst2.m_left = 0.0f + m_px + 40.0f;
			dst2.m_right = 20.0f + m_px + 40.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}

		//描画
		Draw::Draw(9, &src2, &dst2, c, 0.0f);
	}
	else //腕を振り下ろしている
	{
		dst2.m_top = 0.0f + m_py +18.0f;
		dst2.m_left = 0.0f + m_px + 38.0f;
		dst2.m_right = 20.0f + m_px + 38.0f - m_hole_fall;
		dst2.m_bottom = 32.0f + m_py +18.0f - m_hole_fall;

		//描画
		Draw::Draw(9, &src2, &dst2, c, -100.0f);
	}

	//－－－－－－－－－－－－－－－－－－炎ーーーーーーーーーーーーーー
	//描画カラー情報

	RECT_F src3; //描画元切り取り位置
	RECT_F dst3; //描画先表示位置
	
	//切り取り位置の設定
	src3.m_top = 0.0f;
	src3.m_left = 0.0f + m_ani_frame * 64;
	src3.m_right = 64.0f + m_ani_frame * 64;
	src3.m_bottom = 320.0f;

	if (m_ani_change == 0)//腕を振り下ろしていない
	{
		if (m_hole_control == true)  //穴に落ちている場合（当たっている）
		{
			//表示位置の設定
			dst3.m_top = 0.0f + m_py - 30.0f + (m_hole_fall);
			dst3.m_left = 0.0f + m_px + 27.0f;
			dst3.m_right = 25.0f + m_px + 37.0f - (m_hole_fall / 1.5f) - 10.0f;
			dst3.m_bottom = 25.0f + m_py - 30.0f + (m_hole_fall / 2.0f);
		}
		else
		{
			//表示位置の設定
			dst3.m_top = 0.0f + m_py - 30.0f;
			dst3.m_left = 0.0f + m_px + 37.0f;
			dst3.m_right = 25.0f + m_px + 37.0f;
			dst3.m_bottom = 25.0f + m_py - 30.0f;
		}

		//描画
		Draw::Draw(6, &src3, &dst3, c, 0.0f);
	}
	else//腕を振り下ろしている
	{
		//表示位置の設定
		dst3.m_top = 0.0f + m_py +26.0f;
		dst3.m_left = 0.0f + m_px + 52.0f;
		dst3.m_right = 25.0f + m_px + 52.0f - m_hole_fall;
		dst3.m_bottom = 25.0f + m_py +26.0f - m_hole_fall;

		//描画
		Draw::Draw(6, &src3, &dst3, c, -100.0f);
	}
}

void CObjRunner::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ゲージ情報を持ってくる
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//スマホ少年の位置を取得
	CObjSmartphone* sumaho = (CObjSmartphone*)Objs::GetObj(OBJ_SMARTPHONE);

	if (m_hole_control == false)  //穴に落ちている場合（当たっている）
	{
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

			//ゲージを減らすーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
			if (m_smart_control == false) //まだ当たってなければゲージを減らす
			{
				//ゲージが減る
				gauge->SetGauge(1.0f);
				m_smart_control = true;
			}
		}
		else
			m_smart_control = false;//当たってない状態ならゲージを減らせる状態に戻す
	}
}