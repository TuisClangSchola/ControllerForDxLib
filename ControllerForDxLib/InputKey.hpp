#pragma once
#include "DxLib.h"



// キーボードの入力状態
class KeyData
{
private:
	static int m_key[256];		// キーの入力状態格納用変数
	static char m_tmpKey[256];	// 現在のキーの入力状態を格納する

public:
	static void UpDate();			// キー入力の状態更新


	// キー入力状態取得
	static int Get(const int& t_keyCode)
	{
		return m_key[t_keyCode];
	}


	// 強制終了
	static const bool IsCheckEnd()
	{
		return m_key[KEY_INPUT_ESCAPE] > 0;
	}
};