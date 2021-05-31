
// đây là file chuyên tạo các struct về player , ball , dùng để nhận vào tọa độ và in ra hình ảnh lên màn hình.

#pragma once // được dùng để chỉ dẫn trình biên dịch tránh include lại file nhiều lần
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_image.h>
#include "Process.h"
#include <SDL_ttf.h>

using namespace std;

#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

// obj về background
struct background {
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = 0;
        filled_rect.y = 0;
        filled_rect.w = 800;
        filled_rect.h = 600;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
};

// nhận vào tọa độ cây vợt.
struct racket {
    int x;
    int y;
    racket(int _x, int _y) {
        x = _x;
        y = _y;
    }
    // hàm vẽ , xuất ra cửa sổ.
    void render(SDL_Renderer* renderer, SDL_Texture* tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = 20;
        filled_rect.h = 80;

        SDL_RenderCopy(renderer, tex, NULL, &filled_rect);
    }
    // hai hàm up và down , dùng để điều khiển cây vợt.
    void up() {
        y -= 30;
        if (checkout(x, y) == false) // checkout trong common function dùng để kiểm tra xem cây vợt có đi quá màn hình hay chưa ,  nếu đi quá thì return false.
        y += 30;
    }
    void down() {
        y += 30;
            if (checkout(x, y) == false)
                y -= 30;
    }
};
struct ball {
    int x;
    int y;
    int size = 20;
    double step1;   // tốc độ theo chiều x.
    double step2;   // tốc độ theo chiều y.

    ball(int _x, int _y, double _step1, double _step2) {
        x = _x;
        y = _y;
        step1 = _step1;
        step2 = _step2;
    }
    void direction(double _x, double _y) {
        int xxx = crash(_x, _y, x, y); // hàm crash dùng để xác nhận loại va chạm khi bóng va vào vợt.
        double a, b;
        a = 3.15, b = 3.15;

        if (xxx == 1) {
            a = 3.4;
            b = 3.8;
            step(step1, step2, a, b, x, y);
            // hàm step dùng để chuyển hướng bóng sau khi va chạm .
            // hàm step sẽ nhận vào 2 tốc độ ban đầu , nhận vào 2 chỉ số tốc độ mới là a,b.
            // tức là a,b đóng vai trò như tốc độ ,  còn step dùng để xác định step1 , step2 mới bằng cách thêm dấu + - vào.
        }
        else if (xxx == 2) {
            a = 3.2;
            b = 3.5;
            step(step1, step2, a, b, x, y);

        }
        else if (xxx == 3) {
            a = 3.3;
            b = 3.3;
            step(step1, step2, a, b, x, y);

        }
        else if (xxx == 4) {
            a = 3.3;
            b = 3.6;
            step(step1, step2, a, b, x, y);

        }
        //xử lí bóng khi chạm tường.
        if (y + 20 >= 600 || y <= 0) {
            a = 3.15;
            b = 3.15;
            step(step1, step2, a, b, x, y);
        }
        // xử lí bóng khi nó đi ra ngoài màn hình .
        if (x <= 0 || x >= 800) {
            x = 200;
            y = 200;
            step1 = 3.15;
            step2 = 3.15;
        }
    }
    void render(SDL_Renderer* renderer , SDL_Texture * tex) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;

        SDL_RenderCopy(renderer,tex, NULL, &filled_rect);
    }
    // sau khi xác định step thì sẽ làm cho bóng chuyển động.
    void moves() {
        x += step1;
        y += step2;
    }

};

#endif // ACTION_H_INCLUDED
