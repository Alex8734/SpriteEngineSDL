#pragma once

#include <iostream>
#include <vector>

#include "SpriteRepository.h"
#include "GUI/GUIRepository.h"
#include "Core/SeceneHandler.h"
#include "GUI/UIUtility/UIModels.h"

namespace spe
{
	/// <summary>
	/// This class assumes your are in th engine dir
	/// </summary>
	class Savesystem
	{
	public:
		Savesystem() = delete;

		static void CreateAnimationSaveFile(const spe::Sprite* ptr_sprite, const spe::Animation& animationToSave, const spe::SpriteRepository* sprites);
		static void CreateKnownAnimationFile(const spe::SpriteRepository* sprites);

		/// <summary>
		/// Saves everything
		/// </summary>
		/// <param name="sprites">The sprites</param>
		/// <param name="gui">Camera, background</param>
		/// <param name="scene">The scenes</param>
		static void SaveEverything(const spe::SpriteRepository& sprites,
							const spe::GUIRepository& gui,
							const spe::SceneHandler& scene);

		static void SaveProjects(const std::vector<spe::UserProjectInfo>& projects);
	};
}