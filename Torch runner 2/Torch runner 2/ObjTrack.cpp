//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjTrack.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjTrack::CObjTrack(int x, int y)
{
	m_px = (float)x;
	m_py = (float)y;
	m_rx = x / 128;
	m_ry = y / 128;
}

//イニシャライズ
void CObjTrack::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_ani_time = 0; 
	m_ani_frame = 0;		//静止フレームを初期にする
	m_ani_max_time = 2;		//アニメーション動作間隔最大値
	for (int j = 1; j < 10; j++)  //マップのYの値だけ探す
	{
		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		
		if (block->GetMap(m_rx, m_ry - j) == 3)//水たまりが上にあるなら下にあるのを消す
		{
			this->SetStatus(false);		//自身に削除命令を出す
			Hits::DeleteHitBox(this);	//所有するHitBoxに削除する
		}
	}
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 128, 68, ELEMENT_ENEMY, OBJ_TRACK, 1);
}

//アクション
void CObjTrack::Action()
{
	//移動速度
	m_vx = -5.5f;

	//アニメーション---------------------------------------------------
	m_ani_time++;
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}
	//-------------------------------------------------------------------


	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py+60.0f);

	HitBox(); //HitBox関連
	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	CObj::SetPrio((int)m_py+50.0f); //描画優先順位変更
}

//描画
void CObjTrack::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 128;
	src.m_right = 128.0f + m_ani_frame * 128;
	src.m_bottom = 512.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 128.0f + m_px + block->GetScroll();
	dst.m_bottom = 128.0f + m_py;

	//描画
	Draw::Draw(21, &src, &dst, c, 0.0f);
}

void CObjTrack::HitBox()
{
	//HitBoxの情報
	CHitBox* hit = Hits::GetHitBox(this);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ランナーと当たっている場合----------------------------------------------
	if (runner->GetInvincible() < 0) //無敵時間でなければ判定を設ける。
	{
		//ランナーのヒットボックスに触れている時
		if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr)
		{
			//トラックのY軸の位置+65.0fよりランナーの位置が上なら
			if (m_py + 65.0f > runner->GetY())
			{
				//ランナーを後ろに移動させる
				runner->SetVX(-9.0f);
			}
		}
	}
}