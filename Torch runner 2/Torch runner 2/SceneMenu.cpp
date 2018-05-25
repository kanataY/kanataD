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
	//外部グラフィックファイルを読み込み0番に登録(512×512ピクセル)
	Draw::LoadImageW(L"Image\\Menu\\MenuBack.png", 0, TEX_SIZE_512);

	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(0.0f);
	//Audio::Start(0); //音楽スタート

	//メニューオブジェクト作成
	CObjMenu* obj = new CObjMenu();		//メニューオブジェクト作成
	Objs::InsertObj(obj, OBJ_MENU, 10);  //主人公オブジェクト登録
}

//ゲームメイン実行中メソッド
void CSceneMenu::Scene()
{

}