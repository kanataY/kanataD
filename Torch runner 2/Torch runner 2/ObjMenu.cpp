//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	m_key_flag = false;
	//key_select = 0;
	//m_time = 0;
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_l = false;

	((UserData*)Save::GetData())->m_stage_count = 1;
}

//アクション
void CObjMenu::Action()
{
	
	
}

//ドロー
void CObjMenu::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"Menu", 10, 10, 100, c);

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//背景描画
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);
}