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
#include "SceneMenu.h"
#include "GameHead.h"

//コンストラクタ
CSceneMenu::CSceneMenu()
{

}

//デストラクタ
CSceneMenu::~CSceneMenu()
{

}

//ゲームメイン初期化メソッド
void CSceneMenu::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu.png", 0, TEX_SIZE_1024);

	//外部グラフィックファイルを読み込み1番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_start.png", 1, TEX_SIZE_512);//ステージセレクトロゴ

    //外部グラフィックファイルを読み込み2番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_ranking.png", 2, TEX_SIZE_512);//rankingロゴ

	//外部グラフィックファイルを読み込み3番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_title.png", 3, TEX_SIZE_512);//titleに戻るロゴ

	//外部グラフィックファイルを読み込み4番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_operation.png", 4, TEX_SIZE_512);//操作説明ロゴ

	//外部グラフィックファイルを読み込み5番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_start_red.png", 5, TEX_SIZE_512);//ステージセレクトロゴ(赤)

	//外部グラフィックファイルを読み込み6番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_ranking_red.png", 6, TEX_SIZE_512);//rankingロゴ(赤)

    //外部グラフィックファイルを読み込み7番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_title_red.png", 7, TEX_SIZE_512);//titleに戻るロゴ(赤)

	//外部グラフィックファイルを読み込み8番に登録(512ピクセル)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_operation_red.png", 8, TEX_SIZE_512);//操作説明ロゴ(赤)
	
	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(0.0f);
	Audio::LoadAudio(0, L"BGM&SE\\Menu.wav", BACK_MUSIC);
	//音楽スタート
	Audio::Start(0);

	//メニューオブジェクト作成
	CObjMenu* obj = new CObjMenu();		//メニューオブジェクト作成
	Objs::InsertObj(obj, OBJ_MENU, 10);  //主人公オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneMenu::Scene()
{

}