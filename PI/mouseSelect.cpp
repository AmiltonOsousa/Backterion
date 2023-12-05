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

void mouseSelect(ALLEGRO_EVENT event, ALLEGRO_DISPLAY* display, bool infect[]) {

	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {


		//MT
		if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
			event.mouse.y >= 400 && event.mouse.y <= 500) {

			if (infect[23] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//MS
		else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
			event.mouse.y >= 520 && event.mouse.y <= 610) {

			if (infect[25] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PA

		else if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
			event.mouse.y >= 260 && event.mouse.y <= 370.0) {

			if (infect[20] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//AM

		else if (event.mouse.x >= 570 && event.mouse.x <= 730 &&
			event.mouse.y >= 260 && event.mouse.y <= 365.0) {

			if (infect[18] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//RO

		else if (event.mouse.x >= 640 && event.mouse.x <= 710 &&
			event.mouse.y >= 380 && event.mouse.y <= 465) {

			if (infect[17] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//RR

		else if (event.mouse.x >= 670 && event.mouse.x <= 730 &&
			event.mouse.y >= 150 && event.mouse.y <= 250) {

			if (infect[19] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//AP

		else if (event.mouse.x >= 550 && event.mouse.x <= 870 &&
			event.mouse.y >= 150 && event.mouse.y <= 250) {

			if (infect[21] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//MG

		else if (event.mouse.x >= 920 && event.mouse.x <= 1000 &&
			event.mouse.y >= 500 && event.mouse.y <= 580) {

			if (infect[4] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//GO

		else if (event.mouse.x >= 850 && event.mouse.x <= 910 &&
			event.mouse.y >= 460 && event.mouse.y <= 530) {

			if (infect[24] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//TO

		else if (event.mouse.x >= 870 && event.mouse.x <= 920 &&
			event.mouse.y >= 380 && event.mouse.y <= 450) {

			if (infect[22] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//MA

		else if (event.mouse.x >= 920 && event.mouse.x <= 965 &&
			event.mouse.y >= 300 && event.mouse.y <= 345) {

			if (infect[9] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//CE

		else if (event.mouse.x >= 980 && event.mouse.x <= 1055 &&
			event.mouse.y >= 300 && event.mouse.y <= 345) {

			if (infect[10] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//BA

		else if (event.mouse.x >= 940 && event.mouse.x <= 1040 &&
			event.mouse.y >= 415 && event.mouse.y <= 470) {

			if (infect[7] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//AC

		else if (event.mouse.x >= 550 && event.mouse.x <= 610 &&
			event.mouse.y >= 380 && event.mouse.y <= 420 ||
			event.mouse.x >= 490 && event.mouse.x <= 550 &&
			event.mouse.y >= 360 && event.mouse.y <= 420) {

			if (infect[16] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PI

		else if (event.mouse.x >= 960 && event.mouse.x <= 1020 &&
			event.mouse.y >= 350 && event.mouse.y <= 385 ||
			event.mouse.x >= 980 && event.mouse.x <= 1005 &&
			event.mouse.y >= 300 && event.mouse.y <= 345) {

			if (infect[16] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}


		//RS

		else if (event.mouse.x >= 750 && event.mouse.x <= 870 &&
			event.mouse.y >= 705 && event.mouse.y <= 780) {

			if (infect[0] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//SC

		else if (event.mouse.x >= 840 && event.mouse.x <= 900 &&
			event.mouse.y >= 660 && event.mouse.y <= 700) {

			if (infect[1] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PR

		else if (event.mouse.x >= 550 && event.mouse.x <= 900 &&
			event.mouse.y >= 611 && event.mouse.y <= 660) {

			if (infect[2] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//RJ

		else if (event.mouse.x >= 1000 && event.mouse.x <= 1080 &&
			event.mouse.y >= 611 && event.mouse.y <= 710) {

			if (infect[5] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//ES

		else if (event.mouse.x >= 1070 && event.mouse.x <= 1170 &&
			event.mouse.y >= 520 && event.mouse.y <= 600) {

			if (infect[6] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//SE

		else if (event.mouse.x >= 1100 && event.mouse.x <= 1165 &&
			event.mouse.y >= 425 && event.mouse.y <= 470) {

			if (infect[15] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PE

		else if (event.mouse.x >= 150 && event.mouse.x <= 1260 &&
			event.mouse.y >= 350 && event.mouse.y <= 385) {

			if (infect[13] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//PB

		else if (event.mouse.x >= 1160 && event.mouse.x <= 1215 &&
			event.mouse.y >= 310 && event.mouse.y <= 345) {

			if (infect[12] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//RN

		else if (event.mouse.x >= 1130 && event.mouse.x <= 150 &&
			event.mouse.y >= 250 && event.mouse.y <= 300) {

			if (infect[11] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//AL

		else if (event.mouse.x >= 1130 && event.mouse.x <= 1180 &&
			event.mouse.y >= 380 && event.mouse.y <= 420) {

			if (infect[14] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		//SP

		else if (event.mouse.x >= 845 && event.mouse.x <= 920 &&
			event.mouse.y >= 570 && event.mouse.y <= 610 ||
			event.mouse.x >= 880 && event.mouse.x <= 950 &&
			event.mouse.y >= 610 && event.mouse.y <= 635) {

			if (infect[3] == false)
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

		}

		else
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);

	}
}