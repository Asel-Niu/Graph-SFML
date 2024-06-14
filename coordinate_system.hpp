#ifndef COORDINATE_SYSTEM_HPP_
#define COORDINATE_SYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace sf;
template <typename T>
class coordinate_system{
    public:
        coordinate_system(const Vector2<T>& position_, const Vector2<T>& size_, const Vector2<T>& zero_point_, const Vector2<T>& point_min_, const Vector2<T>& point_max_, bool flag_ = 1);
        //A variable of the bool type for determining the point of intersection of the axes: relative to the program window or relative to the coordinate plane and the graph.
        ~coordinate_system(){};
        Vector2<T> position;
        Vector2<T> size;
        Vector2<T> zero_point;
        Vector2<T> point_min, point_max;
        Color color;
        std::string axis_X, axis_Y;
    public:
        void draw_coordinate_axes(RenderWindow& window_) const;
        void draw_serifs(RenderWindow& window_, T scale_X_ = 1, T scale_Y_ = 1) const;
        void draw_function(RenderWindow& window_, Color color_, T (*fun)(T), unsigned number_point_) const;
        void draw_points(RenderWindow& window_, Color color_, Vector2<T> points_[], unsigned number_point_) const;
};

template <typename T>
std::string to_string(T number, unsigned n){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(n) << number;
    return stream.str();
}

template <typename T>
coordinate_system<T>::coordinate_system(const Vector2<T>& position_, const Vector2<T>& size_, const Vector2<T>& zero_point_, const Vector2<T>& point_min_, const Vector2<T>& point_max_, bool flag_){
    position = position_;
    size = size_;
    zero_point = zero_point_;
    point_min = point_min_;
    point_max = point_max_;
    if(flag_) zero_point = zero_point_;
    else{
        zero_point.x = size.x*(zero_point.x - point_min.x)/(point_max.x - point_min.x);
        zero_point.y = size.y*(- zero_point.y + point_max.y)/(point_max.y - point_min.y);
    }
    color = Color::Blue;
    axis_X = "x";
    axis_Y = "y";
}

template <typename T>
void coordinate_system<T>::draw_coordinate_axes(RenderWindow& window_) const{
    const T size_convex = 10;

    Vertex lineX[] = {
        Vertex(Vector2<T>(0, size.y - zero_point.y) + position, color),
        Vertex(Vector2<T>(size.x, size.y - zero_point.y) + position, color)
    };
    
    Vertex lineY[] = {
        Vertex(Vector2<T>(zero_point.x, 0) + position, color),
        Vertex(Vector2<T>(zero_point.x, size.y) + position, color)
    };
    
    ConvexShape convex_X;
    convex_X.setFillColor(color);
    convex_X.setPointCount(3);
    convex_X.setPoint(0, Vector2<T>(size.x - size_convex, size.y - zero_point.y - size_convex / 2) + position);
    convex_X.setPoint(1, Vector2<T>(size.x, size.y - zero_point.y) + position);
    convex_X.setPoint(2, Vector2<T>(size.x - size_convex, size.y - zero_point.y + size_convex / 2) + position);

    ConvexShape convex_Y;
    convex_Y.setFillColor(color);
    convex_Y.setPointCount(3);
    convex_Y.setPoint(0, Vector2<T>(zero_point.x - size_convex / 2, size_convex) + position);
    convex_Y.setPoint(1, Vector2<T>(zero_point.x, 0) + position);
    convex_Y.setPoint(2, Vector2<T>(zero_point.x + size_convex / 2, size_convex) + position);

    Font font;
    if (!font.loadFromFile("CaviarDreams.ttf"))
    {
           
    }
    Text text_X;
    text_X.setFont(font);
    text_X.setString(axis_X);
    text_X.setCharacterSize(18);
    text_X.setFillColor(color);

    T width_text = text_X.getLocalBounds().width;
    text_X.setPosition(Vector2<T>(size.x - width_text, size.y - zero_point.y + 4) + position);

    Text text_Y;
    text_Y.setFont(font);
    text_Y.setString(axis_Y);
    text_Y.setCharacterSize(18);
    text_Y.setFillColor(color);

    width_text = text_Y.getLocalBounds().width;
    text_Y.setPosition(Vector2<T>(zero_point.x - width_text - 8, 0) + position);

    window_.draw(text_X);
    window_.draw(text_Y);
    window_.draw(convex_X);
    window_.draw(convex_Y);
    window_.draw(lineX, 2, Lines);
    window_.draw(lineY, 2, Lines);
}

template <typename T>
void coordinate_system<T>::draw_serifs(RenderWindow& window_, T scale_X_, T scale_Y_) const{
    T delta;
    delta = size.x * scale_X_ / (point_max.x - point_min.x);

    Font font;
    if (!font.loadFromFile("CaviarDreams_Bold.ttf"))
    {
           
    }

    for(T i = zero_point.x; i < size.x - delta; i += delta){
        Vertex lineX[] = {
            Vertex(Vector2<T>(i, size.y - zero_point.y) + position, color),
            Vertex(Vector2<T>(i, size.y - zero_point.y + 5) + position, color)
        };
        
        Text text;
        text.setFont(font);
        text.setString(to_string((point_max.x - point_min.x)*i/size.x + point_min.x, 2));
        text.setCharacterSize(10);
        text.setFillColor(color);

        T width_text = text.getLocalBounds().width;
        text.setPosition(Vector2<T>(i + 1, size.y - zero_point.y + 6) + position);

        window_.draw(lineX, 2, Lines);
        window_.draw(text);
    }
    for(T i = zero_point.x - delta; i > delta; i -= delta){
        Vertex lineX[] = {
            Vertex(Vector2<T>(i, size.y- zero_point.y) + position, color),
            Vertex(Vector2<T>(i, size.y - zero_point.y + 5) + position, color)
        };
        
        Text text;
        text.setFont(font);
        text.setString(to_string((point_max.x - point_min.x)*i/size.x + point_min.x, 2));
        text.setCharacterSize(10);
        text.setFillColor(color);

        T width_text = text.getLocalBounds().width;
        text.setPosition(Vector2<T>(i + 1, size.y - zero_point.y + 6) + position);

        window_.draw(lineX, 2, Lines);
        window_.draw(text);
    }

    delta = size.y * scale_Y_ / (point_max.y - point_min.y);

    for(T i = size.y - zero_point.y + delta; i < size.y - delta; i += delta){
        Vertex lineY[] = {
            Vertex(Vector2<T>(zero_point.x, i) + position, color),
            Vertex(Vector2<T>(zero_point.x - 5, i) + position, color)
        };
        
        Text text;
        text.setFont(font);
        text.setString(to_string(-(point_max.y - point_min.y)*i/size.y + point_max.y, 2));
        text.setCharacterSize(10);
        text.setFillColor(color);

        T width_text = text.getLocalBounds().width;
        text.setPosition(Vector2<T>(zero_point.x - width_text - 7, i - 12) + position);
        
        window_.draw(lineY, 2, Lines);
        window_.draw(text);
    }
    for(T i = size.y - zero_point.y; i > delta; i -= delta){
        Vertex lineY[] = {
            Vertex(Vector2<T>(zero_point.x, i) + position, color),
            Vertex(Vector2<T>(zero_point.x - 5, i) + position, color)
        };
        
        Text text;
        text.setFont(font);
        text.setString(to_string(-(point_max.y - point_min.y)*i/size.y + point_max.y, 2));
        text.setCharacterSize(10);
        text.setFillColor(color);

        T width_text = text.getLocalBounds().width;
        text.setPosition(Vector2<T>(zero_point.x - width_text - 7, i - 12) + position);
        
        window_.draw(lineY, 2, Lines);
        window_.draw(text);
    }
}

template <typename T>
void coordinate_system<T>::draw_function(RenderWindow& window_, Color color_, T (*fun)(T), unsigned number_point_) const{
    T x = point_min.x;
    T y = fun(x);

    T delta_x = (point_max.x - point_min.x)/number_point_;

    for(unsigned i = 0; i < number_point_; i++){
        T x_ = x + delta_x;
        T y_ = fun(x_);

        if(!((y > point_max.y)||(y < point_min.y)||(y_ > point_max.y)||(y_ < point_min.y))){
            T k_x = size.x*(x - point_min.x)/(point_max.x - point_min.x);
            T k_y = size.y*(- y + point_max.y)/(point_max.y - point_min.y);
            T k_x_ = size.x*(x_ - point_min.x)/(point_max.x - point_min.x);
            T k_y_ = size.y*(- y_ + point_max.y)/(point_max.y - point_min.y);
            Vertex line[] = {
                Vertex(Vector2<T>(k_x, k_y) + position, color_),
                Vertex(Vector2<T>(k_x_, k_y_) + position, color_)
            };
            window_.draw(line, 2, Lines);
        }

        x = x_;
        y = y_;
    }
}

template <typename T>
void coordinate_system<T>::draw_points(RenderWindow& window_, Color color_, Vector2<T> points_[], unsigned number_point_) const{
    for(unsigned i = 0; i < number_point_; i++){
        if(!((points_[i].y > point_max.y)||(points_[i].y < point_min.y)||(points_[i].x > point_max.x)||(points_[i].x < point_min.x))){
            T k_x = size.x*(points_[i].x - point_min.x)/(point_max.x - point_min.x);
            T k_y = size.y*(- points_[i].y + point_max.y)/(point_max.y - point_min.y);
            CircleShape shape(3);
            shape.setFillColor(color_);
            shape.setPosition(Vector2<T>(k_x - 3, k_y - 3) + position);
            window_.draw(shape);
        }
    }
}

#endif 