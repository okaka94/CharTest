#pragma once
#include "FBXObject.hpp"

struct AnimationState 
{
	float m_currentAnimationFrame = 0.f;
	float m_AnimationInverse = 1.f;
	// 현재 애니메이션 추가해서 애니메이션 교체가능하도록
};

class AnimationComponent
{
public:
	// 애니메이션 정보
	FBXAnimationSceneInfo	AnimationSceneInfo;
	std::map<std::string, std::vector<Matrix>>	InterpolationFrameMatrixList;
	std::map<std::string, Matrix>				BindPoseMap;
	std::map<std::string, unsigned int>			BindPoseKeyToIndexMap;

	// 애니메이션 스테이트
	AnimationState		CurrentState;

	// 현재 포즈
	BindPoseAnimationData	BPAnimData;
};

