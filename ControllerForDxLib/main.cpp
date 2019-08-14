#include "InputKey.hpp"
#include "InputPad.hpp"
#include "InputMouse.hpp"
#include "DxLib.h"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 640;
	int winHeight = 480;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("ControllerForDxLib");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth / 2, winHeight / 2);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��

	// �L�[�{�[�h�̏�����
	KeyData::UpDate();


	// �Q�[���p�b�h�̏�����
	PadData::SetPadNum();
	PadData::SetDedZone(20000, -20000, 20000, -20000, 20000, -20000, 20000, -20000);
	PadData::UpDate();


	// �}�E�X�̏�����
	MouseData::MouseUpDate();
	// �}�E�X�z�C�[���̏�����
	MouseWheelData::MouseWheelUpDate();


	// demo
	int x = 100;
	int y = 100;
	int red = 255;
	int green = 0;
	int blue = 0;
	

	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd())
	{
		KeyData::UpDate();						// �L�[�{�[�h�̃��[�v����
		PadData::UpDate();						// �Q�[���p�b�h�̃��[�v����
		MouseData::MouseUpDate();				// �}�E�X�̃��[�v����
		MouseWheelData::MouseWheelUpDate();		// �}�E�X�z�C�[���̃��[�v����

		printfDx("%d\n", MouseData::GetClick(MouseData::ECLICK::CENTER));


		/// demo---------------------------------------------------------------------------------
		if (KeyData::Get(KEY_INPUT_W) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, false) > 0)
		{
			y--;
		}
		if (KeyData::Get(KEY_INPUT_S) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_Y, 0, true) > 0)
		{
			y++;
		}
		if (KeyData::Get(KEY_INPUT_A) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, true) > 0)
		{
			x--;
		}
		if (KeyData::Get(KEY_INPUT_D) > 0 || PadData::GetStickCheck(PadStick::LEFT_STICK_X, 0, false) > 0)
		{
			x++;
		}
		if (PadData::GetTrigger(PadStick::LEFT_TRIGGER, 0) == 255)
		{
			if (green < 255) green++;
		}
		if (PadData::GetTrigger(PadStick::RIGHT_TRIGGER, 0) == 255)
		{
			if (green > 0) green--;
		}
		if (PadData::GetStick(PadStick::RIGHT_STICK_X, 0) > 0)
		{
			if (blue < 255) blue++;
		}
		if (PadData::GetStick(PadStick::RIGHT_STICK_X, 0) < 0)
		{
			if (blue > 0) blue--;
		}
		DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(red, green, blue), true);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%dx%d, GetColor(255, %d, %d)", x, y, green, blue);
		/// -------------------------------------------------------------------------------------
	}

	// �폜
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}