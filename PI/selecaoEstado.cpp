#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

void selectState(ALLEGRO_FONT* font, bool infect, bool colorEvent, bool start, ALLEGRO_EVENT event, ALLEGRO_DISPLAY *display) {

	bool hitbox[26]{};

	for (int i = 0; i < 26; i++)
		hitbox[i] = false;

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

		//MT
		if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
			event.mouse.y >= 400 && event.mouse.y <= 500) {

			hitbox[23] = true;
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//MS
		if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
			event.mouse.y >= 520 && event.mouse.y <= 610) {

			hitbox[25] = true;
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PA

		if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
			event.mouse.y >= 260 && event.mouse.y <= 370.0) {

			hitbox[25] = true;
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		else {

			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Select False");
		}
	}

	for (int i = 0; i < 26; i++)
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && hitbox[i] == true) {

			al_draw_text(font, al_map_rgb(255, 0, 0), 1500, 10, ALLEGRO_ALIGN_RIGHT, "Estado selecionado");

			infect[i] = true;
			colorEvent[i] = true;
			start = true;

		}
}