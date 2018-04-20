//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock()
{

}

//イニシャライズ
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//位置
	m_bx = 0.0f;
	m_by = 0.0f;

	m_scroll = 0.0f;
}

//アクション
void CObjBlock::Action()
{
	//ランナーの位置を取得
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	float rx = runner->GetX();
	float ry = runner->GetY();

	//前方スクロールライン
	if (rx > 300)
	{
		runner->SetX(300);		//主人公はラインを超えないようにする
		m_scroll -= runner->GetVX();//主人公が本来動くべき分の値をm_scrollに加える

		//背景1の動作
		m_bx -= runner->GetVX();
		if (m_bx < -800.0f)
			m_bx = 800.0f;

	}
}

//描画
void CObjBlock::Draw()
{
	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//表示位置の設定
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 512.0f + m_bx;
	dst.m_bottom = 512.0f ;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}