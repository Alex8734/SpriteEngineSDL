#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ImGui.h>
#include <manager/initializer.h>

namespace s2d
{
	class UIInfo
	{
		UIInfo() = delete;

	public:
		static float s_defaultFontSize;
		static bool s_renderAssetFolder;
		static bool s_isAssetFolderActive;

		static std::string s_folderIcon;
		static std::string s_defaultIcon;
	};
}

