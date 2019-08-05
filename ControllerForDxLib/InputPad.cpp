#include "InputPad.hpp"
namespace ps = PadStick;



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

int PadData::m_button[4][16];
int PadData::stick[4][6];
int PadData::stickCheck[4][8];
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
	// �Q�[���p�b�h�̎擾�o���Ă��邩
	if (m_padNum == -1) return;


	// �Q�[���p�b�h�̌���������
	for (int i = 0; i < m_padNum; ++i)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(i + 1, &m_input[i]);
	

		// �S�{�^�����͏���
		for (int j = 0; j < 16; ++j)
		{
			// ������Ă��Ȃ�������
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
			// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			else if (m_input[i].Buttons[j] == 1)
			{
				m_button[i][j]++;
			}
		}

		// �g���K�[�̓��͐��l���擾
		PadData::stick[i][ps::XINPUT_LEFT_TRIGGER] = m_input[i].LeftTrigger;
		PadData::stick[i][ps::XINPUT_RIGHT_TRIGGER] = m_input[i].RightTrigger;

		// �X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾
		if (m_input[i].ThumbLX > PadData::thumbLX_DeadMAX || m_input[i].ThumbLX < PadData::thumbLX_DeadMIN)
		{
			PadData::stick[i][ps::XINPUT_LEFT_THUMB_X] = m_input[i].ThumbLX;
		}
		if (m_input[i].ThumbLY > PadData::thumbLY_DeadMAX || m_input[i].ThumbLY < PadData::thumbLY_DeadMIN)
		{
			PadData::stick[i][ps::XINPUT_LEFT_THUMB_Y] = m_input[i].ThumbLY;
		}
		if (m_input[i].ThumbRX > PadData::thumbRX_DeadMAX || m_input[i].ThumbRX < PadData::thumbRX_DeadMIN)
		{
			PadData::stick[i][ps::XINPUT_RIGHT_THUMB_X] = m_input[i].ThumbRX;
		}
		if (m_input[i].ThumbRY > PadData::thumbRY_DeadMAX || m_input[i].ThumbRY < PadData::thumbRY_DeadMIN)
		{
			PadData::stick[i][ps::XINPUT_RIGHT_THUMB_Y] = m_input[i].ThumbRY;
		}

		// �X�e�B�b�N�̉����|�����͂��擾
		if (m_input[i].ThumbLX == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (m_input[i].ThumbLX == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (m_input[i].ThumbLY == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (m_input[i].ThumbLY == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[i][ps::XINPUT_LEFT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (m_input[i].ThumbRX == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (m_input[i].ThumbRX == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_X - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
		if (m_input[i].ThumbRY == ps::XINPUT_THUMB_MAX)
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS]++;
		}
		else if (m_input[i].ThumbRY == ps::XINPUT_THUMB_MIN)
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS]++;
		}
		else
		{
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_PLUS] = 0;
			PadData::stickCheck[i][ps::XINPUT_RIGHT_THUMB_Y - 2 - ps::XINPUT_THUMB_MINUS] = 0;
		}
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
		return PadData::stickCheck[padNum][code - 2];
	}
	else
	{
		return PadData::stickCheck[padNum][code - 2 - 4];
	}
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const bool PadData::IsCheckEnd()
{
	return
	{
		(PadData::m_button[0][XINPUT_BUTTON_START] > 1 && PadData::m_button[0][XINPUT_BUTTON_BACK] > 1) ||
		(PadData::m_button[1][XINPUT_BUTTON_START] > 1 && PadData::m_button[1][XINPUT_BUTTON_BACK] > 1) ||
		(PadData::m_button[2][XINPUT_BUTTON_START] > 1 && PadData::m_button[2][XINPUT_BUTTON_BACK] > 1) ||
		(PadData::m_button[3][XINPUT_BUTTON_START] > 1 && PadData::m_button[3][XINPUT_BUTTON_BACK] > 1)
	};
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const int PadData::GetStick(const int& t_code, const int& t_padNum)
{
	return stick[t_padNum][t_code];
}



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
const char PadData::GetPadNum()
{
	return m_padNum;
}