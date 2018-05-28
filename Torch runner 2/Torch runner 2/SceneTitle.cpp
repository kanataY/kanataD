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
	Draw::LoadImageW(L"Image\\back\\title.png", 0, TEX_SIZE_1024);

	//音楽情報の読み込み

	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(0.0f);
	//Audio::Start(0); //音楽スタート

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();
	Objs::InsertObj(obj, OBJ_TITLE, 10);
}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}