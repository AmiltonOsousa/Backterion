#include <stdio.h>
#include "./Janela.h"
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "./Janela.h"
#include "./selecaoEstado.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "./pontuacao.h"
#include "./mouseSelect.h"

void mouseSelect(ALLEGRO_EVENT event, ALLEGRO_DISPLAY* display) {

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {


		//MT
		if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
			event.mouse.y >= 400 && event.mouse.y <= 500) {

			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//MS
		else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
			event.mouse.y >= 520 && event.mouse.y <= 610) {

			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PA

		else if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
			event.mouse.y >= 260 && event.mouse.y <= 370.0) {

			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		else {

			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
	}
}