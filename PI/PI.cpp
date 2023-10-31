#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>


ALLEGRO_MONITOR_INFO monitor_info;

//variáveis globais
const int SCREEN_W = 1600;
const int SCREEN_H = 900;


// Função de inicialização
int init() {

	// Inicializar biblioteca
	if (!al_init()) {
		printf("Falha na inicialização");
		return -1;
	}

	// Inicializar add-on para usar imagem
	if (!al_init_image_addon()) {
		printf("Falha na inicialização da imagem");
		return -1;
	}

	// Inicializar o teclado
	if (!al_install_keyboard()) {
		printf("Falha na inicialização do teclado");
		return -1;
	}

	// Inicializar o mouse
	if (!al_install_mouse()) {
		printf("Falha na inicialização do mouse");
		return -1;
	}

	// Inicilizar primitiva gráfica
	if (!al_init_primitives_addon()) {
		printf("Falha na inicialização da biblioteca \"primitives\"");
		return -1;
	}

	if (!al_init_font_addon()) {
		printf("Falha na inicialização da fonte");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		printf("Falha na inicialização da fonte true type");
		return -1;
	}

	return 0;
}


int main() {

	int action;

	// Função de inicialização
	init();


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DO JOGO--------\\


	// Variável representando a janela principal
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);

	// Variável representando a fonte
	ALLEGRO_FONT* font = al_load_font("COOPBL.TTF", 20, 0);
	
	// Variável representando a fila
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Variável representando o fundo
	ALLEGRO_BITMAP* background = al_load_bitmap("background.png");

	// Variável representando a imagem do Brasil
	ALLEGRO_BITMAP* brasil = al_load_bitmap("brasil.png");

	// Variável representando o timer
	ALLEGRO_TIMER* timer = NULL, *contador = 0;


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DA LOJA--------\\
	
	ALLEGRO_BITMAP* store = al_load_bitmap("store.png");



	al_set_window_title(display, "Baktérion-23");
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	// Iniciar o timer 
	al_start_timer(timer);
	al_start_timer(contador);

	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;

	//---------------------------TELA---------------------------\\

	while (1) {

		int x = 1;
		bool openStore = false;
		bool select = false;
		bool start = false;

		//---------Evento para fechar a tela---------\\

		al_init_timeout(&timeout, 0.05);

		// Espera o evento para fechar tela
		int close = al_wait_for_event_until(queue, &event, &timeout);
		
		// Fecha tela ao acontecer o evento
		if (close && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;		
	

		// Desenha a imagem
		al_draw_bitmap(brasil, 0, 0, 0);

		
		if (start == true) {

			//usar o timer para desenhar a cada ciclo de tempo
			al_draw_line(500, 600, 1350, 600, al_map_rgb(255, 0, 0), 1);
		}

		al_draw_bitmap(background, 0, 0, 0);
		al_draw_text(font, al_map_rgb(255, 0, 0), 1000, 600, ALLEGRO_ALIGN_LEFT, "Sigla do estado");


		//---------Evento para escolher estado---------\\

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES){

			if (event.mouse.x >= 0 && event.mouse.x <= 800 &&
				event.mouse.y >= 0 && event.mouse.y <= 900) {

				al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Evento funcionou");
				select = true;

			}

			else
				select = false;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			if(select = true){

				al_draw_text(font, al_map_rgb(255, 0, 0), 1500, 10, ALLEGRO_ALIGN_RIGHT, "Estado selecionado");
				start = true;
			}
			
		}
			


			//-------------Gráfico Brasil--------------
		


		//-----------Evento para abrir a loja-----------\\

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (event.keyboard.keycode == ALLEGRO_KEY_B) {
				openStore = true;
		
			}

			else
				openStore = false;
		}

		if (openStore) {

			while (x == 1) {

				al_draw_bitmap(store, 0, 0, 0);
				al_flip_display();
			}
		}
		

		// Atualiza a tela quando tiver algo para mostrar
		al_flip_display();

	}


	//-----------------------DESTROYS------------------------\\


	// Finaliza a janela
	al_destroy_display(display);

	// Finaliza fila de eventos
	al_destroy_event_queue(queue);

	// Finalizar fundo da tela
	al_destroy_bitmap(background);

	// Finalizar a fonte
	al_destroy_font(font);

	return 0;
}