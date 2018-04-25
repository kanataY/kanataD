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
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;

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
		m_bx1 -= runner->GetVX();
		if (m_bx1 < -800.0f)
			m_bx1 = 800.0f;

		//背景2の動作
		m_bx2 -= runner->GetVX();
		if (m_bx2 < -800.0f)
			m_bx2 = 800.0f;
	}

	//後方
	if (m_scroll > -1)//スクロールの場所によってスクロールの入る場所を変える
	{
		if (m_scroll > -1.0f && rx < 50)//初期位置よりも後ろにいけない
		{
			runner->SetX(50.0f);//初期位置に戻す
		}
		else if (rx < 50)
		{
			runner->SetX(50);			//主人公はラインを超えないようにする
			m_scroll -= runner->GetVX();//主人公が本来動くべき分の値をm_scrollに加える

									  //背景1の動作
			m_bx1 -= runner->GetVX();
			if (m_bx1 > 800.0f)
				m_bx1 = -800.0f;

			//背景2の動作
			m_bx2 -= runner->GetVX();
			if (m_bx2 > 800.0f)
				m_bx2 = -800.0f;
		}
	}
	else
	{
		if (rx < 200)
		{
			runner->SetX(200);			//主人公はラインを超えないようにする
			m_scroll -= runner->GetVX();//主人公が本来動くべき分の値をm_scrollに加える

			//背景1の動作
			m_bx1 -= runner->GetVX();
			if (m_bx1 > 800.0f)
				m_bx1 = -800.0f;

			//背景2の動作
			m_bx2 -= runner->GetVX();
			if (m_bx2 > 800.0f)
				m_bx2 = -800.0f;
		}
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
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//表示位置の設定
	//背景１
	dst.m_top = 0.0f ;
	dst.m_left = 0.0f + m_bx1;
	dst.m_right = 800.0f + m_bx1;
	dst.m_bottom = 700.0f ;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//背景２
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_bx2;
	dst.m_right = 805.0f + m_bx2;
	dst.m_bottom = 700.0f;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}