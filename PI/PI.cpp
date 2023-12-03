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


// Variáveis globais
const int SCREEN_W = 1600;
const int SCREEN_H = 900;

// Função de inicialização
int init() {

	// Inicializar biblioteca
	if (!al_init()) {

		printf("Falha na inicialização");
		return -1;
	}

	// Inicializar add-on para usar imagem
	if (!al_init_image_addon()) {
		printf("Falha na inicialização da imagem");
		return -1;
	}

	// Inicializar o teclado
	if (!al_install_keyboard()) {
		printf("Falha na inicialização do teclado");
		return -1;
	}

	// Inicializar o mouse
	if (!al_install_mouse()) {
		printf("Falha na inicialização do mouse");
		return -1;
	}

	// Inicilizar primitiva gráfica
	if (!al_init_primitives_addon()) {
		printf("Falha na inicialização da biblioteca \"primitives\"");
		return -1;
	}

	// Inicializar fonte
	if (!al_init_font_addon()) {
		printf("Falha na inicialização da fonte");
		return -1;
	}

	// Inicializar fontes ttf's
	if (!al_init_ttf_addon()) {
		printf("Falha na inicialização da fonte true type");
		return -1;
	}

	al_install_audio();
	al_init_acodec_addon();

	return 0;
}

int main() {

	// Função de inicialização
	init();


	// Variável representando a janela principal
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);

	// Variável representando a fonte
	ALLEGRO_FONT* font = al_load_font("COOPBL.TTF", 20, 0);
	ALLEGRO_FONT* pointFont = al_load_font("BASKVILL.TTF", 40, 0);
	ALLEGRO_FONT* arial = al_load_font("arial.ttf", 20, 0);

	// Variável representando a fila
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	// Variável representando o fundo
	ALLEGRO_BITMAP* background = al_load_bitmap("background.png");

	// Variável representando a imagem do Brasil
	ALLEGRO_BITMAP* brasil = al_load_bitmap("brasil.png");

	// Variável representando o timer
	ALLEGRO_TIMER* timer = NULL;

	// Variável representando o contorno 
	ALLEGRO_BITMAP* contorno = al_load_bitmap("Contorno.png");

	// Variável representando o icone da pontuação
	ALLEGRO_BITMAP* bioIcon = al_load_bitmap("bioIcon.png");

	// Variável representando o sample
	ALLEGRO_SAMPLE* sample = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instance1 = NULL;

	//---------------Samples e instâncias--------------\\

	al_reserve_samples(1);

	sample = al_load_sample("background_music.wav");
	instance1 = al_create_sample_instance(sample);

	al_set_sample_instance_playmode(instance1, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instance1, al_get_default_mixer());

	// Estados

	ALLEGRO_BITMAP* rs = al_load_bitmap("estado/1_rs.png");
	ALLEGRO_BITMAP* sc = al_load_bitmap("estado/1_sc.png");
	ALLEGRO_BITMAP* pr = al_load_bitmap("estado/1_pr.png");
	ALLEGRO_BITMAP* sp = al_load_bitmap("estado/1_sp.png");
	ALLEGRO_BITMAP* mg = al_load_bitmap("estado/1_mg.png");
	ALLEGRO_BITMAP* rj = al_load_bitmap("estado/1_rj.png");
	ALLEGRO_BITMAP* es = al_load_bitmap("estado/1_es.png");
	ALLEGRO_BITMAP* ba = al_load_bitmap("estado/1_ba.png");
	ALLEGRO_BITMAP* pi = al_load_bitmap("estado/1_pi.png");
	ALLEGRO_BITMAP* ma = al_load_bitmap("estado/1_ma.png");
	ALLEGRO_BITMAP* ce = al_load_bitmap("estado/1_ce.png");
	ALLEGRO_BITMAP* rn = al_load_bitmap("estado/1_rn.png");
	ALLEGRO_BITMAP* pb = al_load_bitmap("estado/1_pb.png");
	ALLEGRO_BITMAP* pe = al_load_bitmap("estado/1_pe.png");
	ALLEGRO_BITMAP* al = al_load_bitmap("estado/1_al.png");
	ALLEGRO_BITMAP* se = al_load_bitmap("estado/1_se.png");
	ALLEGRO_BITMAP* ac = al_load_bitmap("estado/1_ac.png");
	ALLEGRO_BITMAP* ro = al_load_bitmap("estado/1_ro.png");
	ALLEGRO_BITMAP* am = al_load_bitmap("estado/1_am.png");
	ALLEGRO_BITMAP* rr = al_load_bitmap("estado/1_rr.png");
	ALLEGRO_BITMAP* pa = al_load_bitmap("estado/1_pa.png");
	ALLEGRO_BITMAP* ap = al_load_bitmap("estado/1_ap.png");
	ALLEGRO_BITMAP* to = al_load_bitmap("estado/1_to.png");
	ALLEGRO_BITMAP* mt = al_load_bitmap("estado/1_mt.png");
	ALLEGRO_BITMAP* go = al_load_bitmap("estado/1_go.png");
	ALLEGRO_BITMAP* ms = al_load_bitmap("estado/1_ms.png");


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DA LOJA--------\\

	ALLEGRO_BITMAP* store = al_load_bitmap("store.png");
	ALLEGRO_EVENT_QUEUE* storeQueue = al_create_event_queue();

	al_set_window_title(display, "Baktérion-23");

	//----------------------FILA DE EVENT----------------------\\

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout{};
	ALLEGRO_MOUSE_STATE state{};


	//----------------------TIMER---------------------\\

	timer = al_create_timer(0.1);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//---------------------------TELA---------------------------\\

	// Variáveis do jogo

	bool start = false;
	bool infect[26]{}, colorEvent[26]{}, limit[26]{}, hitbox[26]{};

	int r[26]{}, g[26]{}, b[26]{};
	int min = 0, seg = 0, point = 0, x = 0, y = 0, cura = 1200;

	// Inputar os valores nas variáveis que precisam
	for (int i = 0; i < 26; i++) {

		r[i] = 153;
		g[i] = 153;
		b[i] = 153;

		limit[i] = false;
		infect[i] = false;
		colorEvent[i] = false;
		hitbox[i] = false;

	}

	// Tocar a música
	al_play_sample_instance(instance1);

	while (1) {

		bool openStore = false;

		//---------Evento para fechar a tela---------\\
	
		// Espera o evento para fechar tela

		al_wait_for_event(queue, &event);

		// Fecha tela ao acontecer o evento
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		al_draw_bitmap(background, 0, 0, 0);

		al_draw_tinted_bitmap(rs, al_map_rgb(r[0], g[0], b[0]), 0, 0, 0);
		al_draw_tinted_bitmap(sc, al_map_rgb(r[1], g[1], b[1]), 0, 0, 0);
		al_draw_tinted_bitmap(pr, al_map_rgb(r[2], g[2], b[2]), 0, 0, 0);
		al_draw_tinted_bitmap(sp, al_map_rgb(r[3], g[3], b[3]), 0, 0, 0);
		al_draw_tinted_bitmap(mg, al_map_rgb(r[4], g[4], b[4]), 0, 0, 0);
		al_draw_tinted_bitmap(rj, al_map_rgb(r[5], g[5], b[5]), 0, 0, 0);
		al_draw_tinted_bitmap(es, al_map_rgb(r[6], g[6], b[6]), 0, 0, 0);
		al_draw_tinted_bitmap(ba, al_map_rgb(r[7], g[7], b[7]), 0, 0, 0);
		al_draw_tinted_bitmap(pi, al_map_rgb(r[8], g[8], b[8]), 0, 0, 0);
		al_draw_tinted_bitmap(ma, al_map_rgb(r[9], g[9], b[9]), 0, 0, 0);
		al_draw_tinted_bitmap(rn, al_map_rgb(r[11], g[11], b[10]), 0, 0, 0);
		al_draw_tinted_bitmap(pb, al_map_rgb(r[12], g[12], b[11]), 0, 0, 0);
		al_draw_tinted_bitmap(ce, al_map_rgb(r[10], g[10], b[12]), 0, 0, 0);
		al_draw_tinted_bitmap(pe, al_map_rgb(r[13], g[13], b[13]), 0, 0, 0);
		al_draw_tinted_bitmap(al, al_map_rgb(r[14], g[14], b[14]), 0, 0, 0);
		al_draw_tinted_bitmap(se, al_map_rgb(r[15], g[15], b[15]), 0, 0, 0);
		al_draw_tinted_bitmap(ac, al_map_rgb(r[16], g[16], b[16]), 0, 0, 0);
		al_draw_tinted_bitmap(ro, al_map_rgb(r[17], g[17], b[17]), 0, 0, 0);
		al_draw_tinted_bitmap(am, al_map_rgb(r[18], g[18], b[18]), 0, 0, 0);
		al_draw_tinted_bitmap(rr, al_map_rgb(r[19], g[19], b[19]), 0, 0, 0);
		al_draw_tinted_bitmap(pa, al_map_rgb(r[20], g[20], b[20]), 0, 0, 0);
		al_draw_tinted_bitmap(ap, al_map_rgb(r[21], g[21], b[21]), 0, 0, 0);
		al_draw_tinted_bitmap(to, al_map_rgb(r[22], g[22], b[22]), 0, 0, 0);
		al_draw_tinted_bitmap(mt, al_map_rgb(r[23], g[23], b[23]), 0, 0, 0);
		al_draw_tinted_bitmap(go, al_map_rgb(r[24], g[24], b[24]), 0, 0, 0);
		al_draw_tinted_bitmap(ms, al_map_rgb(r[25], g[25], b[25]), 0, 0, 0);

		al_draw_text(font, al_map_rgb(255, 255, 255), 1200, 810, 0, "Cura");
		al_draw_filled_rectangle(1200, 835, 1500, 855, al_map_rgb(52, 89, 139));
		al_draw_filled_rectangle(1200, 835, cura, 855, al_map_rgb(92, 225, 230));

		//---------Evento para escolher estado---------\\

		if (event.type == ALLEGRO_EVENT_TIMER) {

			seg++;

			if (seg == 60) {

				min++;
				seg = 0;
			}

			// Pontuação
			if(seg % 15 == 0)
				point++;

			if (seg % 1 == 0) {
				event.mouse.x = event.mouse.x;
				event.mouse.y = event.mouse.y;
			}


			if (start == true) {

				for (int i = 0; i < 26; i++) {
					if (colorEvent[i] == true && infect[i] == true) {
						r[i] = 0;
						g[i] = 0;
						b[i] = 0;
					}

					colorEvent[i] = false;
				}
			}

			for (int i = 0; i < 26; i++) {
				if (seg % 1 == 0 && limit[i] == false && infect[i] == true) {

					r[i]++;

					if (r[i] == 255)
						limit[i] = true;
				}
			}

			if (seg++ && cura < 1500) {

				cura += 1;

			}
		}

		al_draw_bitmap(contorno, 0, 0, 0);

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

			//MT
			if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
				event.mouse.y >= 400 && event.mouse.y <= 500) {

				hitbox[23] = true;
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

			}

			//MS
			else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
				event.mouse.y >= 520 && event.mouse.y <= 610) {

				hitbox[25] = true;
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);

			}

			//PA

			else if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
				event.mouse.y >= 260 && event.mouse.y <= 370.0) {

				hitbox[20] = true;
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

		//-----------Evento para abrir a loja-----------\\
	 
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (event.keyboard.keycode == ALLEGRO_KEY_B)
				openStore = true;

			else
				openStore = false;
		}

		if (openStore) {
			atualizar_janela(openStore, queue, event, timeout, store, font, bioIcon, point, pointFont);
		}

		/*
		al_draw_rectangle(720, 400, 830.0, 500.0, al_map_rgb(255, 0, 255), 2.0); //MT

		al_draw_rectangle(750, 520, 830.0, 610, al_map_rgb(255, 0, 255), 2.0); //MS

		al_draw_rectangle(770, 260, 880.0, 370.0, al_map_rgb(255, 0, 255), 2.0); //PA

		al_draw_rectangle(570, 260, 730.0, 365.0, al_map_rgb(255, 0, 255), 2.0); //AM

		al_draw_rectangle(640, 380, 710, 465, al_map_rgb(255, 0, 255), 2.0); //RO

		al_draw_rectangle(670, 150, 730.0, 250, al_map_rgb(255, 0, 255), 2.0); //RR

		al_draw_rectangle(810, 150, 870.0, 250, al_map_rgb(255, 0, 255), 2.0); //AP

		al_draw_rectangle(920, 500, 1000, 580, al_map_rgb(255, 0, 255), 2.0); //MG

		al_draw_rectangle(850, 460, 910, 530, al_map_rgb(255, 0, 255), 2.0); //GO

		al_draw_rectangle(870, 380, 920, 450, al_map_rgb(255, 0, 255), 2.0); //TO

		al_draw_rectangle(920, 300, 965, 345, al_map_rgb(255, 0, 255), 2.0); //MA

		al_draw_rectangle(1015, 300, 1055, 345, al_map_rgb(255, 0, 255), 2.0); //CE

		al_draw_rectangle(940, 415, 1040, 470, al_map_rgb(255, 0, 255), 2.0); //BA

		al_draw_rectangle(550, 380, 610, 420, al_map_rgb(255, 0, 255), 2.0); //AC
		al_draw_rectangle(490, 360, 550, 420, al_map_rgb(255, 0, 255), 2.0); //AC

		al_draw_rectangle(960, 350, 1020, 385, al_map_rgb(255, 0, 255), 2.0); //PI
		al_draw_rectangle(980, 300, 1005, 345, al_map_rgb(255, 0, 255), 2.0); //CE

		al_draw_rectangle(750, 705, 870.0, 780, al_map_rgb(255, 0, 255), 2.0); //RS

		al_draw_rectangle(840, 660, 900.0, 700, al_map_rgb(255, 0, 255), 2.0); //SC

		al_draw_rectangle(810, 611, 900.0, 660, al_map_rgb(255, 0, 255), 2.0); //PR

		al_draw_rectangle(1000, 611, 1080.0, 710, al_map_rgb(255, 0, 255), 2.0); //RJ

		al_draw_rectangle(1070, 520, 1170, 600, al_map_rgb(255, 0, 255), 2.0); //ES

		al_draw_rectangle(1100, 425, 1165, 470, al_map_rgb(255, 0, 255), 2.0); //SE

		al_draw_rectangle(1200, 350, 1260, 385, al_map_rgb(255, 0, 255), 2.0); //PE

		al_draw_rectangle(1160, 310, 1215, 345, al_map_rgb(255, 0, 255), 2.0); //PB

		al_draw_rectangle(1130, 250, 1200, 300, al_map_rgb(255, 0, 255), 2.0); //RN
		*/

		// Desenhar o icone de pontuação
		al_draw_bitmap(bioIcon, 30, 795, 0);

		// Desenhar a pontuação
		/*char str[1000];
		sprintf(str, "DNA: %d", point);
		al_draw_text(pointFont, al_map_rgb(255, 0, 110), 160, 835, ALLEGRO_ALIGN_LEFT, str);
		*/

		showPoints(point, pointFont);

		// Atualiza a tela quando tiver algo para mostrar
		al_flip_display();

	}

	//-----------------------DESTROYS------------------------\\

	// Finaliza a janela
	al_destroy_display(display);

	// Finaliza fila de eventos 
	al_destroy_event_queue(queue);

	// Finalizar fundo da tela
	al_destroy_bitmap(background);

	// Finalizar bitmap
	al_destroy_bitmap(brasil);
	al_destroy_bitmap(store);

	// Finalizar a fonte
	al_destroy_font(font);

	al_destroy_bitmap(rs);
	al_destroy_bitmap(sc);
	al_destroy_bitmap(pr);
	al_destroy_bitmap(sp);
	al_destroy_bitmap(mg);
	al_destroy_bitmap(rj);
	al_destroy_bitmap(es);
	al_destroy_bitmap(ba);
	al_destroy_bitmap(pi);
	al_destroy_bitmap(ma);
	al_destroy_bitmap(ce);
	al_destroy_bitmap(rn);
	al_destroy_bitmap(pb);
	al_destroy_bitmap(pe);
	al_destroy_bitmap(al);
	al_destroy_bitmap(se);
	al_destroy_bitmap(ac);
	al_destroy_bitmap(ro);
	al_destroy_bitmap(am);
	al_destroy_bitmap(rr);
	al_destroy_bitmap(pa);
	al_destroy_bitmap(ap);
	al_destroy_bitmap(to);
	al_destroy_bitmap(mt);
	al_destroy_bitmap(go);
	al_destroy_bitmap(ms);

	return 0;
}