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


void showPoints(int point, ALLEGRO_FONT *pointFont) {
	char str[1000];
	sprintf(str, "DNA: %d", point);
	al_draw_text(pointFont, al_map_rgb(220, 0, 255), 160, 835, ALLEGRO_ALIGN_LEFT, str);
}