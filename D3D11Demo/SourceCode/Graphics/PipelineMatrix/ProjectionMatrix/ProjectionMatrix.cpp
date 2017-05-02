//=========================================================================//
//======�yPrijectionMatrix.cpp�z
//======		�v���W�F�N�V�����s����Ǘ����Ă��܂��B
//=========================================================================//
#include "ProjectionMatrix.h"

OGL::ProjectionMatrix::ProjectionMatrix()
{
	D3DXMatrixIdentity(&m_matrix);
	m_fovAngle = 45.0f;
	m_aspect = 16 / 9;
	m_nearZ = 1;
	m_farZ = 1000;
	m_perspectiveEnable = true;
}

OGL::ProjectionMatrix::~ProjectionMatrix()
{
}

//������������������������
//�������yprivate�z ������
//������������������������
//�������v���W�F�N�V�����s��̐ݒ聥����
void	OGL::ProjectionMatrix::CreateMatrix(void)
{
	if (m_perspectiveEnable) {
		D3DXMatrixPerspectiveFovLH(&m_matrix, D3DXToRadian(m_fovAngle), m_aspect, m_nearZ, m_farZ);
	}
	else {
		D3DXMatrixOrthoLH(&m_matrix, m_size.x, m_size.y, m_nearZ, m_farZ);
	}
}

//����������������������
//�������ypublic�z������
//����������������������
void	OGL::ProjectionMatrix::SetPerspectiveEnable(bool enable)
{
	m_perspectiveEnable = enable;
}
//����������p�̐ݒ聥����
void	OGL::ProjectionMatrix::SetFovangle(float angle)
{
	m_fovAngle = angle;
}

//�������A�X�y�N�g��̐ݒ聥����
void	OGL::ProjectionMatrix::SetAspect(float aspect)
{
	m_aspect = aspect;
}

//�������A�X�y�N�g�̐ݒ聥����
void	OGL::ProjectionMatrix::SetAspect(float X, float Y)
{
	m_aspect = X / Y;
	m_size.x = X;
	m_size.y = Y;
}

//�������N���b�s���O�v���[���̐ݒ聥����
void	OGL::ProjectionMatrix::SetClippingPlane(float nearP, float farP)
{
	m_nearZ = nearP;
	m_farZ = farP;
}

//�������v���W�F�N�V�����s��̎擾������
D3DXMATRIX*	OGL::ProjectionMatrix::Getmatrix(void)
{
	CreateMatrix();
	return &m_matrix;
}