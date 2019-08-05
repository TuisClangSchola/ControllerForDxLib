#pragma once
#include "DxLib.h"



#ifndef _INPUTCONTROLLER_H
#define _INPUTCONTROLLER_H
namespace PadStick
{
	const int LEFT_TRIGGER = 0;
	const int RIGHT_TRIGGER = 1;
	const int  LEFT_STICK_X = 2;
	const int  LEFT_STICK_Y = 3;
	const int  RIGHT_STICK_X = 4;
	const int  RIGHT_STICK_Y = 5;

	const int  THUMB_MAX_VALUE = 32767;
	const int  THUMB_MIN_VALUE = -32768;
}
#endif // !_INPUTCONTROLLER_H



// �Q�[���p�b�h�̓��͏��
class PadData 
{
private:
	static int m_button[4][16];		// �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
	static int m_stick[4][6];		// �Q�[���p�b�h�̃X�e�B�b�N�֘A�̓��͏�Ԏ��[�p�ϐ�
	static int m_stickCheck[4][8];	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ��[�p�ϐ��̍ő�܂ł̓|���`�F�b�N
	static int m_trigger[4][2];		// �Q�[���p�b�h�̃g���K�[�̓��͏�Ԏ��[�p�ϐ�


	// �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
	static short stickLX_DeadMAX;
	static short stickLX_DeadMIN;
	static short stickLY_DeadMAX;
	static short stickLY_DeadMIN;
	static short stickRX_DeadMAX;
	static short stickRX_DeadMIN;
	static short stickRY_DeadMAX;
	static short stickRY_DeadMIN;


	static XINPUT_STATE m_input[4];	// �Q�[���p�b�h�̃i���o�[
	static char m_padNum;			// �q�����Ă�Q�[���p�b�h�̐�


	enum class EStickCheck 
	{
		LEFT_STICK_LEFT, LEFT_STICK_DOWN, RIGHT_STICK_LEFT, RIGHT_STICK_DOWN
		, LEFT_STICK_RIGHT, LEFT_STICK_UP, RIGHT_STICK_RIGHT, RIGHT_STICK_UP
	};



public:
	static void UpDate();		// �Q�[���p�b�h�̓��͂̏�ԍX�V


	static const int GetButton(const int& t_code, const int& t_padNum);									// �{�^���̓��͏�Ԏ擾
	static const int GetTrigger(const int& t_code, const int& t_padNum);								// �g���K�[�̎擾
	static const int GetStick(const int& t_code, const int& t_padNum);									// �X�e�B�b�N�̓��͏�Ԏ擾
	static const int GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftOrDown);	// �X�e�B�b�N�̉����|���擾


	static const bool IsCheckEnd();																		// �����I��
	static const char GetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h�̐�


	static inline void SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
		, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN);					// �f�b�h�]�[���̐ݒ�
	static inline void SetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h���擾����
};



/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
inline void PadData::SetDedZone(short thumbLX_MAX, short thumbLX_MIN, short thumbLY_MAX, short thumbLY_MIN
	, short thumbRX_MAX, short thumbRX_MIN, short thumbRY_MAX, short thumbRY_MIN)
{
	stickLX_DeadMAX = thumbLX_MAX;
	stickLX_DeadMIN = thumbLX_MIN;
	stickLY_DeadMAX = thumbLY_MAX;
	stickLY_DeadMIN = thumbLY_MIN;
	stickRX_DeadMAX = thumbRX_MAX;
	stickRX_DeadMIN = thumbRX_MIN;
	stickRY_DeadMAX = thumbRY_MAX;
	stickRY_DeadMIN = thumbRY_MIN;
}



/// ------------------------------------------------------------------------------------------------------------
inline void PadData::SetPadNum()
{
	if (GetJoypadNum() > 0)
	{
		m_padNum = static_cast<char>(GetJoypadNum());
	}
	else
	{
		m_padNum = -1;
	}
}