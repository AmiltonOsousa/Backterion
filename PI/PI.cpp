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

	ALLEGRO_BITMAP* vitoria = al_load_bitmap("vitoria.png");
	ALLEGRO_BITMAP* derrota = al_load_bitmap("derrota.png");

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

	bool bought[21];
	int precoEstado = 5;
	int ordem = 0;
	int velocidade = 3;
	bool selectState = true;
	bool start = false;
	bool infect[26]{}, colorEvent[26]{}, limit[26]{}, hitbox[26]{}, clickCancel[26]{};

	int r[26]{}, g[26]{}, b[26]{};
	int min = 0, seg = 0, x = 0, y = 0, cura = 1200;
	
	int point = 0;

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

		if(i < 21)
			bought[i] = false;
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

			if (seg % 30 == 0)
				selectState = true;

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

				if (infect[i] == 3 && ordem == 1 || infect[i] == 3 && ordem == 2 || infect[i] == 3 && ordem == 3 || infect[i] == 3 && ordem == 4 ||
					infect[i] == 0 && ordem == 1 || infect[i] == 0 && ordem == 2 || infect[i] == 0 && ordem == 3 || infect[i] == 0 && ordem == 4 ||
					infect[i] == 1 && ordem == 1 || infect[i] == 1 && ordem == 2 || infect[i] == 1 && ordem == 3 || infect[i] == 1 && ordem == 4 ||
					infect[i] == 5 && ordem == 1 || infect[i] == 5 && ordem == 2 || infect[i] == 5 && ordem == 3 || infect[i] == 5 && ordem == 4)
						velocidade = 7;

				else velocidade = 7;

				if (seg % velocidade == 0 && limit[i] == false && infect[i] == true) {

					r[i]++;

					if (r[i] == 255)
						limit[i] = true;
				}
			}

			if (seg % 10 == 0 && cura < 1500)
				cura += 1;
		}

		al_draw_bitmap(contorno, 0, 0, 0);

		// Mudar o cursor ao entrar na área do estado
		mouseSelect(event, display, infect);

		//---------------SELEÇÃO PARA INFECTAR-------------------\\

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			//RS
			if (event.mouse.x >= 750 && event.mouse.x <= 870 &&
				event.mouse.y >= 705 && event.mouse.y <= 780 && selectState == true && point >= precoEstado) {

				hitbox[0] = true;
				ordem++;
				point -= precoEstado;
			}

			//SC
			else if (event.mouse.x >= 840 && event.mouse.x <= 900 &&
				event.mouse.y >= 660 && event.mouse.y <= 700 && selectState == true && point >= precoEstado) {

				hitbox[1] = true;
				ordem++;
				point -= precoEstado;
			}

			//PR
			else if (event.mouse.x >= 810 && event.mouse.x <= 900 &&
				event.mouse.y >= 611 && event.mouse.y <= 660 && selectState == true && point >= precoEstado) {

				hitbox[2] = true;
				ordem++;
				point -= precoEstado;
			}

			//SP
			else if (event.mouse.x >= 845 && event.mouse.x <= 920 &&
				event.mouse.y >= 570 && event.mouse.y <= 610 ||
				event.mouse.x >= 880 && event.mouse.x <= 950 &&
				event.mouse.y >= 610 && event.mouse.y <= 635 && selectState == true && point >= precoEstado) {

				hitbox[3] = true;
				ordem++;
				point -= precoEstado;
			}

			//MG
			else if (event.mouse.x >= 920 && event.mouse.x <= 1000 &&
				event.mouse.y >= 500 && event.mouse.y <= 580 && selectState == true && point >= precoEstado) {

				hitbox[4] = true;
				ordem++;
				point -= precoEstado;
			}

			//RJ
			else if (event.mouse.x >= 1000 && event.mouse.x <= 1080 &&
				event.mouse.y >= 611 && event.mouse.y <= 710 && selectState == true && point >= precoEstado) {

				hitbox[5] = true;
				ordem++;
				point -= precoEstado;
			}

			//ES
			else if (event.mouse.x >= 1070 && event.mouse.x <= 1170 &&
				event.mouse.y >= 520 && event.mouse.y <= 600 && selectState == true && point >= precoEstado) {

				hitbox[6] = true;
				ordem++;
				point -= precoEstado;
			}

			//BA
			else if (event.mouse.x >= 940 && event.mouse.x <= 1040 &&
				event.mouse.y >= 415 && event.mouse.y <= 470 && selectState == true && point >= precoEstado) {

				hitbox[7] = true;
				ordem++;
				point -= precoEstado;
			}

			//PI
			else if (event.mouse.x >= 960 && event.mouse.x <= 1020 &&
				event.mouse.y >= 350 && event.mouse.y <= 385 ||
				event.mouse.x >= 980 && event.mouse.x <= 1005 &&
				event.mouse.y >= 300 && event.mouse.y <= 345 && selectState == true && point >= precoEstado) {

				hitbox[8] = true;
				ordem++;
				point -= precoEstado;
			}

			//MA
			else if (event.mouse.x >= 920 && event.mouse.x <= 965 &&
				event.mouse.y >= 300 && event.mouse.y <= 345 && selectState == true && point >= precoEstado) {

				hitbox[9] = true;
				ordem++;
				point -= precoEstado;
			}

			//CE
			else if (event.mouse.x >= 1015 && event.mouse.x <= 1055 &&
				event.mouse.y >= 300 && event.mouse.y <= 345 && selectState == true && point >= precoEstado) {

				hitbox[10] = true;
				ordem++;
				point -= precoEstado;
			}

			//RN
			else if (event.mouse.x >= 1130 && event.mouse.x <= 1200 &&
				event.mouse.y >= 250 && event.mouse.y <= 300 && selectState == true && point >= precoEstado) {

				hitbox[11] = true;
				ordem++;
				point -= precoEstado;
			}

			//PB
			else if (event.mouse.x >= 1160 && event.mouse.x <= 1215 &&
				event.mouse.y >= 310 && event.mouse.y <= 345 && selectState == true && point >= precoEstado) {

				hitbox[12] = true;
				ordem++;
				point -= precoEstado;
			}

			//PE
			else if (event.mouse.x >= 1200 && event.mouse.x <= 1260 &&
				event.mouse.y >= 350 && event.mouse.y <= 385 && selectState == true && point >= precoEstado) {

				hitbox[13] = true;
				ordem++;
				point -= precoEstado;
			}


			//AL
			else if (event.mouse.x >= 1130 && event.mouse.x <= 1180 &&
				event.mouse.y >= 380 && event.mouse.y <= 420 && selectState == true && point >= precoEstado) {

				hitbox[14] = true;
				ordem++;
				point -= precoEstado;
			}

			//SE
			else if (event.mouse.x >= 1100 && event.mouse.x <= 1165 &&
				event.mouse.y >= 425 && event.mouse.y <= 470 && selectState == true && point >= precoEstado) {

				hitbox[15] = true;
				ordem++;
				point -= precoEstado;
			}

			//AC
			else if (event.mouse.x >= 550 && event.mouse.x <= 610 &&
				event.mouse.y >= 380 && event.mouse.y <= 420 ||
				event.mouse.x >= 490 && event.mouse.x <= 550 &&
				event.mouse.y >= 360 && event.mouse.y <= 420 && selectState == true && point >= precoEstado) {

				hitbox[16] = true;
				ordem++;
				point -= precoEstado;
			}


			//RO
			else if (event.mouse.x >= 640 && event.mouse.x <= 710 &&
				event.mouse.y >= 380 && event.mouse.y <= 465 && selectState == true && point >= precoEstado) {

				hitbox[17] = true;
				ordem++;
				point -= precoEstado;
			}

			//AM
			else if (event.mouse.x >= 570 && event.mouse.x <= 730 &&
				event.mouse.y >= 260 && event.mouse.y <= 365.0 && selectState == true && point >= precoEstado) {

				hitbox[18] = true;
				ordem++;
				point -= precoEstado;
			}

			//RR
			else if (event.mouse.x >= 670 && event.mouse.x <= 730 &&
				event.mouse.y >= 150 && event.mouse.y <= 250 && selectState == true && point >= precoEstado) {

				hitbox[19] = true;
				ordem++;
				point -= precoEstado;
			}

			//PA
			else if (event.mouse.x >= 770 && event.mouse.x <= 880.0 &&
				event.mouse.y >= 260 && event.mouse.y <= 370.0 && selectState == true && point >= precoEstado) {

				hitbox[20] = true;
				ordem++;
				point -= precoEstado;
			}


			//AP
			else if (event.mouse.x >= 810 && event.mouse.x <= 870 &&
				event.mouse.y >= 150 && event.mouse.y <= 250 && selectState == true && point >= precoEstado) {

				hitbox[21] = true;
				ordem++;
				point -= precoEstado;
			}

			//TO
			else if (event.mouse.x >= 870 && event.mouse.x <= 920 &&
				event.mouse.y >= 380 && event.mouse.y <= 450 && selectState == true && point >= precoEstado) {

				hitbox[22] = true;
				ordem++;
				point -= precoEstado;
			}

			//MT
			else if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
				event.mouse.y >= 400 && event.mouse.y <= 500 && selectState == true && point >= precoEstado) {

				hitbox[23] = true;
				ordem++;
				point -= precoEstado;
			}

			//GO
			else if (event.mouse.x >= 850 && event.mouse.x <= 910 &&
				event.mouse.y >= 460 && event.mouse.y <= 530 && selectState == true && point >= precoEstado) {

				hitbox[24] = true;
				ordem++;
				point -= precoEstado;
			}

			//MS
			else if (event.mouse.x >= 750 && event.mouse.x <= 830 &&
				event.mouse.y >= 520 && event.mouse.y <= 610 && selectState == true && point >= precoEstado) {

				hitbox[25] = true;
				ordem++;
				point -= precoEstado;
			}

			for (int i = 0; i < 26; i++) {

				if (hitbox[i] == true) {
					infect[i] = true;
					selectState = false;

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

		//--------------------------------------------------------------

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



			// ------------- Eventos de Sintomas ------------- \\

			al_draw_rectangle(130, 290, 185, 380, al_map_rgb(255, 255, 255), 2.0); // gripe

			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				if (event.mouse.x >= 130 && event.mouse.x <= 185 &&
					event.mouse.y >= 290 && event.mouse.y <= 380) {

					if (bought[0] == false && point >= 15) {
						point -= 20;
						velocidade--;
						bought[0] = true;
					}				

				}

				if (event.mouse.x >= 240 && event.mouse.x <= 294 &&
					event.mouse.y >= 371 && event.mouse.y <= 459) {


					if (bought[1] == false && point >= 15) {
						point -= 15;
						velocidade--;
						bought[0] = true;
					}

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






		//----------------------------------------------------------------

		// Desenhar o icone de pontuação
		al_draw_bitmap(bioIcon, 30, 795, 0);

		showPoints(point, pointFont);

		if (limit[0] == true &&
			limit[1] == true &&
			limit[2] == true &&
			limit[3] == true &&
			limit[4] == true &&
			limit[5] == true &&
			limit[6] == true &&
			limit[7] == true &&
			limit[8] == true &&
			limit[9] == true &&
			limit[10] == true &&
			limit[11] == true &&
			limit[12] == true &&
			limit[13] == true &&
			limit[14] == true &&
			limit[15] == true &&
			limit[16] == true &&
			limit[17] == true &&
			limit[18] == true &&
			limit[19] == true &&
			limit[20] == true &&
			limit[21] == true &&
			limit[22] == true &&
			limit[23] == true &&
			limit[24] == true &&
			limit[25] == true) {

			
			al_draw_bitmap(vitoria, 0, 0, 0);
			
		}

		if (cura >= 1499)
			while (1) {
				al_draw_bitmap(derrota, 0, 0, 0);

				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
					break;

				al_flip_display();
		}

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