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

	//外部グラフィックファイルを読み込み0番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back.png", 1, TEX_SIZE_512); //背景仮

	//主人公オブジェクト作成
	CObjRunner* obj = new CObjRunner();
	Objs::InsertObj(obj, OBJ_RUNNER, 12);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

