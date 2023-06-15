#include "UIAnimation.h"

s2d::UIAnimation::UIAnimation()
{
	this->m_UIAnimationEditor.resetAnim();
	this->m_fileName = "";
	const std::string pathToAssets = s2d::EngineData::s_path_to_user_project + "\\" + "assets\\";
	this->m_createAnimtionPathFileDialoge = s2d::FileDialog(pathToAssets, ICON_FA_PLUS, "Create Animation", ImVec2(500, 250));
	this->m_createAnimtionPathFileDialoge.setFirstNode("assets");
	this->m_background_counter = START_CNT_BG;
}

//Public functions

void s2d::UIAnimation::createUIAnimationWindow()
{
	if (!s2d::UIInfo::s_is_animation_open.is_open)
	{
		this->is_hovered = false;
		return;
	}
	if (this->m_UIAnimationEditor.display)
	{
		this->m_UIAnimationEditor.displayEditor();
		this->is_hovered = this->m_UIAnimationEditor.is_hovered;
	}
	else
	{
		this->m_background_counter = START_CNT_BG;
		ImGui::Begin("##Animations", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

		this->displayTopOfEditor();
		this->getFileNameInput();
		this->displayAnimations();
		this->addAnimationsToAnimator();

		ImGui::SetWindowSize(WINDOW_SIZE_ANIMATION_CREATE);

		if (!this->is_hovered)
			this->is_hovered = s2d::UI::isHovered(ImGui::GetWindowPos(), ImGui::GetWindowSize());
		ImGui::End();
	}
}

void s2d::UIAnimation::setSpriteRepository(s2d::SpriteRepository& repo)
{
	this->m_ptr_repo = &repo;
	this->m_UIAnimationEditor.setSpriteRepository(repo);
}

//Private functions

void s2d::UIAnimation::getFileNameInput()
{
	//Open popup
	if (s2d::FontManager::displaySmybolAsButton(ICON_FA_PLUS, s2d::UIInfo::s_default_font_size - 0.2f))
	{
		this->m_openFileDialog = true;
		this->m_createAnimtionPathFileDialoge.enableWindow();
		this->m_openInputWindow = true;
	}

	ImGui::SameLine();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2);
	ImGui::SetWindowFontScale(s2d::UIInfo::s_default_font_size - 0.2f);
	ImGui::Text("Add animations");
	ImGui::Separator();
	ImGui::SetWindowFontScale(s2d::UIInfo::s_default_font_size);

	if (this->m_openFileDialog)
	{
		if (this->m_createAnimtionPathFileDialoge.pathClicked == ""
			&& !this->m_createAnimtionPathFileDialoge.closeWindow())
		{
			this->m_createAnimtionPathFileDialoge.enableWindow();
			this->m_createAnimtionPathFileDialoge.displayNodes();
		}
	}

	if (this->m_createAnimtionPathFileDialoge.pathClicked == "")
	{
		return;
	}

	if(ImGui::Begin("##CreateAnimtion", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		ImVec2 old = ImGui::GetCursorPos();
		ImVec2 closeCursorPos = ImVec2(ImGui::GetCursorPosX() + 250, ImGui::GetCursorPosY() - 5);
		ImGui::SetCursorPos(closeCursorPos);

		// Clicked at the "x", stop displaying the file dialoge
		if (ImGui::Button("x") || s2d::Input::onKeyPress(s2d::KeyBoardCode::Escape))
		{
			this->m_openInputWindow = false;
			this->m_openFileDialog = false;
			this->m_animationFile[0] = '\0';
			s2d::UIInfo::s_is_animation_open.is_open = false;
			this->m_createAnimtionPathFileDialoge.disableWindow();
		}
		ImGui::SetCursorPos(old);

		ImGui::InputTextWithHint("##addFile", "<name>", this->m_animationFile, CHAR_MAX);
		if (ImGui::IsItemHovered() || ImGui::IsItemFocused())
		{
			this->is_hovered = true;
		}
		const std::string path = s2d::UI::getUserProjectPathSeperatetFromEnginePath(this->m_createAnimtionPathFileDialoge.pathClicked);
		std::string createAnimtionAt = "Create animation file at: " + path;
		ImGui::Text(createAnimtionAt.c_str());
		ImGui::Text("Press Enter when u are done giving it a name");
		ImGui::SetWindowSize(ImVec2(WINDOW_SIZE_ANIMATION_CREATE.x, 120));
		ImGui::End();
	}
}

void s2d::UIAnimation::displayAnimations()
{
	ImGui::Dummy(ImVec2(0, 7)); 
	for (auto& anim : this->m_ptr_repo->sprite_in_inspector->animator.animations)
	{
		this->drawBackgroundBehinAnimation();
		if (ImGui::Selectable(anim.second.name.c_str(), false, ImGuiSelectableFlags_DontClosePopups,
			ImVec2(ImGui::CalcTextSize(anim.second.name.c_str()).x, 0)))
		{
			this->enterAnimation(anim.second);
		}

		std::string s = "#" + anim.second.name;
		std::string deleteButton = ICON_FA_TRASH "##" + anim.second.name;

		if (s2d::FontManager::displaySmybolAsButton(deleteButton.c_str(),
			ImVec2(WINDOW_SIZE_ANIMATION_CREATE.x - 50, ImGui::GetCursorPosY() - 30)))
		{
			this->m_ptr_repo->sprite_in_inspector->animator.removeAnimation(anim.second.name);
			break;
		}
	}
	
}

void s2d::UIAnimation::displayTopOfEditor()
{
	ImGui::Text("Animations");
	ImGui::SameLine();
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 345 , ImGui::GetCursorPosY() - 10));

	//Close button
	if (ImGui::Button("x"))
	{
		s2d::UIInfo::s_is_animation_open.is_open = false;
	}

	ImGui::Separator();
}

void s2d::UIAnimation::enterAnimation(s2d::Animation& animation)
{
	this->m_UIAnimationEditor.setAnim(&animation);
	this->m_UIAnimationEditor.displayEditor();
}

void s2d::UIAnimation::drawBackgroundBehinAnimation()
{
	if (this->m_background_counter < 1)
	{
		this->m_background_counter++;
		return;
	}
	this->m_background_counter = 0;

	const ImVec2 temp = ImGui::GetCursorPos();
	ImGui::SetCursorPosX(ImGui::GetWindowPos().x);
	ImGui::SetCursorPosY(ImGui::GetWindowPos().y + ImGui::GetCursorPosY() + 23);
	s2d::UI::drawRectangleInGUIWIndow(ImVec2(WINDOW_SIZE_ANIMATION_CREATE.x, 24), ImGui::GetCursorPos(), COMPONENT_SELECTED_COLOR);
	ImGui::SetCursorPos(temp);
}

void s2d::UIAnimation::addAnimationsToAnimator()
{
	if (this->m_openInputWindow && ImGui::IsKeyReleased(ImGuiKey_Enter))
	{
		for (std::pair<std::string, s2d::Animation> anim : this->m_ptr_repo->sprite_in_inspector->animator.animations)
		{
			// Found a aniamtion with this name, which already exists
			if (anim.first == this->m_animationFile)
			{
				std::cout << "LOG [ERROR] Cant create anoter file with the same name!";
				return;
			}
		}
		if (this->m_animationFile[0] != '\0')
		{
			const std::string& path = 
				s2d::UI::getUserProjectPathSeperatetFromEnginePath(this->m_createAnimtionPathFileDialoge.pathClicked)
				+ this->m_animationFile
				+ EXTENSION_ANIMATION_FILE;
			this->m_ptr_repo->sprite_in_inspector->animator.createAnimation(this->m_animationFile, path, { });
		}
		s2d::flc::createAnimationSaveFile
			(this->m_ptr_repo->sprite_in_inspector, this->m_ptr_repo->sprite_in_inspector->animator.animations[this->m_animationFile]);

		this->m_createAnimtionPathFileDialoge.disableWindow();
		this->m_openFileDialog = false;
		this->m_animationFile[0] = '\0';
	}
}
