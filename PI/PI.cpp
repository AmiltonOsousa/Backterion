#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "./Janela.h"


ALLEGRO_MONITOR_INFO monitor_info;

//variáveis globais
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

	return 0;
}

int main() {

	// Função de inicialização
	init();


	// Variável representando a janela principal
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);

	// Variável representando a fonte
	ALLEGRO_FONT* font = al_load_font("COOPBL.TTF", 20, 0);
	ALLEGRO_FONT* pointFont = al_load_font("BASKVILL.TTF", 20, 0);
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


	//Estados

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

	//----------------------TIMER---------------------\\

	timer = al_create_timer(0.1);
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//---------------------------TELA---------------------------\\
	// Variáveis do jogo
	bool start = false, colorEvent = true, selectState = true;
	bool infect[26]{}; //colorEvent: transformar em array

	int r[26]{};
	int g = 153, b = 153;
	bool limit[26]{};


	//--------VARIÁVEIS PARA CRIAR OS ELEMENTOS DO JOGO--------\\

	int min = 0, seg = 0, intPoint = 0;
	const char point = intPoint + '0';

	//TESTE
	for (int i = 0; i < 26; i++) {
		r[i] = 153;
		limit[i] = false;
	}

	while (1) {

		bool openStore = false;
		bool select;

		//---------Evento para fechar a tela---------\\
		// Espera o evento para fechar tela

		al_wait_for_event(queue, &event);

		// Fecha tela ao acontecer o evento
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		al_draw_bitmap(background, 0, 0, 0);

		al_draw_tinted_bitmap(rs, al_map_rgb(r[0], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(sc, al_map_rgb(r[1], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(pr, al_map_rgb(r[2], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(sp, al_map_rgb(r[3], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(mg, al_map_rgb(r[4], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(rj, al_map_rgb(r[5], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(es, al_map_rgb(r[6], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ba, al_map_rgb(r[7], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(pi, al_map_rgb(r[8], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ma, al_map_rgb(r[9], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ce, al_map_rgb(r[10], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(rn, al_map_rgb(r[11], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(pb, al_map_rgb(r[12], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(pe, al_map_rgb(r[13], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(al, al_map_rgb(r[14], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(se, al_map_rgb(r[15], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ac, al_map_rgb(r[16], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ro, al_map_rgb(r[17], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(am, al_map_rgb(r[18], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(rr, al_map_rgb(r[19], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(pa, al_map_rgb(r[20], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ap, al_map_rgb(r[21], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(to, al_map_rgb(r[22], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(mt, al_map_rgb(r[23], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(go, al_map_rgb(r[24], g, b), 0, 0, 0);
		al_draw_tinted_bitmap(ms, al_map_rgb(r[25], g, b), 0, 0, 0);

		//---------Evento para escolher estado---------\\

		if (event.type == ALLEGRO_EVENT_TIMER) {
			seg++;

			// Pontuação
			if (seg == 15)
				intPoint++;

			if (seg == 60) {

				min++;
				seg = 0;
			}

			if (start == true) {

				if (colorEvent) {

					for (int i = 0; i < 26; i++)
						r[i] = 0;

					g = 0;
					b = 0;

					colorEvent = false;
				}

				if (seg % 1 == 0 && limit[1] == false) {

					r[1]++;

					if (r[1] == 255)
						limit[1] = true;
				}

			}
		}

		al_draw_bitmap(contorno, 0, 0, 0);

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) { //720, 400, 830.0, 500.0

			if (event.mouse.x >= 720 && event.mouse.x <= 830 &&
				event.mouse.y >= 400 && event.mouse.y <= 500) {

				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
				select = true;
				al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Evento funcionou");

			}

			else {

				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
				select = false;
				al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Select False");
			}
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			if (select == true) {

				al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Entrou");

				al_draw_text(font, al_map_rgb(255, 0, 0), 1500, 10, ALLEGRO_ALIGN_RIGHT, "Estado selecionado");
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

		if (openStore) {
			atualizar_janela(openStore, queue, event, timeout, store, font);
		}

		al_draw_rectangle(720, 400, 830.0, 500.0, al_map_rgb(255, 0, 255), 2.0); //MT
		al_draw_rectangle(920, 500, 1000, 580, al_map_rgb(255, 0, 255), 2.0); //MG

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