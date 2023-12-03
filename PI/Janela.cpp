#include <stdio.h>
#include "./Janela.h"
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "compraLoja.h"

void atualizar_janela(bool openStore, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_TIMEOUT timeout, ALLEGRO_BITMAP* store, ALLEGRO_FONT* font) {
	while (openStore) {
		int activeEvent = al_wait_for_event_until(queue, &event, &timeout);

		// Evento para fechar no botão
		if (activeEvent && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		// Apertar botão para voltar para o main
		if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			if (event.keyboard.keycode == ALLEGRO_KEY_B)
				openStore = false;

		// Deseja a loja
		al_draw_bitmap(store, 0, 0, 0);

		int teste = 20;
		char str[1000];
		sprintf(str, "%d", teste);
		
		// COMPRA
		buy();

		// Pontuação
		al_draw_text(font, al_map_rgb(77, 0, 110), 250, 840, ALLEGRO_ALIGN_LEFT, str);

		al_flip_display();
	}
}