#pragma once
#ifndef _INPUTMOUSE_HPP
#define _INPUTMOUSE_HPP



// �}�E�X
class MouseData
{
private:
	static int m_mouse[3];
	static int m_mouseInput;
	struct MouseXY
	{
		int x;
		int y;
	};
	static MouseXY m_preMouseArea;
	static MouseXY m_mouseArea;


public:
	//���N���b�N���E�N���b�N��
	enum class ECLICK { LEFT, RIGHT, CENTER };


	//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
	static void UpDate();

	//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
	static const int& GetClick(const ECLICK& t_mouseCode);

	// ���݂̃}�E�X�̈ʒu
	static const MouseXY& GetMouseArea();

	// ���O����ǂꂭ�炢�ړ�������
	static const MouseXY GetMouseMoveValue();
};



// �}�E�X�z�C�[��
class MouseWheelData
{
private:
	static int m_mouseWheel;
	static int m_oldMouseWheel;


public:
	//�}�E�X�̃z�C�[���̏�Ԃ��X�V
	static void UpDate();

	//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
	static const int& GetMouseWheel();
};


#endif // !_INPUTMOUSE_HPP