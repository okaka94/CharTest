#include "SkeletalMeshComponent.h"
#include "AnimationComponent.h"

SkeletalMeshComponent::SkeletalMeshComponent() 
{
	Initialize();
}

SkeletalMeshComponent::~SkeletalMeshComponent()
{

}

// 본데이터 업데이트 -> 버퍼로 올리는 건 렌더 시스템에서
bool SkeletalMeshComponent::UpdatePose(const AnimationComponent& anim)
{
	BoneData = anim.CurrentState.BPAnimData;


	return true;
}

bool SkeletalMeshComponent::Render()
{
	DXDevice::g_pImmediateContext->IASetInputLayout(VertexLayout);
	DXDevice::g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DXDevice::g_pImmediateContext->VSSetShader(VertexShader, NULL, 0);
	DXDevice::g_pImmediateContext->HSSetShader(HullShader, NULL, 0);
	DXDevice::g_pImmediateContext->DSSetShader(DomainShader, NULL, 0);
	DXDevice::g_pImmediateContext->GSSetShader(GeometryShader, NULL, 0);
	DXDevice::g_pImmediateContext->UpdateSubresource(TransformBuffer, 0, NULL, &TransformData, 0, 0);
	DXDevice::g_pImmediateContext->VSSetConstantBuffers(0, 1, &TransformBuffer);

	// BoneBuffer Update -> Set CB
	DXDevice::g_pImmediateContext->UpdateSubresource(BoneBuffer, 0, NULL, &BoneData, 0, 0);
	DXDevice::g_pImmediateContext->VSSetConstantBuffers(2, 1, &BoneBuffer);

	DXDevice::g_pImmediateContext->PSSetConstantBuffers(4, 1, &TransformBuffer);

	for (auto& it : Meshes)
	{
		it.Render();
	}

	return true;
}

bool SkeletalMeshComponent::Initialize()
{
	if (isCreated)
	{
		return true;
	}

	// InputLayout 추가
	VertexLayout = DXShaderManager::GetInstance()->GetInputLayout(L"SkeletalMesh");
	// VS 추가
	VertexShader = DXShaderManager::GetInstance()->GetVertexShader(L"SkeletalMesh");
	TransformBuffer = DXShaderManager::GetInstance()->CreateConstantBuffer<TransformMatrix>(TransformData);
	BoneBuffer = DXShaderManager::GetInstance()->CreateConstantBuffer<BindPoseAnimationData>(BoneData);
	isCreated = true;

	return true;
}

void SkeletalMeshComponent::UpdateTransformMatrix(const TransformComponent& transform)
{
	DirectX::FXMVECTOR q = DirectX::XMQuaternionRotationRollPitchYawFromVector(transform.Rotation);
	TransformData.Mat = DirectX::XMMatrixAffineTransformation(transform.Scale, transform.Translation, q, transform.Translation);
	TransformData.InversedMat = DirectX::XMMatrixInverse(0, TransformData.Mat);
	TransformData.Mat = TransformData.Mat.Transpose();
}