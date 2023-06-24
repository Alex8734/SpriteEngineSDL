#pragma once

#include <physicalComponents/sprite.h>
#include <fstream>
#include <vector>
#include <calculationComponents/vector3.h>
#include <physicalComponents/camera.h>
#include <data/engineData.h>	

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

#include <dirent.h>
#include <guiComponents/UI.h>
#include <manager/initializer.h>
#include <sys/stat.h>

namespace s2d
{
	namespace flc
	{
		void saveEverything(const s2d::Vector3& bg, s2d::SpriteRepository& toSave, s2d::GUIRepository& gui_repo, std::vector<std::string>& scene_names);

		void createTagSaveFile(s2d::SpriteRepository& repo);
		void createSaveFile(const SpriteRepository& spriteRepo);
		void createWindowBackgroundSaveFile(const s2d::Vector3 windowBackground);
		void createCameraSaveFile(const s2d::Camera& camera);
		void createIndexSaveFile(s2d::SpriteRepository& repo);
		void createKnownProjectDirFile();
		void createAnimtionSaveFiles(const s2d::SpriteRepository& spriteRepository);
		void createKnownAnimationFile(const s2d::SpriteRepository& spriteRepository);
		bool isProjectPathValid(const std::string& path);
		bool checkIfProjectExistInFile(std::string& ref);
		void createAnimationSaveFile(const s2d::Sprite* ptr_sprite, const s2d::Animation& animationToSave);
		void createSceneSaveFile(const std::vector<std::string>& scene_names);

		void createOrUpdatePrefabFile(const s2d::Sprite* content, const std::string& pathToFile, const std::string& pathToOldFile);

		/// <summary>
		/// Checks if the absulute path exists in the 'knownProject' file
		/// </summary>
		/// <param name="path">path to prect</param>
		/// <returns>True if there is a project</returns>
		bool checkIfProjcetAlreadyExists(const std::string& path);

		/// <summary>
		/// This method iterates over the 'createKnownProjectDirFile' and removes the
		/// projects which it cant find
		/// </summary>
		void removeInvalidPathsFromFile();
			
		/// <summary>
		/// Copies the CONTENT of the input DIR into the the output dir, 
		/// there a folder gets created with the name you provided 
		/// </summary>
		/// <param name="name">The name the folder should have</param>
		/// <returns>A absulute path to the directory</returns>
		std::string copyDir(const std::string& inputDir, const std::string& outputdir, const std::string& name);
		void removeDir(const std::string& path);

		/// <summary>
		/// For folders = "\\folder\\
		/// For files = ".cpp"
		/// </summary>
		std::string copyDir(const std::string& inputDir, const std::string& outputdir, const std::string& name, const std::vector<std::string>& exclude);

		void cleanUp(s2d::SpriteRepository& repo, bool save_sprites);

		std::string getPropertyLineWithSeperator(const Sprite* const sprite);
	}
}


