#pragma once
#ifndef _INPUTMOUSE_HPP
#define _INPUTMOUSE_HPP



// �}�E�X
class MouseData
{
private:
	static int m_mouse[3];
	static int m_mouseInput;

public:
	//���N���b�N���E�N���b�N��
	enum class ECLICK { LEFT, RIGHT, CENTER };


	//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
	static void MouseUpDate();

	//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
	static const int& GetClick(const ECLICK& t_mouseCode);
};



// �}�E�X�z�C�[��
class MouseWheelData
{
private:
	static int m_mouseWheel;
	static int m_oldMouseWheel;

public:
	//�}�E�X�̃z�C�[���̏�Ԃ��X�V
	static void MouseWheelUpDate();

	//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
	static int GetMouseWheel(int MouseWheelCode);
};


#endif // !_INPUTMOUSE_HPP