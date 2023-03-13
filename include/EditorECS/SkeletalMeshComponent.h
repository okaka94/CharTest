#pragma once
#include "Define.h"
#include "DXTexture.hpp"
#include "Material.h"
#include "MeshComponent.hpp"
#include "DXShaderManager.h"
#include "TransformComponent.h"
#include "FBXObject.hpp"

class SkeletalMeshComponent
{
public:

	std::map<std::string, Matrix>				BindPoseMap;
	std::map<std::string, unsigned int>			BindPoseKeyToIndexMap;


	std::vector<MeshComponent> Meshes; // 정점, IW 메시데이터 
	ID3D11InputLayout* VertexLayout = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11HullShader* HullShader = nullptr;
	ID3D11DomainShader* DomainShader = nullptr;
	ID3D11GeometryShader* GeometryShader = nullptr;
	ID3D11Buffer* TransformBuffer = nullptr;
	TransformMatrix			TransformData;

	bool isCreated = false;

public:
	SkeletalMeshComponent();
	virtual ~SkeletalMeshComponent();
public:
	virtual bool Render();
	virtual bool Initialize();
public:
	virtual void UpdateTransformMatrix(const TransformComponent& transform);
};
