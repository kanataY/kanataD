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
#include "SceneOperation.h"
#include "GameHead.h"

//コンストラクタ
CSceneOperation::CSceneOperation()
{

}

//デストラクタ
CSceneOperation::~CSceneOperation()
{

}

//ゲームメイン初期化メソッド
void CSceneOperation::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_key.png", 0, TEX_SIZE_1024);//操作説明
	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_object.png", 1, TEX_SIZE_1024);//移すの説明
	//外部グラフィックファイルを読み込み2番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_enemy.png", 2, TEX_SIZE_1024);//敵の説明
	//外部グラフィックファイルを読み込み6番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_gimmick.png", 6, TEX_SIZE_1024);//ギミックの説明

	//外部グラフィックファイルを読み込み3番に登録(256ピクセル)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 3, TEX_SIZE_256);    //スマホ少年
	//外部グラフィックファイルを読み込み4番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\okama.png", 4, TEX_SIZE_512);    //オカマ
	//外部グラフィックファイルを読み込み5番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\object\\Track.png", 5, TEX_SIZE_512);    //トラック



	//説明オブジェクト作成
	CObjOperation* obj = new CObjOperation();
	Objs::InsertObj(obj, OBJ_OPERATION, 10);

	//バックミュージックスタート
	Audio::LoadAudio(0, L"BGM&SE\\syareotu.wav", BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CSceneOperation::Scene()
{

}