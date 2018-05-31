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
}

//イニシャライズ
void CObjTrack::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 128, 128, ELEMENT_ENEMY, OBJ_TRACK, 1);
}

//アクション
void CObjTrack::Action()
{
	m_vx = -2.0f;

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//描画
void CObjTrack::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 128.0f + m_px;
	dst.m_bottom = 128.0f + m_py;

	//描画
	Draw::Draw(18, &src, &dst, c, 0.0f);
}