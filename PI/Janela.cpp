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
#include "pontuacao.h"

void atualizar_janela(bool openStore, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_TIMEOUT timeout, ALLEGRO_BITMAP* store, ALLEGRO_FONT* font, ALLEGRO_BITMAP *bioIcon, int point, ALLEGRO_FONT *pointFont) {
	
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
		
		// ------------- Sintomas ------------- \\

		/*
		al_draw_rectangle(158, 326, 216, 416, al_map_rgb(255, 255, 255), 2.0); // febre

		al_draw_rectangle(240, 371, 294, 459, al_map_rgb(255, 255, 255), 2.0); // gripe

		al_draw_rectangle(315, 415, 373, 500, al_map_rgb(255, 255, 255), 2.0); // anemia

		al_draw_rectangle(398, 460, 455, 548, al_map_rgb(255, 255, 255), 2.0); // dor de cabeça

		al_draw_rectangle(475, 505, 533, 590, al_map_rgb(255, 255, 255), 2.0); // Encefalite

		al_draw_rectangle(555, 550, 613, 635, al_map_rgb(255, 255, 255), 2.0); // coma

		// ------------- Transmissão ------------- \\

		al_draw_rectangle(1050, 268, 1101, 345, al_map_rgb(255, 255, 255), 2.0); // água

		al_draw_rectangle(1148, 268, 1198, 345, al_map_rgb(255, 255, 255), 2.0); // vento

		al_draw_rectangle(1245, 268, 1292, 345, al_map_rgb(255, 255, 255), 2.0); // alimentos

		// ------------- Citologia ------------- \\

		al_draw_rectangle(1003, 578, 1054, 663, al_map_rgb(255, 255, 255), 2.0);

		al_draw_rectangle(1084, 621, 1135, 706, al_map_rgb(255, 255, 255), 2.0);

		al_draw_rectangle(1185, 621, 1235, 706, al_map_rgb(255, 255, 255), 2.0);

		al_draw_rectangle(1265, 664, 1315, 749, al_map_rgb(255, 255, 255), 2.0);
		*/


		// ------------- Eventos de Sintomas ------------- \\

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			if (event.mouse.x >= 158 && event.mouse.x <= 216 &&
				event.mouse.y >= 326 && event.mouse.y <= 416) {

				openStore = false;

			}

			if (event.mouse.x >= 240 && event.mouse.x <= 294 &&
				event.mouse.y >= 371 && event.mouse.y <= 459) {

				openStore = false;

			}

			if (event.mouse.x >= 315 && event.mouse.x <= 373 &&
				event.mouse.y >= 415 && event.mouse.y <= 500) {

				openStore = false;

			}

			if (event.mouse.x >= 398 && event.mouse.x <= 455 &&
				event.mouse.y >= 460 && event.mouse.y <= 548) {

				openStore = false;

			}

			if (event.mouse.x >= 475 && event.mouse.x <= 533 &&
				event.mouse.y >= 505 && event.mouse.y <= 590) {

				openStore = false;

			}

			if (event.mouse.x >= 555 && event.mouse.x <= 613 &&
				event.mouse.y >= 550 && event.mouse.y <= 635) {

				openStore = false;

			}

			// ------------- Eventos de Transmissão ------------- \\

			if (event.mouse.x >= 1050 && event.mouse.x <= 1101 &&
				event.mouse.y >= 268 && event.mouse.y <= 345) {

				openStore = false;

			}

			if (event.mouse.x >= 1148 && event.mouse.x <= 1198 &&
				event.mouse.y >= 268 && event.mouse.y <= 345) {

				openStore = false;

			}

			if (event.mouse.x >= 1245 && event.mouse.x <= 1292 &&
				event.mouse.y >= 268 && event.mouse.y <= 345) {

				openStore = false;

			}

			// ------------- Eventos de Citologia ------------- \\

			if (event.mouse.x >= 1003 && event.mouse.x <= 1054 &&
				event.mouse.y >= 578 && event.mouse.y <= 663) {

				openStore = false;

			}

			if (event.mouse.x >= 1084 && event.mouse.x <= 1135 &&
				event.mouse.y >= 621 && event.mouse.y <= 706) {

				openStore = false;

			}

			if (event.mouse.x >= 1185 && event.mouse.x <= 1235 &&
				event.mouse.y >= 621 && event.mouse.y <= 706) {

				openStore = false;

			}

			if (event.mouse.x >= 1265 && event.mouse.x <= 1315 &&
				event.mouse.y >= 664 && event.mouse.y <= 749) {

				openStore = false;

			}
		}

		// Desenhar icone 
		al_draw_bitmap(bioIcon, 30, 795, 0);
	
		showPoints(point, pointFont);

		al_flip_display();
	}
}