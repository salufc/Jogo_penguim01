#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

class Music
{
private:
	Mix_Music* music;

	int time;
	bool open;
public:
	Music();
	Music(std::string file);

	~Music();

	void Play(int i);

	void Stop();
	void Stop(int time);

	void Open(std::string file);

	inline bool is_open(){return open;}
};


class Game
{
public:
	static Game& getInstance()
	{
		static Game instance;
		return instance;	
	}

private:
	Game();

    int width, height;
    std::string name;
    bool window_is_open;
    SDL_Window *window;
    SDL_Renderer *renderer;
    FILE *fp;
    int opt;

    //audio
    Uint32 audio_length; // length of our sample
	Uint8 *audio_buffer; // buffer containing our audio file
	SDL_AudioSpec audio_spec; // the specs of our piece of music

public:
	class Sprite
	{
	private:
		int width, height, x, y;
		bool open;
		SDL_Surface surface;
		SDL_Texture *texture;
		SDL_Renderer *_renderer;
		SDL_Rect retangulo;

		

	public:
		Sprite();

		Sprite(std::string file);

		Sprite (const char* file);

		~Sprite();

		void Render();

		void Render(int x, int y);

		void Open(std::string file);
		void Open(const char* file);

		inline bool is_open(){return open;}
		inline int get_width(){return width;}
		inline int get_height(){return width;}

		void set_clip(int x, int y, int w, int h);


		
	};

public:
	Game(Game const&) = delete;
	void operator = (Game const&) = delete;

    ~Game();

    inline SDL_Renderer* get_renderer(){return renderer;}

    inline bool is_open(){return window_is_open;}

    //inicia o loop primario do jogo
    void Run();

    //Recebe o resolucao e o nome da janela a ser criada
    void set_game(int width, int height, std::string name);

    //inicia funcoes essenciais da biblioteca SDL2
    void init_game();
};

class State
{
private:
	enum event
	{
		QUIT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		LEFT_CLICK,
		RIGHT_CLICK,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
		NUM_0,
		PAUSA
	};
	bool quit_requested;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Surface *window_surface;
	std::vector<event> events_list;
	int width, height;
	int x, y, mouse_x, mouse_y;
	int game_speed;
	
	int temp_flag;
	bool PAUSED;

	Game::Sprite fundo;
	Music audio;
		
public:
	State(SDL_Window *window, SDL_Renderer *renderer, int width, int height);

	~State();

	inline bool QuitRequest(){return quit_requested;}

	inline void set_game_speed(int game_speed){this->game_speed=game_speed;}
	
	//Salva as entradas relevantes do mousse e teclado na events_list
	void Input();

	//Percorre events_list executando as acoes apropriadas para cada evento registrado
	void Update();

	//Funcao onde todas as renderizacoes sao feitas
	void Render();

};


