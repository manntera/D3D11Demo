//==========================
//===�yD3D11RenderManager.cpp�z
//==========================
//    DirectX11�ɂ�����
//    �`��ݒ�̊Ǘ����s���܂��B
//==========================

//=====================//
//===�y�C���N���[�h�L�q�z ===//
//=====================//
#include	"D3D11RenderManager.h"
OGL::D3D11RenderManager::D3D11RenderManager()
{
}

OGL::D3D11RenderManager::~D3D11RenderManager()
{
}

//����������������������//
//�������ypublic�z������//
//����������������������//

//��������������������������������������������
//�������@�@�\�FRenderData���Z�b�g���܂��B
//������ ����1�FD3D11RenderData*�F�����_�����O�f�[�^
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetRenderData(D3D11RenderData* data)
{
	ID3D11DeviceContext* dev=D3D11Device::GetDeviceConText();
	dev->IASetPrimitiveTopology(data->m_primitiveTopology);
	dev->IASetInputLayout(data->mp_inputLayout.Get());
	// TODO �C���X�^���X�`�掞�̊g���l���悤�ˁ[
	dev->VSSetShader(data->mp_vertexShader.Get(), NULL, 0);
	dev->HSSetShader(data->mp_hullShader.Get(),NULL,0);
	dev->DSSetShader(data->mp_domainShader.Get(), NULL, 0);
	dev->GSSetShader(data->mp_geometryShader.Get(), NULL, 0);
	dev->PSSetShader(data->mp_pixelShader.Get(), NULL, 0);
	dev->RSSetViewports(1, data->mp_viewPort.get());
	for (unsigned int i = 0; i < data->m_vsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_vsSamplerState[i].state.Get();
		dev->VSSetSamplers(data->m_vsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_hsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_hsSamplerState[i].state.Get();
		dev->HSSetSamplers(data->m_hsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_dsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_dsSamplerState[i].state.Get();
		dev->DSSetSamplers(data->m_dsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_gsSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_gsSamplerState[i].state.Get();
		dev->GSSetSamplers(data->m_gsSamplerState[i].slot, 1, &smp);
	}
	for (unsigned int i = 0; i < data->m_psSamplerState.size(); i++)
	{
		ID3D11SamplerState* smp = data->m_psSamplerState[i].state.Get();
		dev->PSSetSamplers(data->m_psSamplerState[i].slot, 1, &smp);
	}
	dev->RSSetState(data->mp_rasterizerState.Get());
	dev->OMSetDepthStencilState(data->mp_depthStencilState.Get(), data->m_writeStencilNum);
	dev->OMSetBlendState(data->mp_blendState.Get(), data->m_blendFactor, data->m_sampleMask);
}

//��������������������������������������������
//�������@�@�\�F�C���f�b�N�X�o�b�t�@���Z�b�g���܂��B
//������ ����1�FIndexBuffer*�F�C���f�b�N�X�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetIndexBuffer(IndexBuffer* buff)
{
	D3D11Device::GetDeviceConText()
		->IASetIndexBuffer(buff->mp_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

//��������������������������������������������
//�������@�@�\�F���_�o�b�t�@���Z�b�g���܂��B
//������ ����1�FVertexBuffer*�F���_�o�b�t�@
//������ ����2�FUINT�F�X���b�g
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetVertexBuffer(VertexBuffer* buff, UINT slot)
{
	UINT	stride = sizeof(D3DXVECTOR4);
	UINT	offset = 0;
	D3D11Device::GetDeviceConText()->IASetVertexBuffers(slot, 1, buff->mp_buffer.GetAddressOf(), &stride, &offset);
}

//��������������������������������������������
//�������@�@�\�F���_�V�F�[�_�ɒ萔�o�b�t�@��ݒ肵�܂��B
//������ ����1�FConstantBuffer*�F�萔�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetVsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->VSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//��������������������������������������������
//�������@�@�\�F�n���V�F�[�_�ɒ萔�o�b�t�@��ݒ肵�܂��B
//������ ����1�FConstantBuffer*�F�萔�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetHsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->HSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//��������������������������������������������
//�������@�@�\�F�h���C���V�F�[�_�ɒ萔�o�b�t�@��ݒ肵�܂��B
//������ ����1�FConstantBuffer*�F�萔�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetDsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->DSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}
//��������������������������������������������
//�������@�@�\�F�W�I���g���V�F�[�_�ɒ萔�o�b�t�@��ݒ肵�܂��B
//������ ����1�FConstantBuffer*�F�萔�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetGsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->GSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//��������������������������������������������
//�������@�@�\�F�s�N�Z���V�F�[�_�ɒ萔�o�b�t�@��ݒ肵�܂��B
//������ ����1�FConstantBuffer*�F�萔�o�b�t�@
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetPsConstantBuffer(ConstantBuffer* buffer, UINT slot)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();

	dev->PSSetConstantBuffers(slot, 1, buffer->mp_buffer.GetAddressOf());
}

//��������������������������������������������
//�������@�@�\�F���_�V�F�[�_�Ƀe�N�X�`�����\�[�X��ݒ肵�܂��B
//������ ����1�FInputTexture*�F���͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetVsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->VSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�n���V�F�[�_�Ƀe�N�X�`�����\�[�X��ݒ肵�܂��B
//������ ����1�FInputTexture*�F���͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetHsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->HSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�h���C���V�F�[�_�Ƀe�N�X�`�����\�[�X��ݒ肵�܂��B
//������ ����1�FInputTexture*�F���͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetDsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->DSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�W�I���g���V�F�[�_�Ƀe�N�X�`�����\�[�X��ݒ肵�܂��B
//������ ����1�FInputTexture*�F���͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetGsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->GSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�s�N�Z���V�F�[�_�Ƀe�N�X�`�����\�[�X��ݒ肵�܂��B
//������ ����1�FInputTexture*�F���͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetPsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		ID3D11ShaderResourceView* srv = inputTex->inputData[i].p_srv;
		dev->PSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�o�͂����e�N�X�`����ݒ肵�܂��B
//������ ����1�FOutputTexture*�F�o�͂���e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::SetOutputTexture(OutputTexture* outputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11RenderTargetView** rtv = outputTex->mp_rtv;
	dev->OMSetRenderTargets(8, rtv, outputTex->mp_dsv);
}

//��������������������������������������������
//�������@�@�\�F���_�V�F�[�_�ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearVsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->VSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�n���V�F�[�_�ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearHsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->HSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�h���C���V�F�[�_�ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearDsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->DSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�W�I���g���V�F�[�_�ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearGsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->GSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�s�N�Z���V�F�[�_�ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearPsInputTexture(InputTexture* inputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11ShaderResourceView* srv = nullptr;
	for (unsigned int i = 0; i < inputTex->inputData.size(); i++)
	{
		dev->PSSetShaderResources(inputTex->inputData[i].slot, 1, &srv);
	}
}

//��������������������������������������������
//�������@�@�\�F�o�͂����e�N�X�`���ɐݒ肵�Ă����e�N�X�`�����\�[�X���������܂��B
//������ ����1�FInputTexture*�F���͂��Ă����e�N�X�`��
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::ClearOutputTexture(OutputTexture* outputTex)
{
	ID3D11DeviceContext* dev = D3D11Device::GetDeviceConText();
	ID3D11RenderTargetView* rtv[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	ID3D11DepthStencilView* dsv = nullptr;
	dev->OMSetRenderTargets(8, rtv, dsv);
}

//��������������������������������������������
//�������@�@�\�F�`������s���܂��B
//������ ����1�FUINT�F�`�悷��C���f�b�N�X��
//������ ����1�FUINT�F�`����J�n����C���f�b�N�X�l
//������ ����1�FUINT�F�e�C���f�b�N�X�ɉ��Z����l
//������   �Ԓl�Fvoid
//��������������������������������������������
void	OGL::D3D11RenderManager::Draw(UINT drawIndexCount, UINT startIndexOffset, int addIndex)
{
	D3D11Device::GetDeviceConText()->DrawIndexed(drawIndexCount, startIndexOffset, addIndex);
}