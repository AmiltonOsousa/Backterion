#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "./Janela.h"


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

	// Inicializar fonte
	if (!al_init_font_addon()) {
		printf("Falha na inicialização da fonte");
		return -1;
	}

	// Inicializar fontes ttf's
	if (!al_init_ttf_addon()) {
		printf("Falha na inicialização da fonte true type");
		return -1;
	}

	return 0;
}

int main() {

	// Função de inicialização
	init();

	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DO JOGO--------\\
 
	int min = 0, seg = 0, point = 0;

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
	ALLEGRO_TIMER* timer = NULL;


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DA LOJA--------\\

	ALLEGRO_BITMAP* store = al_load_bitmap("store.png");
	ALLEGRO_EVENT_QUEUE* storeQueue = al_create_event_queue();

	al_set_window_title(display, "Baktérion-23");


	//----------------------FILA DE EVENT----------------------\\

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout{};

	//----------------------TIMER---------------------\\

	timer = al_create_timer(0.1);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//---------------------------TELA---------------------------\\
	// Variáveis do jogo
	bool start = false;

	int arraym[1000]{};
	int indexLinha = 0;
	int lineY = 600;

	while (1) {

		bool openStore = false;
		bool select = false;

		//---------Evento para fechar a tela---------\\
		// Espera o evento para fechar tela

		al_wait_for_event(queue, &event);

		// Fecha tela ao acontecer o evento
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		// Desenha a imagem
		al_draw_tinted_bitmap(brasil, al_map_rgb(10, 0, 0), 0, 0, 0);

		for (int i = 0; i < indexLinha; i++) {
			al_draw_line(450, arraym[i], 1350, arraym[i], al_map_rgb(255, 0, 0), 1);
		}

		al_draw_bitmap(background, 0, 0, 0);
		al_draw_text(font, al_map_rgb(255, 0, 0), 1000, 600, ALLEGRO_ALIGN_LEFT, "Sigla do estadosss");


		//---------Evento para escolher estado---------\\

		if (event.type == ALLEGRO_EVENT_TIMER) {
		seg++;


		// Grafico com o tempo
		if (seg == 60) {

			min++;
			seg = 0;
		}

		if (start == true) {

			if (seg % 5 == 0) {

				arraym[indexLinha] = lineY;
				indexLinha++;

				lineY++;

				if (lineY == 1000)
					lineY = 600;
			}
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

		if (event.mouse.x >= 0 && event.mouse.x <= 800 &&
			event.mouse.y >= 0 && event.mouse.y <= 900) {

			al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Evento funcionou");
			select = true;

		}

		else
			select = false;
	}

	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

		if (select = true) {

			al_draw_text(font, al_map_rgb(255, 0, 0), 1500, 10, ALLEGRO_ALIGN_RIGHT, "Estado selecionado");
			start = true;
		}
	}


	//-----------Evento para abrir a loja-----------\\
 
	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

		if (event.keyboard.keycode == ALLEGRO_KEY_B) {
			openStore = true;

		}

		else
			openStore = false;
	}

	if (openStore) {
		atualizar_janela(openStore, queue, event, store, font);
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

// Finalizar bitmap
al_destroy_bitmap(brasil);
al_destroy_bitmap(store);

// Finalizar a fonte
al_destroy_font(font);

return 0;
}