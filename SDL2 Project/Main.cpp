#include <SDL.h>
//
//#define POINTS_COUNT 4
//
//static SDL_Point points[POINTS_COUNT] = {
//	{320, 200},
//	{300, 240},
//	{340, 240},
//	{320, 200}
//};
//#define SQUARE_POINTS_COUNT 5
//static SDL_Point square[SQUARE_POINTS_COUNT] = {
//	{100, 100},
//	{100, 200},
//	{200, 200},
//	{200, 100},
//	{100, 100}
//};
//void rect(int x,int y,int w,int h,SDL_Renderer* rend){
//	 SDL_Point rect_points[SQUARE_POINTS_COUNT] = {
//	{x, y},
//	{x, y+h},
//	{x+w, y+h},
//	{x+w, y},
//	{x, y}
//	};
//	SDL_RenderDrawLines(rend, rect_points, SQUARE_POINTS_COUNT);
//
//}

int main(int argc, char* argv[])
{
	SDL_Rect player = { 40, 100, 10, 100 };
	SDL_Rect enemy  = { 780, 100, 10, 100 };
	SDL_Rect Ball = { 100, 100, 10, 10 };
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		const Uint8* state;
		if (SDL_CreateWindowAndRenderer(840, 480, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;
			int Bd = 1;
			while (!done) {
				int BallSpeed=2;
				//VERY CLOSE TO TOP OF LOOP
				Uint32 currTime = SDL_GetTicks();

				SDL_Event event;

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
				state = SDL_GetKeyboardState(NULL);

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &player);
				SDL_RenderDrawRect(renderer, &enemy);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawRect(renderer, &Ball);

				
				if (Ball.y < 2) {
					if (Bd == 1) {
						Bd = 2;
					}
					if (Bd == 3) {
						Bd = 4;
					}
				}
				if (Ball.y > 468) {
					if (Bd == 2) {
						Bd = 1;
					}
					if (Bd == 4) {
						Bd = 3;
					}
				}

				if (Ball.x < 2) {
					if (Bd == 1) {
						Bd = 4;
					}
				}
				if (Bd == 1) {
					Ball.y -= BallSpeed;
					Ball.x += BallSpeed;
				}
				if (Bd == 2) {
					Ball.y += BallSpeed;
					Ball.x += BallSpeed;
				}
				if (Bd == 3) {
					Ball.y -= BallSpeed;
					Ball.x -= BallSpeed;
				}
				if (Bd == 4) {
					Ball.y += BallSpeed;
					Ball.x -= BallSpeed;
				}
				if(Ball.x<=50 && Ball.x>=40 &&  player.y +player.h >= Ball.y &&  player.y <= Ball.y+Ball.h){
					if (Bd == 3) {
						Bd = 1;
					}
					if (Bd == 4) {
						Bd = 2;
					}
				}
				if(
					Ball.x+Ball.w<=790 &&
					Ball.x+Ball.w>=780 &&
					enemy.y + enemy.h >= Ball.y &&
					enemy.y <= Ball.y+Ball.h
				){
					
						if (Bd == 1) {
							Bd = 3;
						}
						if (Bd == 2) {
							Bd = 4;
						}
					
				}
				if (state[SDL_SCANCODE_S]) {
					if (player.y < 380) {
						player.y += 2;
					}
				}
				
				if (state[SDL_SCANCODE_W]) {
					if (player.y > 00) {
						player.y -= 2;
					}
				}
				if(enemy.y + (enemy.h / 2) >Ball.y){
					enemy.y-=2;
				}
				if(enemy.y + (enemy.h / 2) <Ball.y){
					enemy.y+=2;
				}
				SDL_RenderPresent(renderer);

				//LAST THING IN LOOP
				Uint32 endTime = SDL_GetTicks();
				if (endTime - currTime < ((Uint32)((double)1000 / 60)))
					SDL_Delay(((double)1000 / 60) - (endTime - currTime));
					
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}