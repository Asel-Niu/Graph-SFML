#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "coordinate_system.hpp"

using namespace sf;

float fun(float x);
float fun1(float x);
float t = 0.f;

int main()
{
    const unsigned SCREEN_WEIGHT = 540;
    const unsigned SCREEN_HIGHT = 340;
    const char *SCREEN_TITLE = "Graph";

    ContextSettings settings;
    settings.antialiasingLevel = 2;

    RenderWindow window(VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE, Style::Default, settings);

    Event event;

    coordinate_system<float> a(Vector2<float>(20.f, 20.f),
                               Vector2<float>(500.f, 300.f),
                               Vector2<float>(0.f, 0.f),
                               Vector2<float>(-4.2f, -1.5f),
                               Vector2<float>(4.2f, 1.5f),
                               false);

    Vector2<float> points[5] = {Vector2<float>(-5.f, -2.f),
                                Vector2<float>(-4.f, -1.f),
                                Vector2<float>(-0.5f, 1.5f),
                                Vector2<float>(0.f, 0.f),
                                Vector2<float>(1.f, 1.f)};

    while (window.isOpen()){

        while (window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
        }

        if(t <= 3.1415f) t += 0.0005f;
        else t = 0.f;

        window.clear();
        a.draw_coordinate_axes(window);
        a.draw_serifs(window, 1.f, 0.25f);
        a.draw_function(window, Color::Green, fun, 100);
        a.draw_function(window, Color::Green, fun1, 100);
        a.draw_points(window, Color::Red, points, 5);
        window.display();
    }

    return 0;
}

float fun(float x){
    return sin(x);
}
float fun1(float x){
    return sin(t)*sin(x + t);
}