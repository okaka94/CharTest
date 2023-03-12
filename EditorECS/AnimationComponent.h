#pragma once
#include "FBXObject.hpp"

struct AnimationState 
{
	float m_currentAnimationFrame = 0.f;
	float m_AnimationInverse = 1.f;
	BindPoseAnimationData	BPAnimData;
	// 현재 애니메이션 추가해서 애니메이션 교체가능하도록
	// currentAnimation
};

class AnimationComponent
{
public:
	// 애니메이션 정보
	FBXAnimationSceneInfo	AnimationSceneInfo;

	// string -> NodeName
	std::map<std::string, std::vector<Matrix>>	InterpolationFrameMatrixList;

	

	// 애니메이션 스테이트
	AnimationState		CurrentState;

	// 현재 포즈
	
};

// UpdateAnimsys(AnimationComponent, skeletal) -> Rendersys(AnimationCom + SkeletalMeshCom)

