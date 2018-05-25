//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneGameOver.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//初期化メソッド
void CSceneGameOver::InitScene()
{
	//音楽読み込み
	/*Audio::LoadAudio(0, L"gameover.wav", BACK_MUSIC);

	//ボリュームを1.0fに戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((1.0 - v));

	//音楽スタート
	Audio::Start(0);*/

	//外部グラフィックファイルを読み込み0番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER4.png", 1, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み1番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER1_Font.png", 2, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み2番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER2_Font.png", 3, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み3番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER3_Font.png", 4, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み4番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GAMEOVER4_Font.png", 5, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み6番に登録(512×512ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\Menutransfer.png", 6, TEX_SIZE_512);

	//外部グラフィックファイルを読み込み7番に登録(1024×1024ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\GameOver.png", 7, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み8番に登録(512×512ピクセル)
	Draw::LoadImageW(L"Image\\GameOver\\retry.png", 8, TEX_SIZE_512);

	//ゲームオーバーオブジェクト作成
	CObjGameOver* obj = new CObjGameOver();
	Objs::InsertObj(obj, OBJ_GAME_OVER, 10);
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}