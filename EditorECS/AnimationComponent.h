#pragma once
#include "FBXObject.hpp"

struct AnimationState 
{
	float m_currentAnimationFrame = 0.f;
	float m_AnimationInverse = 1.f;
	// ���� �ִϸ��̼� �߰��ؼ� �ִϸ��̼� ��ü�����ϵ���
};

class AnimationComponent
{
public:
	// �ִϸ��̼� ����
	FBXAnimationSceneInfo	AnimationSceneInfo;
	std::map<std::string, std::vector<Matrix>>	InterpolationFrameMatrixList;
	std::map<std::string, Matrix>				BindPoseMap;
	std::map<std::string, unsigned int>			BindPoseKeyToIndexMap;

	// �ִϸ��̼� ������Ʈ
	AnimationState		CurrentState;

	// ���� ����
	BindPoseAnimationData	BPAnimData;
};

