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
#include "./infeccao.h"


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
	ALLEGRO_FONT* cure = al_load_font("BASKVILL.TTF", 25, 0);
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
	bool infect[26]{}, colorEvent[26]{}, limit[26]{}, hitbox[26]{}, clickCancel[26]{};

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
		clickCancel[i] = false;

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

		al_draw_text(cure, al_map_rgb(255, 255, 255), 1200, 810, 0, "Cura");
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

			if (seg++ && cura < 1500)
				cura += 1;
		}

		al_draw_bitmap(contorno, 0, 0, 0);

		// Mudar o cursor ao entrar na área do estado
		mouseSelect(event, display, infect);

		//---------------SELEÇÃO PARA INFECTAR-------------------\\

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			//RS
			if (event.mouse.x >= 750 && event.mouse.x <= 870 &&
				event.mouse.y >= 705 && event.mouse.y <= 780) {

				hitbox[0] = true;
			}

			//SC
			else if (event.mouse.x >= 840 && event.mouse.x <= 900 &&
				event.mouse.y >= 660 && event.mouse.y <= 700) {

				hitbox[1] = true;
			}

			//PR
			else if (event.mouse.x >= 810 && event.mouse.x <= 900 &&
				event.mouse.y >= 611 && event.mouse.y <= 660) {

				hitbox[2] = true;
			}

			//SP
			else if (event.mouse.x >= 845 && event.mouse.x <= 920 &&
				event.mouse.y >= 570 && event.mouse.y <= 610 ||
				event.mouse.x >= 880 && event.mouse.x <= 950 &&
				event.mouse.y >= 610 && event.mouse.y <= 635) {

				hitbox[3] = true;
			}

			//MG
			else if (event.mouse.x >= 920 && event.mouse.x <= 1000 &&
				event.mouse.y >= 500 && event.mouse.y <= 580) {

				hitbox[4] = true;
			}

			//RJ
			else if (event.mouse.x >= 1000 && event.mouse.x <= 1080 &&
				event.mouse.y >= 611 && event.mouse.y <= 710) {

				hitbox[5] = true;
			}

			//ES
			else if (event.mouse.x >= 1070 && event.mouse.x <= 1170 &&
				event.mouse.y >= 520 && event.mouse.y <= 600) {

				hitbox[6] = true;
			}

			//BA
			else if (event.mouse.x >= 940 && event.mouse.x <= 1040 &&
				event.mouse.y >= 415 && event.mouse.y <= 470) {

				hitbox[7] = true;
			}

			//PI
			else if (event.mouse.x >= 960 && event.mouse.x <= 1020 &&
				event.mouse.y >= 350 && event.mouse.y <= 385 ||
				event.mouse.x >= 980 && event.mouse.x <= 1005 &&
				event.mouse.y >= 300 && event.mouse.y <= 345) {

				hitbox[8] = true;
			}

			//MA
			else if (event.mouse.x >= 920 && event.mouse.x <= 965 &&
				event.mouse.y >= 300 && event.mouse.y <= 345) {

				hitbox[9] = true;
			}

			//CE
			else if (event.mouse.x >= 1015 && event.mouse.x <= 1055 &&
				event.mouse.y >= 300 && event.mouse.y <= 345) {

				hitbox[10] = true;
			}

			//RN
			else if (event.mouse.x >= 1130 && event.mouse.x <= 1200 &&
				event.mouse.y >= 250 && event.mouse.y <= 300) {

				hitbox[11] = true;
			}

			//PB
			else if (event.mouse.x >= 1160 && event.mouse.x <= 1215 &&
				event.mouse.y >= 310 && event.mouse.y <= 345) {

				hitbox[12] = true;
			}

			//PE
			else if (event.mouse.x >= 1200 && event.mouse.x <= 1260 &&
				event.mouse.y >= 350 && event.mouse.y <= 385) {

				hitbox[13] = true;
			}


			//AL
			else if (event.mouse.x >= 1130 && event.mouse.x <= 1180 &&
				event.mouse.y >= 380 && event.mouse.y <= 420) {

				hitbox[14] = true;
			}

			//SE
			else if (event.mouse.x >= 1100 && event.mouse.x <= 1165 &&
				event.mouse.y >= 425 && event.mouse.y <= 470) {

				hitbox[15] = true;
			}

			//AC
			else if (event.mouse.x >= 550 && event.mouse.x <= 610 &&
				event.mouse.y >= 380 && event.mouse.y <= 420 ||
				event.mouse.x >= 490 && event.mouse.x <= 550 &&
				event.mouse.y >= 360 && event.mouse.y <= 420) {

				hitbox[16] = true;
			}


			//RO
			else if (event.mouse.x >= 640 && event.mouse.x <= 710 &&
				event.mouse.y >= 380 && event.mouse.y <= 465) {

				hitbox[17] = true;
			}

			//AM
			else if (event.mouse.x >= 570 && event.mouse.x <= 730 &&
				event.mouse.y >= 260 && event.mouse.y <= 365.0) {

				hitbox[18] = true;
			}

			//RR
			else if (event.mouse.x >= 670 && event.mouse.x <= 730 &&
				event.mouse.y >= 150 && event.mouse.y <= 250) {

				hitbox[19] = true;
			}

			//PA
			else if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
				event.mouse.y >= 260 && event.mouse.y <= 370.0) {

				hitbox[20] = true;
			}


			//AP
			else if (event.mouse.x >= 810 && event.mouse.x <= 870 &&
				event.mouse.y >= 150 && event.mouse.y <= 250) {

				hitbox[21] = true;
			}

			//TO
			else if (event.mouse.x >= 870 && event.mouse.x <= 920 &&
				event.mouse.y >= 380 && event.mouse.y <= 450) {

				hitbox[22] = true;
			}

			//MT
			else if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
				event.mouse.y >= 400 && event.mouse.y <= 500) {

				hitbox[23] = true;
			}

			//GO
			else if (event.mouse.x >= 850 && event.mouse.x <= 910 &&
				event.mouse.y >= 460 && event.mouse.y <= 530) {

				hitbox[24] = true;
			}

			//MS
			else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
				event.mouse.y >= 520 && event.mouse.y <= 610) {

				hitbox[25] = true;
			}

			for (int i = 0; i < 26; i++) {

				if (hitbox[i] == true) {
					infect[i] = true;

					if (clickCancel[i] == false) {
						colorEvent[i] = true;
						clickCancel[i] = true;
					}
				}
				start = true;
			}
		


		for (int i = 0; i < 26; i++) {

			if (hitbox[i] == true) {
				infect[i] = true;

				if(clickCancel[i] == false) {
					colorEvent[i] = true;
					clickCancel[i] = true;
					}
			}
				start = true;
		}
	}

		//-----------Evento para abrir a loja-----------\\
	 
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (event.keyboard.keycode == ALLEGRO_KEY_B)
				openStore = true;

			else
				openStore = false;
		}

		if (openStore)
			atualizar_janela(openStore, queue, event, timeout, store, font, bioIcon, point, pointFont);

		// Desenhar o icone de pontuação
		al_draw_bitmap(bioIcon, 30, 795, 0);

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
	al_destroy_font(pointFont);

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