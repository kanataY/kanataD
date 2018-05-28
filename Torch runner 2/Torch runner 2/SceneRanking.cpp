//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneRanking.h"
#include "GameHead.h"

//コンストラクタ
CSceneRanking::CSceneRanking()
{

}

//デストラクタ
CSceneRanking::~CSceneRanking()
{

}

//ランキング初期化メソッド
void CSceneRanking::InitScene()
{
	Draw::LoadImageW(L"Image\\back\\Numeric.png", 0, TEX_SIZE_256);

	Draw::LoadImageW(L"Image\\back\\ranking_mozi.png", 1, TEX_SIZE_1024);

	Draw::LoadImageW(L"Image\\back\\Bit.png", 2, TEX_SIZE_64);

	//ランキングオブジェクト作成
	CObjRanking* obj = new CObjRanking();		//ランキングオブジェクト作成
	Objs::InsertObj(obj, OBJ_RANKING, 10);		//ランキングオブジェクト登録
}

//ランキング実行中メソッド
void CSceneRanking::Scene()
{

}