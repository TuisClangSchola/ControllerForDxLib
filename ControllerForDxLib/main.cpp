#include "InputKey.hpp"
#include "InputPad.hpp"



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 1920;
	int winHeight = 1080;
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
	SetWindowSize(winWidth, winHeight);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\�����\���ɂ���


	KeyData::UpDate();


	PadData::PadData();
	PadData::UpDate();


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && KeyData::CheckEnd() && PadData::CheckEnd())
	{
		KeyData::UpDate();
		PadData::UpDate();
	}

	// �폜
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}