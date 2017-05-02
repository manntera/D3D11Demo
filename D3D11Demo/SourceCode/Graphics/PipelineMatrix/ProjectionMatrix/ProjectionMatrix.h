//=========================================================================//
//======�yPrijectionMatrix.h�z
//======		�v���W�F�N�V�����s����Ǘ����Ă��܂��B
//=========================================================================//
#pragma once

#include	<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")			// �����N�Ώۃ��C�u������d3dx9.lib��ǉ�
#else
#pragma comment(lib, "d3dx9.lib")			// �����N�Ώۃ��C�u������d3dx9.lib��ǉ�
#endif

namespace OGL
{
	class ProjectionMatrix
	{
	private:
		D3DXMATRIX m_matrix;

		bool	m_perspectiveEnable;

		float	m_fovAngle;
		float	m_aspect;
		float	m_nearZ;
		float	m_farZ;

		D3DXVECTOR2	m_size;
	private:
		void	CreateMatrix(void);

	public:
		ProjectionMatrix();
		~ProjectionMatrix();
		void	SetPerspectiveEnable(bool enable);
		void	SetFovangle(float angle);
		void	SetAspect(float aspect);
		void	SetAspect(float X,float Y);
		void	SetClippingPlane(float nearP, float farP);
		D3DXMATRIX*	Getmatrix(void);
	};
}