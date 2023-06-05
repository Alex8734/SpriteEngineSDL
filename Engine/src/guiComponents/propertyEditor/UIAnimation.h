#pragma once

#include <ImGui.h>
#include <data/UIInfo.h>
#include <icons.h>
#include <iostream>
#include <physicalComponents/sprite.h>
#include <UIAnimationEditor.h>
#include <manager/fontManager.h>
#include <manager/fileDialogs.h>
#include <engineComponents/input.h>

namespace s2d
{
	class UIAnimation
	{
	private:
		//Setting display to false and shit in its own class
		s2d::SpriteRepository* m_ptr_repo;
		UIAnimationEditor m_UIAnimationEditor;
		std::string m_fileName;
		s2d::FileDialog m_createAnimtionPathFileDialoge;

		bool m_openFileDialog;
		bool m_openInputWindow;
		char m_animationFile[150];

		void getFileNameInput();
		void displayAnimations();
		void addAnimationsToAnimator();
		void displayTopOfEditor();

	public:
		bool isHovered;

		UIAnimation();

		void createUIAnimationWindow();
		void setSpriteRepository(s2d::SpriteRepository& repo);
	};
}