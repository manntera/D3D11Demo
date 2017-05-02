//=========================================================================//
//======【ViewMatrix.h 】
//======		カメラ行列を管理しています。
//=========================================================================//
#pragma once

#include	<d3dx9.h>
#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")			// リンク対象ライブラリにd3dx9.libを追加
#else
#pragma comment(lib, "d3dx9.lib")			// リンク対象ライブラリにd3dx9.libを追加
#endif

namespace OGL
{
	class ViewMatrix
	{
	private:
		D3DXMATRIX m_matrix;
		D3DXVECTOR3	m_centerPos;
		D3DXVECTOR3	m_rot;
		float	m_length;
	private:
		void	CreateMatrix(void);
	public:
		ViewMatrix();
		~ViewMatrix();
		void	SetCenterPos(float x, float y, float z);
		void	SetRotation(float x, float y, float z);
		void	SetLength(float length);
		void	AddCenterPos(float x, float y, float z);
		void	AddRotation(float x, float y, float z);
		void	AddLength(float length);
		void	UpdateDebugCamera(void);
		D3DXMATRIX*	Getmatrix(void);
	};
}