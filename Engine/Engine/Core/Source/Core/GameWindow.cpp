#include "GameWindow.h"

#include "Event.h"

// Ctor

spe::GameWindow::GameWindow()
{
	this->m_IsOpen = false;
	this->m_BackgroundColor = nullptr;
	this->m_Camera = nullptr;
	this->WindowEvent.type = sf::Event::GainedFocus;
	this->m_ptr_Window = nullptr;
}

spe::GameWindow::GameWindow(const spe::Vector2& size, const std::string& name)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::exception();
    }

	this->m_BackgroundColor = nullptr;
	this->m_Size = size;
	this->m_Camera = nullptr;
    this->WindowEvent.type = SDL_WINDOWEVENT_FOCUS_GAINED;//= sf::Event::GainedFocus;

	this->m_ptr_Window = SDL_CreateWindow(
            name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            (int)size.X,
            (int)size.Y,
            SDL_WINDOW_SHOWN
            );
    //= new sf::RenderWindow(sf::VideoMode((int)size.X, (int)size.Y), name, sf::Style::Default);
	if(!this->m_ptr_Window){
        SDL_Quit();
        this->m_IsOpen = false;
        return;
    }
    this->m_ptr_Renderer = SDL_CreateRenderer(this->m_ptr_Window,-1,0);
    if(!this->m_ptr_Renderer){
        SDL_DestroyWindow(this->m_ptr_Window);
        SDL_Quit();
        this->m_IsOpen = false;
        return;
    }
    this->m_IsOpen = true;
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(this->m_ptr_Window, &width, &height);
	this->m_WindowBounds = {0,0, width,height }; //= sf::IntRect(0, 0, this->m_ptr_Window->getSize().x, this->m_ptr_Window->getSize().y);

    SDL_SetHint(SDL_HINT_KEY_REPEAT_DELAY, "0"); //this->m_ptr_Window->setKeyRepeatEnabled(false);

    //ImGui::SFML::Init(*this->m_ptr_Window);//TODO -> SDL
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(
            this->m_ptr_Window,
            this->m_ptr_Renderer
            );
    ImGui_ImplSDLRenderer2_Init(this->m_ptr_Renderer);
}

// Private

void spe::GameWindow::UpdateCamera()
{
	if (this->m_Camera != nullptr)
	{
		this->m_Camera->Update();
}

// Public
void spe::GameWindow::PollEvents()
{
	bool EventChanged = false;
	Event.Type = spe::Event::None;
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT)
		{
			this->m_IsOpen = false;
			SDL_DestroyWindow(this->m_ptr_Window);
		}
		if (!EventChanged)
		{
			if (event.type == SDL_KEYUP)
			{
				Event.Type = spe::Event::KeyReleased;
				EventChanged = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				EventChanged = true;
				Event.Type = spe::Event::KeyPressed;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Event.Type = spe::Event::MousePressedLeft;
					EventChanged = true;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Event.Type = spe::Event::MouseReleasedLeft;
					EventChanged = true;
				}
			}
			else
			{
				EventChanged = true;
				Event.Type = spe::Event::None;
			}
			Event.Key = static_cast<spe::KeyBoardCode>(event.key.keysym.sym);
		}
	}
	ImGui_ImplSDL2_NewFrame(this->m_ptr_Window);
}

void spe::GameWindow::Draw(spe::Sprite* ptr, const S shader, bool ignoreLight)
{
	if (!ptr->SpriteRenderer.Render)
	{
		return;
	}
	if (shader != nullptr && ptr->SpriteRenderer.EffectedByLight && !ignoreLight)
	{
		this->m_ptr_Window->draw(ptr->GetSprite(), shader);
	}
	else 
	{

		this->m_ptr_Window->draw(ptr->GetSprite());
	}
}

void spe::GameWindow::Display()
{

	ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->m_ptr_Window);
    ImGui::NewFrame();
	this->UpdateCamera();

}

void spe::GameWindow::Clear()
{
	SDL_Color backgroundColor = SDL_Color(0, 0, 0);

	if (this->m_BackgroundColor != nullptr)
	{
		backgroundColor = SDL_Color(SDL_MAX_UINT8(this->m_BackgroundColor->X),
			SDL_MAX_UINT8(this->m_BackgroundColor->Y),
			SDL_MAX_UINT8(this->m_BackgroundColor->Z));
	}

	SDL_RenderClear(SDL_GetRenderer(this->m_ptr_Window));
}

void spe::GameWindow::Shutdown()
{
    SDL_DestroyRenderer(this->m_ptr_Renderer);
    SDL_DestroyWindow(this->m_ptr_Window);
    SDL_Quit();

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    delete this->m_ptr_Renderer;
	delete this->m_ptr_Window;
	this->m_IsOpen = false;
}

bool spe::GameWindow::ContainsCursor()
{
    return SDL_MouseInWindow(this->m_ptr_Window);//DONE
}
	

