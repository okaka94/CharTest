#pragma once
#include "Define.h"
//#include "DXTexture.hpp"
//#include "Material.h"
#include "SkeletalMesh.h"
//#include "MeshComponent.hpp"
//#include "DXShaderManager.h"
#include "TransformComponent.h"
#include "FBXObject.hpp"
#include "Camera.h"

class AnimationComponent;

class SkeletalMeshComponent
{
public:

	std::map<std::string, Matrix>				BindPoseMap;
	std::map<std::string, unsigned int>			BindPoseKeyToIndexMap;
	ID3D11Buffer*								BoneBuffer = nullptr;
	BindPoseAnimationData						BoneData;

	std::vector<SkeletalMesh> Meshes; // 정점, IW 메시데이터 


	ID3D11InputLayout* VertexLayout = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11HullShader* HullShader = nullptr;
	ID3D11DomainShader* DomainShader = nullptr;
	ID3D11GeometryShader* GeometryShader = nullptr;
	ID3D11Buffer* TransformBuffer = nullptr;
	TransformMatrix			TransformData;

	ID3D11Buffer* CameraMatrixBuffer = nullptr;

	bool isCreated = false;

public:
	SkeletalMeshComponent();
	virtual ~SkeletalMeshComponent();
public:
	virtual bool Render();
	virtual bool Initialize();
public:
	bool UpdatePose(const AnimationComponent& anim);
	virtual void UpdateTransformMatrix(const TransformComponent& transform);
	virtual void UpdateCamera(Camera* camera, const TransformComponent& transform);
};
