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
#include "./teste.h"

void atualizar_janela(ALLEGRO_EVENT event, ALLEGRO_DISPLAY *display, ALLEGRO_FONT* font) {

	// ------------- Mostrar Transmissão ------------- \\

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		if (event.mouse.x >= 930 && event.mouse.x <= 975 &&
			event.mouse.y >= 250 && event.mouse.y <= 330) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Agua 2");

		}

		if (event.mouse.x >= 1000 && event.mouse.x <= 1050 &&
			event.mouse.y >= 210 && event.mouse.y <= 285) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Agua 1");


		}

		if (event.mouse.x >= 1090 && event.mouse.x <= 1150 &&
			event.mouse.y >= 210 && event.mouse.y <= 285) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Vento 1");

		}

		if (event.mouse.x >= 1090 && event.mouse.x <= 1150 &&
			event.mouse.y >= 285 && event.mouse.y <= 365) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Vento 2");

		}

		if (event.mouse.x >= 1190 && event.mouse.x <= 1245 &&
			event.mouse.y >= 210 && event.mouse.y <= 282) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Alimentos 1");

		}

		if (event.mouse.x >= 1260 && event.mouse.x <= 1315 &&
			event.mouse.y >= 250 && event.mouse.y <= 325) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Alimentos 2");

		}

		if (event.mouse.x >= 1355 && event.mouse.x <= 1410 &&
			event.mouse.y >= 250 && event.mouse.y <= 325) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Insetos 1");

		}

		if (event.mouse.x >= 1355 && event.mouse.x <= 1410 &&
			event.mouse.y >= 327 && event.mouse.y <= 405) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Insetos 2");

		}

		// ------------- Mostrar Citologia ------------- \\

		if (event.mouse.x >= 920 && event.mouse.x <= 975 &&
			event.mouse.y >= 590 && event.mouse.y <= 675) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Citoplasma");

		}

		if (event.mouse.x >= 1025 && event.mouse.x <= 1075 &&
			event.mouse.y >= 590 && event.mouse.y <= 675) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Ribossomo");

		}

		if (event.mouse.x >= 1130 && event.mouse.x <= 1185 &&
			event.mouse.y >= 590 && event.mouse.y <= 675) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Nucleolo");

		}

		if (event.mouse.x >= 1210 && event.mouse.x <= 1265 &&
			event.mouse.y >= 635 && event.mouse.y <= 720) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Mitocondria");

		}

		if (event.mouse.x >= 1315 && event.mouse.x <= 1370 &&
			event.mouse.y >= 635 && event.mouse.y <= 720) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Parede Celular");

		}

		if (event.mouse.x >= 1390 && event.mouse.x <= 1450 &&
			event.mouse.y >= 675 && event.mouse.y <= 765) {

			al_draw_text(font, al_map_rgb(255, 255, 255), 150, 550, 0, "Nucleo");

		}

	}
}