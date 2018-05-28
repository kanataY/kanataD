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

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 124, 300, ELEMENT_ITEM, OBJ_CHECK_POINT, 1);
}

//アクション
void CObjCheckPoint::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

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
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 256.0f;

	//表示位置の設定
	dst2.m_top = 0.0f + m_py* 3.0f;
	dst2.m_left = 64.0f + m_px + block->GetScroll() + 230.0f;
	dst2.m_right = 0.0f + m_px + block->GetScroll() + 230.0f;
	dst2.m_bottom = 64.0f + m_py * 3.0f;

	//描画
	Draw::Draw(19, &src2, &dst2, c, 0.0f);
}

void CObjCheckPoint::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	if (hit->CheckObjNameHit(OBJ_RUNNER) != nullptr) //ランナーと当たっている
	{
		;
	}
}