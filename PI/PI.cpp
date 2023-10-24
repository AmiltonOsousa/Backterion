#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>


//variáveis globais
const int SCREEN_W = 1920;
const int SCREEN_H = 1080;


int main() {

	// Variável representando a janela principal
	ALLEGRO_DISPLAY* display = NULL;

	// Variável representando a imagem
	ALLEGRO_BITMAP* image = NULL;

	// Inicializamos a biblioteca e apresentar erro caso o al init não retorne 0
	if (!al_init()) {
		printf("Falha na inicialização");
		return -1;
	}

	// Inicializar add-on para usar imagem
	al_init_image_addon();

	//---------------------------TELA---------------------------\\

	// Configura a janela
	display = al_create_display(SCREEN_W, SCREEN_H);

	// Carrega a imagem e desenha
	image = al_load_bitmap("tela_principal.png");
	al_draw_bitmap(image, 0, 0, 0);


	// Atualiza a tela quando tiver algo para mostrar
	al_flip_display();

	// Segura a execução por 10 segundos
	al_rest(10.0);

	// Finaliza a janela
	al_destroy_display(display);

	return 0;
}