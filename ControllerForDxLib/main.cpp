#include "InputKey.hpp"
#include "InputPad.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 640;
	int winHeight = 480;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("ControllerForDxLib");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth, winHeight);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(FALSE);		// マウスカーソルを非表示にする


	KeyData::UpDate();


	PadData::PadData();
	PadData::UpDate();


	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && PadData::CheckEnd())
	{
		KeyData::UpDate();
		PadData::UpDate();


		printfDx("%d", KeyData::Get(KEY_INPUT_Z));
	}

	// 削除
	DxLib_End();		// DXライブラリの後始末


	return 0;
}