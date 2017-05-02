//=========================================================================//
//======yWorldMatrix.‚–‚ƒ‚‚z
//======		ƒ[ƒ‹ƒhs—ñ‚ðŠÇ—‚µ‚Ä‚¢‚Ü‚·B
//=========================================================================//
#include "WorldMatrix.h"

OGL::WorldMatrix::WorldMatrix()
{
	D3DXMatrixIdentity(&m_WorldMatrix);
	D3DXMatrixIdentity(&m_tempMatrix);
}

OGL::WorldMatrix::~WorldMatrix()
{
}

//¡¡¡¡¡¡¡¡¡¡¡
//¡¡¡ypublicz¡¡¡
//¡¡¡¡¡¡¡¡¡¡¡
void	OGL::WorldMatrix::SetTransPos(float x, float y, float z)
{
	m_WorldMatrix._41 = x;
	m_WorldMatrix._42 = y;
	m_WorldMatrix._43 = z;
}

void	OGL::WorldMatrix::SetMatrix(D3DXMATRIX*	mat)
{
	m_WorldMatrix = *mat;
}

void	OGL::WorldMatrix::SetRotationDegree(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(
		&m_tempMatrix, D3DXToRadian(y), D3DXToRadian(x), D3DXToRadian(z));
	m_tempMatrix._41 = m_WorldMatrix._41;
	m_tempMatrix._42 = m_WorldMatrix._42;
	m_tempMatrix._43 = m_WorldMatrix._43;
	m_WorldMatrix = m_tempMatrix;
}

void	OGL::WorldMatrix::SetRotationRadian(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(&m_tempMatrix, y, x, z);
	m_tempMatrix._41 = m_WorldMatrix._41;
	m_tempMatrix._42 = m_WorldMatrix._42;
	m_tempMatrix._43 = m_WorldMatrix._43;
	m_WorldMatrix = m_tempMatrix;
}

void	OGL::WorldMatrix::AddTransVector(float x, float y, float z)
{
	m_WorldMatrix._41 += x;
	m_WorldMatrix._42 += y;
	m_WorldMatrix._43 += z;
}

void	OGL::WorldMatrix::AddRotationDegree(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(
		&m_tempMatrix, D3DXToRadian(y), D3DXToRadian(x), D3DXToRadian(z));
	D3DXMATRIX	tem, temOf;
	tem = m_WorldMatrix;
	D3DXMatrixInverse(&temOf, 0, &tem);
	m_WorldMatrix *= temOf;
	m_WorldMatrix *= m_tempMatrix;
	m_WorldMatrix *= tem;
}

void	OGL::WorldMatrix::AddRotationRadian(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(	&m_tempMatrix, y,x,z);
	D3DXMATRIX	tem, temOf;
	tem = m_WorldMatrix;
	D3DXMatrixInverse(&temOf, 0, &tem);
	m_WorldMatrix *= temOf;
	m_WorldMatrix *= m_tempMatrix;
	m_WorldMatrix *= tem;
}

void	OGL::WorldMatrix::LookForPos(D3DXVECTOR3* lookAt, D3DXVECTOR3* up)
{
	D3DXVECTOR3 X, Y, Z;
	D3DXVECTOR3	myPos = this->GetPos();
	Z = *lookAt - myPos;
	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, up), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	m_WorldMatrix._11 = X.x; m_WorldMatrix._12 = X.y; m_WorldMatrix._13 = X.z;
	m_WorldMatrix._21 = Y.x; m_WorldMatrix._22 = Y.y; m_WorldMatrix._23 = Y.z;
	m_WorldMatrix._31 = Z.x; m_WorldMatrix._32 = Z.y; m_WorldMatrix._33 = Z.z;
}

void	OGL::WorldMatrix::LookForPos(float lookX, float lookY, float lookZ,float upX, float upY, float upZ)
{
	D3DXVECTOR3	look = D3DXVECTOR3(lookX, lookY, lookZ);
	D3DXVECTOR3	up = D3DXVECTOR3(upX, upY, upZ);
	LookForPos(&look, &up);
}

void	OGL::WorldMatrix::MoveForVector(D3DXVECTOR3* vec)
{
	MoveForVector(vec->x, vec->y, vec->z);
}

void	OGL::WorldMatrix::MoveForVector(float x, float y, float z)
{
	if (x == 0 && y == 0 && z == 0)	return;
	tempVec = this->GetPos();
	tempVec.x -= x;
	tempVec.y -= y;
	tempVec.z -= z;
	D3DXVECTOR3	tempUp;
	tempUp.x = m_WorldMatrix._21;
	tempUp.y = m_WorldMatrix._22;
	tempUp.z = m_WorldMatrix._23;
	LookForPos(&tempVec, &tempUp);
	this->AddTransVector(x, y, z);
}

D3DXVECTOR3	OGL::WorldMatrix::GetPos(void)
{
	return D3DXVECTOR3(m_WorldMatrix._41, m_WorldMatrix._42, m_WorldMatrix._43);
}

D3DXMATRIX*	OGL::WorldMatrix::Getmatrix(void)
{
	return &m_WorldMatrix;
}
