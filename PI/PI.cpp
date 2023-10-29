#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>


//variáveis globais
const int SCREEN_W = 1600;
const int SCREEN_H = 900;


int init() {

	// Inicializamos a biblioteca e apresentar erro caso o al init não retorne 0
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

	return 0;
}

int main() {

	// Função de inicialização
	init();


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DO JOGO--------\\


	// Variável representando a janela principal
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);;

	// Variável representando a imagem
	ALLEGRO_BITMAP* image = al_load_bitmap("tela_principal.png");;

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();



	al_register_event_source(queue, al_get_display_event_source(display));

	//---------------------------TELA---------------------------\\

	bool playing = true;

	while (playing) {

		ALLEGRO_EVENT event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.05);

		int close = al_wait_for_event_until(queue, &event, &timeout);

		if (close && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;

		// Desenha a imagem
		al_draw_bitmap(image, 0, 0, 0);

		// Atualiza a tela quando tiver algo para mostrar
		al_flip_display();

	}


	//-----------------------DESTROYS------------------------\\


	// Finaliza a janela
	al_destroy_display(display);

	// Finaliza fila de eventos
	al_destroy_event_queue(queue);


	return 0;
}