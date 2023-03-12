#pragma once
#include "FBXObject.hpp"

struct AnimationState 
{
	float m_currentAnimationFrame = 0.f;
	float m_AnimationInverse = 1.f;
	BindPoseAnimationData	BPAnimData;
	// ���� �ִϸ��̼� �߰��ؼ� �ִϸ��̼� ��ü�����ϵ���
	// currentAnimation
};

class AnimationComponent
{
public:
	// �ִϸ��̼� ����
	FBXAnimationSceneInfo	AnimationSceneInfo;

	// string -> NodeName
	std::map<std::string, std::vector<Matrix>>	InterpolationFrameMatrixList;

	

	// �ִϸ��̼� ������Ʈ
	AnimationState		CurrentState;

	// ���� ����
	
};

// UpdateAnimsys(AnimationComponent, skeletal) -> Rendersys(AnimationCom + SkeletalMeshCom)

