#include "AnimationComponent.h"

bool AnimationComponent::Tick(float tick)
{
	CurrentState.m_currentAnimationFrame += (tick * AnimationSceneInfo.FrameSpeed * CurrentState.m_AnimationInverse);
	if ((CurrentState.m_currentAnimationFrame > AnimationSceneInfo.EndFrame ) ||
		(CurrentState.m_currentAnimationFrame < AnimationSceneInfo.StartFrame))
	{
		CurrentState.m_currentAnimationFrame = min(CurrentState.m_currentAnimationFrame, AnimationSceneInfo.EndFrame);
		CurrentState.m_currentAnimationFrame = max(CurrentState.m_currentAnimationFrame, AnimationSceneInfo.StartFrame);
		CurrentState.m_AnimationInverse *= -1.0f;
	}

	UINT InterpolationIdx = CurrentState.m_currentAnimationFrame * 100; // InterpolationSampling 일단 100 고정
	
	if (BindPoseMap.empty())
	{
		auto it = FileData->InterpolationFrameMatrixList.find(m_strNodeName);
		if (it != FileData->InterpolationFrameMatrixList.end())
		{
			Matrix matTranspose = it->second[InterpolationIdx].Transpose();
			//ConstantBufferData_Bone CBData_Bone;
			BPAnimData.Bone[0] = matTranspose;
		}
//	}
//	else
//	{
//		size_t BoneIdx = 0;
		for (auto &it : BindPoseMap)
		{
			auto AnimationTrack = FileData->InterpolationFrameMatrixList.find(it.first);
			if (AnimationTrack == FileData->InterpolationFrameMatrixList.end())
			{
				BPAnimData.Bone[BoneIdx++] = it.second;
			}
			else
			{
				Matrix MergedMatrix = it.second * AnimationTrack->second[InterpolationIdx];
				BPAnimData.Bone[BoneIdx++] = MergedMatrix.Transpose();
			}
		}
		
	}

//	return true;
}