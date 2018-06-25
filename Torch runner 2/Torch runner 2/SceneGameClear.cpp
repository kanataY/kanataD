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
#include "SceneGameClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameClear::CSceneGameClear()
{

}

//デストラクタ
CSceneGameClear::~CSceneGameClear()
{

}

//初期化メソッド
void CSceneGameClear::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\Fire.png", 0, TEX_SIZE_320);
	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear1.png", 1, TEX_SIZE_800);
	//外部グラフィックファイルを読み込み2番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear2.png", 2, TEX_SIZE_800);
	//外部グラフィックファイルを読み込み3番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear3.png", 3, TEX_SIZE_800);
	//外部グラフィックファイルを読み込み4番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear_mozi.png", 4, TEX_SIZE_512);
	//外部グラフィックファイルを読み込み5番に登録(64ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\o.png", 5, TEX_SIZE_64);
	//外部グラフィックファイルを読み込み5番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear.png", 6, TEX_SIZE_1024);
	
	Audio::LoadAudio(1, L"BGM&SE\\BGMClear_.wav", BACK_MUSIC);
	

	//クリアオブジェクト作成
	CObjGameClear* obj = new CObjGameClear();		//クリアオブジェクト作成
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//クリアオブジェクト登録
}

//実行中メソッド
void CSceneGameClear::Scene()
{


}