//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneTitle.h"
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\title\\title_back.png", 0, TEX_SIZE_1024);//背景

	//外部グラフィックファイルを読み込み1番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\title\\title_title.png", 1, TEX_SIZE_512);//タイトルの文字

	//外部グラフィックファイルを読み込み2番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\title\\title_menu.png", 2, TEX_SIZE_512);//メニューの文字

	//外部グラフィックファイルを読み込み3番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\title\\title_exit.png", 3, TEX_SIZE_512);//終了の文字

	//外部グラフィックファイルを読み込み2番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\back\\title\\Frame.png", 4, TEX_SIZE_512);//枠

	//音楽情報の読み込み

	//バックミュージックスタート
	Audio::LoadAudio(0, L"BGM&SE\\BGMTitle_.wav", BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();
	Objs::InsertObj(obj, OBJ_TITLE, 10);
}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}