//=========================================================================//
//======【WorldMatrix.cpp 】
//======		ワールド行列を管理しています。
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
	class WorldMatrix
	{
	private:
		D3DXMATRIX	m_WorldMatrix;
		D3DXMATRIX	m_tempMatrix;
		D3DXVECTOR3 tempVec;

	public:
		WorldMatrix();
		~WorldMatrix();
		void	SetMatrix(D3DXMATRIX*	mat);

		void	SetTransPos(float x, float y, float z);
		void	SetRotationDegree(float x, float y, float z);
		void	SetRotationRadian(float x, float y, float z);
		void	AddTransVector(float x, float y, float z);
		void	AddRotationDegree(float x, float y, float z);
		void	AddRotationRadian(float x, float y, float z);

		void	LookForPos(D3DXVECTOR3* lookAt, D3DXVECTOR3* up);
		void	LookForPos(float lookX, float lookY, float lookZ, float upX, float upY, float upZ);
		void	MoveForVector(D3DXVECTOR3* vec);
		void	MoveForVector(float x, float y, float z);

		D3DXVECTOR3	GetPos(void);
		D3DXMATRIX*	Getmatrix(void);
	};
}