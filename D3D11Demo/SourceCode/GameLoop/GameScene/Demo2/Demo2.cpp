//==========================
//===�yDemo2.cpp�z
//==========================
//    �Q�[���{�̉�ʂ̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"../GameSceneList.h"
#include	"../../GameLoopManager/GameLoopManager.h"
#include	"../../../Window/Window.h"

//��������������������������������������//
//�������V�[���̏��������s���܂��B������//
//��������������������������������������//
void	OGL::Demo2::Init(void)
{
	//--------
	// RenderData�̐ݒ�
	//--------
	ViewPort				viewPort;
	VertexShader		vsSprite;
	GeometryShader	gsSprite;
	PixelShader			psSprite;
	//�r���[�|�[�g�ݒ�
	viewPort.SetRange(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	//�V�F�[�_�[�֘A�ݒ�
	vsSprite.SetInputLayoutNum(2);
	vsSprite.SetInputLayoutData(0, "RECT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	vsSprite.SetInputLayoutData(1, "COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);
	vsSprite.CreateShader("HLSL/vsSprite.hlsl", "VS", "vs_5_0");
	gsSprite.CreateShader("HLSL/gsSprite.hlsl", "GS", "gs_5_0");
	psSprite.CreateShader("HLSL/psSprite.hlsl", "PS", "ps_5_0");
	//RenderData�ɃZ�b�g
	m_renderData.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_renderData.SetViewPort(&viewPort);
	m_renderData.SetVertexShader(&vsSprite);
	m_renderData.SetGeometryShader(&gsSprite);
	m_renderData.SetPixelShader(&psSprite);

	//--------
	//�R���X�^���g�o�b�t�@�̐ݒ�
	//--------
	m_windowScale.Create(sizeof(D3DXVECTOR4));
	m_windowScale.SetResource(D3DXVECTOR4(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), 0, 0));

	//--------
	//�e�N�X�`���̐ݒ�
	//--------
	//�摜�f�[�^���[�h
	m_imageTexture.LoadFile("Resource/image1.png");
	//�C���v�b�g�e�N�X�`���ɉ摜���Z�b�g
	m_inputTexture.SetTexture(&m_imageTexture, 0);

	//�o�b�N�o�b�t�@�̐���
	m_backBuffer.Create();
	//�A�E�g�v�b�g�e�N�X�`���Ƀo�b�N�o�b�t�@��ݒ�
	m_outPutTexture.SetTexture(&m_backBuffer, 0);

	//--------
	//���_�f�[�^�̐ݒ�
	//--------
	//�C���f�b�N�X�o�b�t�@����
	int index[4] = { 0, 1, 2, 3 };
	m_indexBuffer.Create(4, index);
	//���_�o�b�t�@����
	D3DXVECTOR4 rect[4] = { { 110, 110, 100, 100 }, { 300, 300, 100, 120 }, { 600, 500, 50, 150 }, { 1000, 700, 100, 80 } };
	m_rectBuffer.Create(4, rect);
	D3DXVECTOR4 color[4] = { { 1, 1, 1, 1 }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 } };
	m_colorBuffer.Create(4, color);

	m_rpRect.SetInputTexture(&m_inputTexture);
	m_rpRect.SetPixelShader("HLSL/psSprite.hlsl");
	m_rpRect.SetRectSize(1280/2,720/2, 1280, 720);
	SamplerState ss;
	m_rpRect.SetSampler(&ss, 0);
}

//������������������������������������//
//�������V�[���̍X�V���s���܂��B������//
//������������������������������������//
void	OGL::Demo2::Update(void)
{
	//�o�b�N�o�b�t�@��ΐF�ɓh��ׂ�
	m_backBuffer.Clear(0, 1, 0, 1);
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		this->nextScene = Demo3::GetInstance();
	}
}

//������������������������������������//
//�������V�[���̕`����s���܂��B������//
//������������������������������������//
void	OGL::Demo2::Draw(void)
{
	m_rpRect.Draw(&m_outPutTexture);
	//�`������l�ߍ���
	D3D11RenderManager::SetRenderData(&m_renderData);
	D3D11RenderManager::SetVsConstantBuffer(&m_windowScale,0);
	D3D11RenderManager::SetIndexBuffer(&m_indexBuffer);
	D3D11RenderManager::SetOutputTexture(&m_outPutTexture);
	D3D11RenderManager::SetPsInputTexture(&m_inputTexture);
	D3D11RenderManager::SetVertexBuffer(&m_rectBuffer, 0);
	D3D11RenderManager::SetVertexBuffer(&m_colorBuffer, 1);
	D3D11RenderManager::Draw(4, 0, 0);
}

//����������������������������������������//
//�������V�[���̏I���������s���܂��B������//
//����������������������������������������//
void	OGL::Demo2::Uninit(void)
{
	//�e�N�X�`����j��
//	m_imageTexture.Release();
//	m_backBuffer.Release();
}