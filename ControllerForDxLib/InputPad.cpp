#include "InputPad.hpp"
namespace ps = PadStick;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

int PadData::m_button[4][16];

int PadData::m_stick[4][6];
int PadData::m_stickCheck[4][8];
int PadData::m_trigger[4][2];

short PadData::thumbLX_DeadMAX;
short PadData::thumbLX_DeadMIN;
short PadData::thumbLY_DeadMAX;
short PadData::thumbLY_DeadMIN;
short PadData::thumbRX_DeadMAX;
short PadData::thumbRX_DeadMIN;
short PadData::thumbRY_DeadMAX;
short PadData::thumbRY_DeadMIN;

XINPUT_STATE PadData::m_input[4];

char PadData::m_padNum = -1;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
	, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN)
{
	thumbLX_DeadMAX = thumbLX_MAX;
	thumbLX_DeadMIN = thumbLX_MIN;
	thumbLY_DeadMAX = thumbLY_MAX;
	thumbLY_DeadMIN = thumbLY_MIN;
	thumbRX_DeadMAX = thumbRX_MAX;
	thumbRX_DeadMIN = thumbRX_MIN;
	thumbRY_DeadMAX = thumbRY_MAX;
	thumbRY_DeadMIN = thumbRY_MIN;
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
void PadData::UpDate()
{
	// ゲームパッドの取得出来ているか
	if (m_padNum == -1) return;


	// ゲームパッドの個数だけ処理
	for (int i = 0; i < static_cast<int>(m_padNum); ++i)
	{
		// 入力状態を取得
		GetJoypadXInputState(i + 1, &m_input[i]);
	


		/// ボタン関係-----------------------------------------------------------
		{
			// 全ボタン入力処理
			for (int j = 0; j < 16; ++j)
			{
				// 押されていなかったら
				if (m_input[i].Buttons[j] == 0)
				{
					if (m_button[i][j] < 0)
					{
						m_button[i][j] = 0;
					}
					else if (m_button[i][j] > 0)
					{
						m_button[i][j] = -1;
					}
				}
				// i番のキーコードに対応するボタンが押されていたら
				else if (m_input[i].Buttons[j] == 1)
				{
					m_button[i][j]++;
				}
			}
		}
		/// ---------------------------------------------------------------------



		/// トリガー関係---------------------------------------------------------
		{
			// トリガーの入力数値を渡す
			m_trigger[i][ps::LEFT_TRIGGER] = m_input[i].LeftTrigger;
			m_trigger[i][ps::RIGHT_TRIGGER] = m_input[i].RightTrigger;
		}
		/// ---------------------------------------------------------------------



		/// スティック関係-------------------------------------------------------
		{
			// スティックのデッドゾーンを考慮した入力数値を取得
			if (m_input[i].ThumbLX > thumbLX_DeadMAX || m_input[i].ThumbLX < thumbLX_DeadMIN)
			{
				m_stick[i][ps::LEFT_STICK_X] = m_input[i].ThumbLX;
			}
			if (m_input[i].ThumbLY > thumbLY_DeadMAX || m_input[i].ThumbLY < thumbLY_DeadMIN)
			{
				m_stick[i][ps::LEFT_STICK_Y] = m_input[i].ThumbLY;
			}
			if (m_input[i].ThumbRX > thumbRX_DeadMAX || m_input[i].ThumbRX < thumbRX_DeadMIN)
			{
				m_stick[i][ps::RIGHT_STICK_X] = m_input[i].ThumbRX;
			}
			if (m_input[i].ThumbRY > thumbRY_DeadMAX || m_input[i].ThumbRY < thumbRY_DeadMIN)
			{
				m_stick[i][ps::RIGHT_STICK_Y] = m_input[i].ThumbRY;
			}


			// スティックの押し倒し入力を取得
			if (m_input[i].ThumbLX == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][ps::LEFT_STICK_X - 2 - ps::THUMB_PLUS]++;
			}
			else if (m_input[i].ThumbLX == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][ps::LEFT_STICK_X - 2 - ps::THUMB_MINUS]++;
			}
			else
			{
				m_stickCheck[i][ps::LEFT_STICK_X - 2 - ps::THUMB_PLUS] = 0;
				m_stickCheck[i][ps::LEFT_STICK_X - 2 - ps::THUMB_MINUS] = 0;
			}
			if (m_input[i].ThumbLY == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][ps::LEFT_STICK_Y - 2 - ps::THUMB_PLUS]++;
			}
			else if (m_input[i].ThumbLY == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][ps::LEFT_STICK_Y - 2 - ps::THUMB_MINUS]++;
			}
			else
			{
				m_stickCheck[i][ps::LEFT_STICK_Y - 2 - ps::THUMB_PLUS] = 0;
				m_stickCheck[i][ps::LEFT_STICK_Y - 2 - ps::THUMB_MINUS] = 0;
			}
			if (m_input[i].ThumbRX == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][ps::RIGHT_STICK_X - 2 - ps::THUMB_PLUS]++;
			}
			else if (m_input[i].ThumbRX == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][ps::RIGHT_STICK_X - 2 - ps::THUMB_MINUS]++;
			}
			else
			{
				m_stickCheck[i][ps::RIGHT_STICK_X - 2 - ps::THUMB_PLUS] = 0;
				m_stickCheck[i][ps::RIGHT_STICK_X - 2 - ps::THUMB_MINUS] = 0;
			}
			if (m_input[i].ThumbRY == ps::THUMB_MAX_VALUE)
			{
				m_stickCheck[i][ps::RIGHT_STICK_Y - 2 - ps::THUMB_PLUS]++;
			}
			else if (m_input[i].ThumbRY == ps::THUMB_MIN_VALUE)
			{
				m_stickCheck[i][ps::RIGHT_STICK_Y - 2 - ps::THUMB_MINUS]++;
			}
			else
			{
				m_stickCheck[i][ps::RIGHT_STICK_Y - 2 - ps::THUMB_PLUS] = 0;
				m_stickCheck[i][ps::RIGHT_STICK_Y - 2 - ps::THUMB_MINUS] = 0;
			}
		}
		/// ---------------------------------------------------------------------
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::Get(const int& t_code, const int& t_padNum)
{
	return m_button[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
int PadData::GetStickCheck(int code, int padNum, bool plus)
{
	if (plus)
	{
		return m_stickCheck[padNum][code - 2];
	}
	else
	{
		return m_stickCheck[padNum][code - 2 - 4];
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetTrigger(const int& t_code, const int& t_padNum)
{
	return m_trigger[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool PadData::IsCheckEnd()
{
	return
	{
		(m_button[0][XINPUT_BUTTON_START] > 1 && m_button[0][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[1][XINPUT_BUTTON_START] > 1 && m_button[1][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[2][XINPUT_BUTTON_START] > 1 && m_button[2][XINPUT_BUTTON_BACK] > 1) ||
		(m_button[3][XINPUT_BUTTON_START] > 1 && m_button[3][XINPUT_BUTTON_BACK] > 1)
	};
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStick(const int& t_code, const int& t_padNum)
{
	return m_stick[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const char PadData::GetPadNum()
{
	return m_padNum;
}