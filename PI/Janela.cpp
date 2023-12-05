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

		
		al_draw_rectangle(130, 290, 185, 380, al_map_rgb(255, 255, 255), 2.0); // gripe

		al_draw_rectangle(240, 290, 294, 380, al_map_rgb(255, 255, 255), 2.0); // febre

		al_draw_rectangle(320, 245, 373, 335, al_map_rgb(255, 255, 255), 2.0); // anemia

		al_draw_rectangle(400, 290, 455, 380, al_map_rgb(255, 255, 255), 2.0); // dor de cabeça

		al_draw_rectangle(475, 245, 533, 335, al_map_rgb(255, 255, 255), 2.0); // Encefalite

		al_draw_rectangle(555, 200, 613, 290, al_map_rgb(255, 255, 255), 2.0); // coma

		al_draw_rectangle(555, 290, 613, 380, al_map_rgb(255, 255, 255), 2.0); // ataque cardiaco

		// ------------- Transmissão ------------- \\

		al_draw_rectangle(930, 250, 975, 330, al_map_rgb(255, 255, 255), 2.0); // água 2
		al_draw_rectangle(1000, 210, 1050, 285, al_map_rgb(255, 255, 255), 2.0); // água 1

		al_draw_rectangle(1090, 210, 1150, 285, al_map_rgb(255, 255, 255), 2.0); // vento 1
		al_draw_rectangle(1090, 285, 1150, 365, al_map_rgb(255, 255, 255), 2.0); // vento 2


		al_draw_rectangle(1190, 210, 1245, 282, al_map_rgb(255, 255, 255), 2.0); // alimentos 1
		al_draw_rectangle(1260, 250, 1315, 325, al_map_rgb(255, 255, 255), 2.0); // alimentos 1

		al_draw_rectangle(1355, 250, 1410, 325, al_map_rgb(255, 255, 255), 2.0); // inseto 1 
		al_draw_rectangle(1355, 327, 1410, 405, al_map_rgb(255, 255, 255), 2.0); // inseto 2

		// ------------- Citologia ------------- \\

		al_draw_rectangle(920, 590, 975, 675, al_map_rgb(255, 255, 255), 2.0); // Citoplasma

		al_draw_rectangle(1025, 590, 1075, 675, al_map_rgb(255, 255, 255), 2.0); // Ribossomo

		al_draw_rectangle(1130, 590, 1185, 675, al_map_rgb(255, 255, 255), 2.0); // Nucléolo

		al_draw_rectangle(1210, 635, 1265, 720, al_map_rgb(255, 255, 255), 2.0); // Mitocondria

		al_draw_rectangle(1315, 635, 1370, 720, al_map_rgb(255, 255, 255), 2.0); // Parede Celular

		al_draw_rectangle(1390, 675, 1450, 765, al_map_rgb(255, 255, 255), 2.0); // Núcleo

		


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