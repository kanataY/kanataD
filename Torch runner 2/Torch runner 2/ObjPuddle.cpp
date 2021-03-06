//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjPuddle.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjPuddle::CObjPuddle(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 64;
	m_ry = y / 64;
	m_hit = false;
}

//イニシャライズ
void CObjPuddle::Init()
{
	m_drow_down = 1;
	m_map_con = false;
	
	for (int j = 1; j < 10; j++)  //マップのYの値だけ探す
	{
		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		//マップ番号を取ってくる　
		if (block->GetMap(m_rx, m_ry + j) == 5)//水たまりが下にあるなら増やす
		{
			m_drow_down++;
		}

		if (block->GetMap(m_rx, m_ry - j) == 5)//水たまりが上にあるなら下にあるのを消す
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}

		//水たまり以外なら終了させる
		if (block->GetMap(m_rx, m_ry + j) != 5)
		{
			break;
		}
		//水たまり以外なら終了させる
		if (block->GetMap(m_rx, m_ry - j) != 5)
		{
			break;
		}
	}

	//for (int x = 1; x < 10; x++)  //マップのXの値だけ探す
	//{
	//	//ブロック情報を持ってくる
	//	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//	//マップ番号を取ってくる　
	//	if (block->GetMap(m_rx + x, m_ry) == 5)//水たまりが下にあるなら増やす
	//	{
	//		m_drow_down++;
	//	}

	//	if (block->GetMap(m_rx - x, m_ry) == 5)//水たまりが上にあるなら下にあるのを消す
	//	{
	//		this->SetStatus(false);		//自身に削除命令を出す
	//		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	//	}

	//	//水たまり以外なら終了させる
	//	if (block->GetMap(m_rx + x, m_ry) != 5)
	//	{
	//		break;
	//	}
	//	//水たまり以外なら終了させる
	//	if (block->GetMap(m_rx - x, m_ry) != 5)
	//	{
	//		break;
	//	}
	//}
	
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 55, 45 * (float)m_drow_down, ELEMENT_ITEM, OBJ_PUDDLE, 1);
}

//アクション
void CObjPuddle::Action()
{
	////ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);
	m_py = cor->RangeYPuddle(m_py); //Yの位置がおかしかったら調整する

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 5.0f + block->GetScroll(), m_py + 8.0f * m_drow_down);

	HitBox();

	//画面外に行くと死ぬ
	bool m_s_o = cor->Screen_Out(m_px);

	if (m_s_o == 1)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
	}

}

//描画
void CObjPuddle::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f * m_drow_down + m_py;

	//描画
	Draw::Draw(10, &src, &dst, c, 0.0f);
}

//当たり判定関連
void CObjPuddle::HitBox()
{
	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ランナーを跳ね返す量
	float m_run_return_1 = 2.0f;  //左右
	float m_run_return_2 = 0.5f;  //上下
									 //ランナーが火にあたった場合　ランナーを跳ね返す量を倍にする
	if (runner->GetStickFire() == true)
	{
		m_run_return_1 = 4.0f; //倍にする
		m_run_return_2 = 1.0f;
	}

	//ランナーと当たっている場合
	if (runner->GetInvincible() < 0 && runner->GetJamp() == false) //無敵時間でなければ判定を設ける。&ジャンプしてない時
	{
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//ランナーの足の位置が水たまりにかかってない場合は判定をなくす
			if (m_py + (40.0f * ((float)m_drow_down - 1)) > runner->GetY())
			{
				//水の音を一回だけ鳴らす
				if (m_hit == false)
				{
					Audio::Start(5);
					m_hit = true;
				}
				if (Input::GetVKey('D') == true)  //右移動
				{
					runner->SetVX(-m_run_return_1);//ランナーの移動量を減少させる
				}
				if (Input::GetVKey('A') == true)  //左移動
				{
					runner->SetVX(-m_run_return_1);//ランナーの移動量を減少させる
				}
				if (Input::GetVKey('W') == true)//上移動
				{
					runner->SetVY(m_run_return_2);//ランナーの移動量を減少させる
				}
				if (Input::GetVKey('S') == true)//下移動
				{
					runner->SetVY(-m_run_return_2);//ランナーの移動量を減少させる
				}
			}
		}
		else
		{
			m_hit = false;
		}
	}

}