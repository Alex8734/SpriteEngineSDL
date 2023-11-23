#pragma once

#include <iostream>
#include <ImGui.h>

#include "UIBase.h"
#include "Sprite/Sprite.h"
#include "GUI/GUIRepository.h"
#include "GUI/UIUtility/UIUtility.h"
#include "Utility/Style.h"
#include "Include/icons.h"

#define SPRITE_SELECTED_COLOR ImVec4(139.0f / 255.0f, 180.0f / 255.0f, 234.0f / 255.0f,1.0f)

#define POPUP_NAME "CONTEXT_MENU"
#define WINDOW_SIZE_HIERARCHY_Y 1080 - WINDOW_POS.y
#define FOLDER_SPRITE_HIERARCHY_PADDING 50

#define MENU_ITEM_PADDING 50
#define TREE_NODE_PADDING 40

#define ADD_WHEN_SPRITE_HAS_PARENT 30

#define SPRITE_BACKGROUND_COLOR ImColor(30, 30, 30, 255)

#define WINDOW_POS ImVec2(0.0f, WINDOW_SIZE_Y_TOOL_BUTTONS + 38)
#define HIERARCHY_DEFAULT_WINDOW_SIZE ImVec2(300.0f, 1080.0f - 350.0f)
// x amount of s to select a child to parent
#define TIME_TO_CAN_SELECT_CHILD 0.3f

namespace spe
{
	class UIHierarchy : public spe::IUIBase
	{
	private:
		bool m_wait_one_frame;
		ImVec2 m_window_size;
		ImGuiTextFilter m_search_sprite_filter;
		uint8_t m_sprite_background_color_cnt;
		bool m_found_hovering;
		bool m_found_selected;
		float m_child_select_timer;

		void displayContextPopup();
		bool displaySprites();
		void displaySprites(spe::Sprite* parent, bool& any_hovered);
		void displayChildToParent();
		void displaySpriteSeperated(spe::Sprite* d, bool& any_hovered);

		void setSpriteAsChild();

		void addSprite();
		void deleteSprite();
		void cleanRepoSpritesUp(bool any_hovered);
		void setMenuitemHovered(bool& any_hovered, spe::Sprite* sprite);

		void addPrefab();
		void renderCloseRectangle();
		void renderHierarchyOptions();
		void resizeWindow();

		void drawbackgroundRectangle();
		void setSpriteOnClick(spe::Sprite* sprite);
		void drawUIRactangleWhenHovered(spe::Sprite* sprite);

		void drawRenderSymbol(spe::Sprite* child);

		/// <summary>
		/// Dont forget to call PopStyleColor();
		/// </summary>
		void setSelectedBackgroundColor(spe::Sprite* sprite, bool& pop_style);

		/// <summary>
		/// Checks for specfic things which get hovered 
		/// </summary>
		void setHovering(spe::Sprite* sprite, bool& any_hovered);

		void copySprite();

		void Init() override;
	public:
		bool is_hovered;

		UIHierarchy();
		UIHierarchy(spe::SpriteRepository& repo);
		void Render() override;
	};
}

