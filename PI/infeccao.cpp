#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

void infectState(ALLEGRO_EVENT event, bool* pHitBox, ALLEGRO_DISPLAY* display, bool *pColorEvent, bool start, bool* pInfect) {

	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

		if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
			event.mouse.y >= 400 && event.mouse.y <= 500) {

			pHitBox[23] = true;
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
		}

		else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
			event.mouse.y >= 520 && event.mouse.y <= 610) {

			pHitBox[25] = true;
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		for (int i = 0; i < 26; i++) {

			if (pHitBox[i] == true) {

				pInfect[i] = true;
				pColorEvent[i] == true;
				start = true;
			}
		}
	}
}