#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#define DEFAULT_DISPLAY_WIDTH	640
#define DEFAULT_DISPLAY_HEIGHT	480

struct GameState {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_TIMER *sysTimer;
	ALLEGRO_FONT *builtinFont;
	int displayWidth;
	int displayHeight;
};

int main(void) {
	struct GameState gameState;
	memset(&gameState, 0, sizeof(struct GameState));

	al_init();
	al_install_keyboard();
	al_init_font_addon();

	gameState.sysTimer = al_create_timer(1.0 / 60.0);
	gameState.eventQueue = al_create_event_queue();
	gameState.builtinFont = al_create_builtin_font();
	gameState.displayWidth = DEFAULT_DISPLAY_WIDTH;
	gameState.displayHeight = DEFAULT_DISPLAY_HEIGHT;
	gameState.display = al_create_display(gameState.displayWidth, gameState.displayHeight);

	al_register_event_source(gameState.eventQueue, al_get_keyboard_event_source());
	al_register_event_source(gameState.eventQueue, al_get_timer_event_source(gameState.sysTimer));
	al_register_event_source(gameState.eventQueue, al_get_display_event_source(gameState.display));

	al_start_timer(gameState.sysTimer);

	bool loop = true;
	bool redraw = false;
	ALLEGRO_EVENT ev;

	while (loop) {
		al_wait_for_event(gameState.eventQueue, &ev);

		switch (ev.type) {
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			int keycode = ev.keyboard.keycode;
			if (keycode == ALLEGRO_KEY_ESCAPE)
				loop = false;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			loop = false;
			break;
		}

		if (redraw && al_is_event_queue_empty(gameState.eventQueue)) {
			al_clear_to_color(al_map_rgb(0, 0, 255));
			al_draw_text(gameState.builtinFont, al_map_rgb(255, 255, 0), 10, 10, 0, "Hello GOAT");
			al_flip_display();
			redraw = false;
		}
	}

	al_destroy_font(gameState.builtinFont);
	al_destroy_timer(gameState.sysTimer);
	al_destroy_display(gameState.display);
	al_destroy_event_queue(gameState.eventQueue);

	return 0;
}
