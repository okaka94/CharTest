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

void SkeletalMeshComponent::UpdateCamera(Camera* camera, const TransformComponent& transform)
{
	if (camera == nullptr)
	{
		return;
	}

	DirectX::FXMVECTOR q = DirectX::XMQuaternionRotationRollPitchYawFromVector(Vector3(0.0f, 0.0f, 0.0f));
	TransformData.Mat = DirectX::XMMatrixAffineTransformation(transform.Scale, Vector3(0.0f, 0.0f, 0.0f), q, Vector3(0.0f, 0.0f, 0.0f));
	//TransformData.Mat = DirectX::XMMatrixAffineTransformation(transform.Scale, camera->Pos, q, camera->Pos);
	TransformData.InversedMat = DirectX::XMMatrixInverse(0, TransformData.Mat);
	TransformData.Mat = TransformData.Mat.Transpose();


	CameraMatrixData.View = camera->View;
	CameraMatrixData.View._41 = 0.0f;
	CameraMatrixData.View._42 = 0.0f;
	CameraMatrixData.View._43 = 0.0f;
	CameraMatrixData.View = CameraMatrixData.View.Transpose();


	//CameraMatrixData.Projection = DirectX::XMMatrixPerspectiveFovLH(PI * 0.25, 1.0f, 1.0f, 10000.0f);
	CameraMatrixData.Projection = camera->Projection;
	CameraMatrixData.Projection = CameraMatrixData.Projection.Transpose();

	DXDevice::g_pImmediateContext->UpdateSubresource(CameraMatrixBuffer, 0, NULL, &CameraMatrixData, 0, 0);
	DXDevice::g_pImmediateContext->VSSetConstantBuffers(1, 1, &CameraMatrixBuffer);
}