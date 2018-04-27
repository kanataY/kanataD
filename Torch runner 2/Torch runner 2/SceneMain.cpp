//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain()
{

}


//デストラクタ
CSceneMain::~CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\hero\\run.png", 0, TEX_SIZE_64);    //人間仮

	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back1.png", 1, TEX_SIZE_1024); //背景仮  1

	//外部グラフィックファイルを読み込み2番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\back2.png", 2, TEX_SIZE_1024); //背景仮   2

	//外部グラフィックファイルを読み込み3番に登録(192ピクセル)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 3, TEX_SIZE_192);    //ゲージ

	//外部グラフィックファイルを読み込み4番に登録(128ピクセル)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 4, TEX_SIZE_64);    //木箱

	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock();
	Objs::InsertObj(block, OBJ_BLOCK, 12);

	//ゲージオブジェクト作成
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

	//木箱
	CObjCrates* crates = new CObjCrates();
	Objs::InsertObj(crates, OBJ_CRATES, 13);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

