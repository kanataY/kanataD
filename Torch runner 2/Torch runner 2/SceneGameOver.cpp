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
	Draw::LoadImageW(L"Image\\back\\gameover\\GameOver.png", 0, TEX_SIZE_1024);

	//ゲームオーバーオブジェクト作成
	CObjGameOver* obj = new CObjGameOver();
	Objs::InsertObj(obj, OBJ_GAME_OVER, 10);

	Audio::LoadAudio(0, L"BGM&SE\\BGMGameOver_.wav", BACK_MUSIC);
	//音楽スタート
	Audio::Start(0);
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}