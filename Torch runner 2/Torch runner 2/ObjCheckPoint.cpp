//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjCheckPoint.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCheckPoint::CObjCheckPoint(int x,int y)
{
	m_px = (float)x;
	m_py = (float)y;
}

//イニシャライズ
void CObjCheckPoint::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_pos = 0.0f;
	m_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅
	m_ani_change = 19;

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 150, 300, ELEMENT_ITEM, OBJ_CHECK_POINT, 1);
}

//アクション
void CObjCheckPoint::Action()
{
	//ゲージ情報を持ってくる
	CObjGauge* gauge = (CObjGauge*)Objs::GetObj(OBJ_GAUGE);

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	//ランナーが目の前に来た時
	if (runner->GetCheckTransfer() == true)
	{
		m_time++;
		m_ani_change = 20; //腕を振り下ろす
	}

	if (m_time > 50)	   //振り下ろしてしばらくたったら走り出す
	{
		m_pos = 1.0f;      //向きを変える
		m_ani_change = 19; //走る描画に変える

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

		m_vx += 1.0f;
	}

	//シーン移動する。
	if (m_time > 220)
	{
		((UserData*)Save::GetData())->m_point += (int)gauge->GetGauge() * 100;
		((UserData*)Save::GetData())->m_stage_count += 1;
		
		if (((UserData*)Save::GetData())->m_stage_count == 4)
		{
			Scene::SetScene(new CSceneGameClear());
		}
		else
			Scene::SetScene(new CSceneMain(3));
	}

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll() + 50.0f, m_py + 180.0f);

	HitBox();  //当たり判定関連
}

//描画
void CObjCheckPoint::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py - 55.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 256.0f + m_px + block->GetScroll();
	dst.m_bottom = 256.0f + m_py * 3;

	//描画
	Draw::Draw(18, &src, &dst, c, 0.0f);

	RECT_F src2; //描画元切り取り位置
	RECT_F dst2; //描画先表示位置

	//切り取り位置の設定
	src2.m_top = 0.0f;
	src2.m_left = 64.0f + m_ani_frame * 64;
	src2.m_right = 128.0f + m_ani_frame * 64;
	src2.m_bottom = 256.0f;

	//表示位置の設定
	dst2.m_top = 0.0f + m_py* 3.0f;
	dst2.m_left = (64.0f -(64.0f * m_pos)) + m_px + block->GetScroll() + 230.0f + m_vx;
	dst2.m_right = (64.0f * m_pos) + m_px + block->GetScroll() + 230.0f + m_vx;
	dst2.m_bottom = 64.0f + m_py * 3.0f;

	//描画
	Draw::Draw(m_ani_change, &src2, &dst2, c, 0.0f);

	//ーーーーーーーーーーーーーーーーー聖火のもつとこーーーーーーーーーーーー

	RECT_F src3; //描画元切り取り位置
	RECT_F dst3; //描画先表示位置

	//切り取り位置の設定 
	src3.m_top = 1.0f;
	src3.m_left = 0.0f;
	src3.m_right = 64.0f;
	src3.m_bottom = 64.0f;

	//表示位置の設定
	if (m_ani_change == 19) //腕を振り下ろしていない
	{
		if (m_time > 50)
		{
			dst3.m_top = 0.0f + m_py * 3.0f - 10.0f;
			dst3.m_left = 0.0f + m_px + block->GetScroll() + 267.0f + m_vx;
			dst3.m_right = 20.0f + m_px + block->GetScroll() + 267.0f + m_vx;
			dst3.m_bottom = 32.0f + m_py * 3.0f - 10.0f;
		}
		else
		{
			dst3.m_top = 0.0f + m_py * 3.0f - 10.0f;
			dst3.m_left = 0.0f + m_px + block->GetScroll() + 240.0f;
			dst3.m_right = 20.0f + m_px + block->GetScroll() + 240.0f;
			dst3.m_bottom = 32.0f + m_py * 3.0f - 10.0f;
		}

		//描画
		Draw::Draw(9, &src3, &dst3, c, 0.0f);
	}
	else //腕を振り下ろしている
	{
		dst3.m_top = 0.0f + m_py * 3.0f + 18.0f;
		dst3.m_left = 0.0f + m_px + block->GetScroll() + 240.0f;
		dst3.m_right = 20.0f + m_px + block->GetScroll() + 240.0f;
		dst3.m_bottom = 32.0f + m_py * 3.0f + 18.0f;

		//描画
		Draw::Draw(9, &src3, &dst3, c, 100.0f);
	}

	//－－－－－－－－－－－－－－－－－－炎ーーーーーーーーーーーーーー
	//描画カラー情報

	RECT_F src4; //描画元切り取り位置
	RECT_F dst4; //描画先表示位置

	//切り取り位置の設定
	src4.m_top = 0.0f;
	src4.m_left = 0.0f + m_ani_frame * 64;
	src4.m_right = 64.0f + m_ani_frame * 64;
	src4.m_bottom = 320.0f;

	if (m_ani_change == 20)//腕を振り下ろしていない
	{
		//表示位置の設定
		dst4.m_top = 0.0f + m_py* 3.0f + 26.0f;
		dst4.m_left = 0.0f + m_px + block->GetScroll() + 220.0f;
		dst4.m_right = 25.0f + m_px + block->GetScroll() + 220.0f;
		dst4.m_bottom = 25.0f + m_py* 3.0f + 26.0f;

		//描画
		Draw::Draw(6, &src4, &dst4, c, 100.0f);
	}
	else if (m_time > 50)
	{
		//表示位置の設定
		dst4.m_top = 0.0f + m_py* 3.0f - 30.0f;
		dst4.m_left = 0.0f + m_px + block->GetScroll() + 265.0f + m_vx;
		dst4.m_right = 25.0f + m_px + block->GetScroll() + 265.0f + m_vx;
		dst4.m_bottom = 25.0f + m_py* 3.0f  - 30.0f;

		//描画
		Draw::Draw(6, &src4, &dst4, c, 0.0f);
	}

}

void CObjCheckPoint::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
}