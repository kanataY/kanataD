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
	Draw::LoadImageW(L"Image\\run.png", 0, TEX_SIZE_64);    //人間仮

	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back1.png", 1, TEX_SIZE_1024); //背景仮

	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 12);

	//主人公オブジェクト作成
	CObjBlock* block = new CObjBlock();
	Objs::InsertObj(block, OBJ_BLOCK, 12);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

