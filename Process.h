// file để xử lí và kiểm tra các trường hợp,

#pragma once // được dùng để chỉ dẫn trình biên dịch tránh include lại file nhiều lần
#include <iostream>
#include <SDL.h>
#include <string>
#include <map>
#include <SDL_image.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

// để kiểm tra xem cây vợt có ra ngoài màn hình hay không.
bool checkout(int x, int y) {
	if ( y >=520  || y<=0 ) {
		return false;
	}
	return true;
}

// hàm crash dựa vào mối liên hệ giữa tọa độ bóng và tọa độ cây gậy để xác định 4 loại va chạm , với mỗi loại va chạm thì hướng nảy sẽ khác.
int crash(double x1, double y1 , double x2 , double y2) {
	if ((x2 < x1 + 20 &&  x2 >= x1 )|| (x2 + 20  > x1 && x1 > 200) ){
		if (y2 > y1 && y2 <= y1 + 20) {
			return 1;
		}
		else if (y2 > y1 + 20 && y2 <= y1 + 40) {
			return 2;
		}
		else if (y2 > y1 + 40 && y2 <= y1 + 60) {
			return 3;
		}
		else if (y2 > y1 + 60 && y2 < y1 + 80) {
			return 4;
		}
		else return 5;
	}
	return 6;
}

// hàm step có mục đích dùng để thêm dấu vào tốc độ nhận vào a,b , để tạo ra hướng chuyển động mới của bóng.
bool step(double &step1, double &step2 , double a , double b , double x , double y) {
	if (step1 < 0 && step2 < 0 &&  y <=0 ) {
		step1 = -a;
		step2 = b;
		return true;
	}
	else if (step1 < 0 && step2 < 0) {
		step1 = a;
		step2 = -b;
		return true;
	}
    if (step1 > 0 && step2 < 0 && y<=0 ) {
		step1 = a;
		step2 = b;
		return true;
	}
	else if (step1 > 0 && step2 < 0) {
		step1 = -a;
		step2 = -b;
		return true;
	}
	if (step1 < 0 && step2 > 0 && y+20 >=600) {
		step1 = -a;
		step2 = -b;
		return true;
	}
	else if (step1 < 0 && step2 > 0) {
		step1 = a;
		step2 = b;
		return true;
	}
	if (step1 > 0 && step2 > 0 && y+20>=600) {
		step1 = a;
		step2 = -b;
		return true;
	}
	else if (step1 > 0 && step2 > 0) {
		step1 = -a;
		step2 = b;
		return true;
	}
}

// hàm rendertext
void rendertext(SDL_Renderer* renderer , string text , int _x , int _y) {
    TTF_Font * font = TTF_OpenFont("font.ttf", 24);
	SDL_Color White = { 255, 255, 255 , 255};
    SDL_Surface * surfaceMessage = TTF_RenderText_Solid(font, text.c_str() , White);
    SDL_Texture * Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = _x ;
	Message_rect.y = _y ;
	Message_rect.w = 20;
	Message_rect.h = 50;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

#endif
