#pragma once
#include "FBXObject.hpp"

struct AnimationState 
{
	float m_currentAnimationFrame;
	float m_AnimationInverse;
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
	AnimationState		AnimState;

	// ���� ����
	BindPoseAnimationData	BPAnimData;
};

