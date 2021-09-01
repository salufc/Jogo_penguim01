#include "game.hpp"


State::State(SDL_Window *window, SDL_Renderer *renderer, int width, int height)
{
    this->width = width;
    this->height = height;
    this->window = window;
    quit_requested = false;
    this->renderer = renderer;
    window_surface = SDL_GetWindowSurface(window);
    game_speed = 1;
    quit_requested = false;
    x = 0;
    y = 0;
    mouse_x = 0;
    mouse_y = 0;
    temp_flag = 1;
    PAUSED = false;

    fundo.Open("assets/img/ocean.jpg");
    audio.Open("assets/audio/stageState.ogg");
    audio.Play(-1);
}

State::~State()
{
    audio.Stop();
}

void State::Input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {

        case SDL_QUIT:
            events_list.push_back(QUIT);
            break;

        case SDL_MOUSEMOTION:
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            events_list.push_back(LEFT_CLICK);
            break;

        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {

            case SDLK_ESCAPE:
                events_list.push_back(QUIT);
                break;

            case SDLK_UP:
                events_list.push_back(UP);
                break;

            case SDLK_DOWN:
                events_list.push_back(DOWN);
                break;

            case SDLK_LEFT:
                events_list.push_back(LEFT);
                break;

            case SDLK_RIGHT:
                events_list.push_back(RIGHT);
                break;

            case SDLK_1:
                events_list.push_back(NUM_1);
                break;

            case SDLK_2:
                events_list.push_back(NUM_2);
                break;

            case SDLK_3:
                events_list.push_back(NUM_3);
                break;

            case SDLK_4:
                events_list.push_back(NUM_4);
                break;

            case SDLK_5:
                events_list.push_back(NUM_5);
                break;

            case SDLK_6:
                events_list.push_back(NUM_6);
                break;

            case SDLK_7:
                events_list.push_back(NUM_7);
                break;

            case SDLK_8:
                events_list.push_back(NUM_8);
                break;

            case SDLK_9:
                events_list.push_back(NUM_9);
                break;

            case SDLK_p:
                events_list.push_back(PAUSA);
            }
            break;
        }
    }
}

void LoadAssets()
{
    Game::Sprite fundo("assets/img/ocean.jpg");
}

void State::Update()
{
    event last_event;

    if(false)//game over
    {
    	PAUSED = true;
    	if( true)
    	{
    		std::cout<<"Parabens voce venceu"<<std::endl;
    	}
    	else
    	{
    		std::cout<<"VOCE PERDEU"<<std::endl;
    	}
    }

    while(events_list.size() != 0)
    {
        last_event = events_list.back();
        events_list.pop_back();

        switch(last_event)
        {
        case QUIT:
            quit_requested = true;
            break;

        case UP:
            temp_flag = -1;
            break;

        case DOWN:
            temp_flag = 1;
            break;

        case LEFT:
        	if(game_speed>0)
        		{
        			game_speed--;        		
        		}

            break;

        case RIGHT:
        	if(game_speed<5)
        		{
        			game_speed++;        		
        		}

            break;

        case RIGHT_CLICK:

            break;

        case LEFT_CLICK:

            break;

        case NUM_1:
            
            break;

        case NUM_2:

            break;

        case NUM_3:

            break;

        case NUM_4:

            break;

        case NUM_5:

            break;

        case NUM_6:

            break;

        case NUM_7:

            break;

        case NUM_8:

            break;

        case NUM_9:

            break;
         case NUM_0:

        case PAUSA:
            PAUSED = !PAUSED;

        }
    }
}

void State::Render()
{
    //int temp_x, temp_y, temp_tipo;
    SDL_SetRenderDrawColor(renderer,255,0,100,255);
    SDL_RenderClear(renderer);

    //Game::Sprite fundo("assets/img/ocean.jpg");

    fundo.Render();

    if(PAUSED)
    {
        //menu da pausa vai aqui        
    }

    /*
    retangulo.x=0;
    retangulo.y=height-24;
    retangulo.h=12;
    retangulo.w=10;
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&retangulo);
    */


    SDL_RenderPresent(renderer);
}

Game::Game()
{
    name = "GAME";
    window_is_open = false;
    window = NULL;
    renderer = NULL;
    width = 0;
    height = 0;
    opt=-1;
    //std::cout<<"deseja comecar um novo jogo ou continuar o jogo salvo"<<std::endl;
 	//std::cout<<"digite 1 pra continuar e 2 para comecar um jogo novo"<<std::endl;
 	fp=NULL;
    opt =2;
 	while(opt!=1 && opt!=2)
 	{
 		std::cin>>opt;
 	}
       
}

Game::~Game()
{
   	window_is_open=false;
   	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::set_game(int width, int height, std::string name)
{

    this->width=width;
    this->height=height;
    this->name=name;
}

void Game::init_game()
{
    window_is_open=true;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout<<"SDL ERRO:"<<SDL_GetError() << std::endl;
    }
    else
    {
        SDL_Window *window = SDL_CreateWindow(name.c_str(),
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              width, height,
                                              SDL_WINDOW_OPENGL);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        SDL_RaiseWindow(window);
    }
    //SDL_ShowCursor(SDL_DISABLE);

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);

}

void Game::Run()
{
    State state(window,renderer, width, height);  

    //load
    int temp1, temp2, temp3;
    if(opt==1)
    {
    	fp=fopen("save.txt","r");
    	if(fp!=NULL)
    	{
    		fscanf(fp,"%d %d", &temp1, &temp2);

    		while(!feof(fp))
    		{
    			fscanf(fp,"%d %d %d\n",&temp1,&temp2,&temp3);

    		}	
    	}
    	fclose(fp);
    	fp=NULL;
    }
    else
    {
        //no save 
    }

    while(!(state.QuitRequest()))
    {
        state.Input();
        state.Update();
        state.Render();
    }

    //save
    /*
    fp=fopen("save.txt","w");

    fprintf(fp, "%d %d\n", temp1,temp2);
    while(false)
    {
    	fprintf(fp, "%d %d %d\n",temp1,temp2,temp3);
    }
    fclose(fp);
    */
    SDL_CloseAudio();

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game::Sprite::Sprite()
{
    texture = nullptr;
    open = false;
    _renderer = Game::getInstance().get_renderer();
}

Game::Sprite::Sprite(std::string file)
{
    texture = nullptr;
    open = false;
    _renderer = Game::getInstance().get_renderer();
    Open(file);
}

Game::Sprite::Sprite(const char* file)
{
    texture = nullptr;
    open = false;
    _renderer = Game::getInstance().get_renderer();
    Open(file);
}

Game::Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

void Game::Sprite::Open(std::string file)
{

    //const char *path = file.c_str();
    texture = IMG_LoadTexture(_renderer, file.c_str());

    if(texture == NULL)
    {
        std::cout<< "erro em carregar: " << file << std::endl;
        std::cout << IMG_GetError()<< std::endl;
        //getchar();
    }
    else
    {
        open = true;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
}

void Game::Sprite::Open(const char* file)
{

    //const char *path = file.c_str();
    texture = IMG_LoadTexture(_renderer, file);

    if(texture == NULL)
    {
        std::cout<< "erro em carregar: " << file << std::endl;
        std::cout << IMG_GetError()<< std::endl;
        //getchar();
    }
    else
    {
        open = true;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
}

void Game::Sprite::set_clip(int x, int y, int w, int h)
{
    this->x=x;
    this->y=y;
    retangulo.w=w;
    retangulo.h=h;
}

void Game::Sprite::Render()
{
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(_renderer,texture,NULL,NULL);
}

void Game::Sprite::Render(int x, int y)
{

}


Music::Music()
{

}

Music::Music(std::string file)
{
    open= true;
    Open(file);
}

Music::~Music()
{
    open=false;
    Mix_FreeMusic(music);
}

void Music::Play(int i)
{
    Mix_PlayMusic(music,i);
}

void Music::Stop()
{
    Mix_FadeOutMusic(0);
}

void Music::Stop(int time)
{
    Mix_FadeOutMusic(time);
}

void Music::Open(std::string file)
{
    //file= "stageState.ogg";
    music = Mix_LoadMUS(file.c_str());

    if(music == NULL)
    {
        std::cout<< "erro em carregar: " << file << std::endl;
        std::cout << Mix_GetError()<< std::endl;
        //getchar();
    }
    else
    {
        open = true;
    }

}