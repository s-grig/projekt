#include <SFML/Graphics.hpp>
#include <algorithm>
#ifndef INCLUDE_DRAWER_HPP_

#define INCLUDE_DRAWER_HPP_

class function_plot_drawer {
	unsigned int x_size = 1000;
	unsigned int y_size = 800;
    unsigned int marker_size = 3;

    unsigned int new_center_x = x_size / 2;
    unsigned int new_center_y = y_size / 2;
    int border = 0;

    double limit_x0;
    double limit_x1;
    double limit_y0;
    double limit_y1;

	double step_x = 1;
	double step_y = 1;

public:

	void main_cicle(std::string& x, std::string& y) {
        std::vector<std::pair<double, double>> coordinates;
        std::string tmp;
        std::vector<int> x_vec, y_vec;
        //Извлечь x
        for (int i = 0; i < x.size(); i++) {
            if (std::isdigit(x[i]) || x[i] == '-') {
                tmp.push_back(x[i]);
                if (x[i + 1] == ' ' || i + 1 >= x.size()) {
                    x_vec.push_back(std::stod(tmp));
                    tmp = "";
                }
            }
        }
        for (auto el : x_vec) {
            std::cout << el << std::endl;
        }
        //Извлечь y
        for (int i = 0; i < y.size(); i++) {
            if (std::isdigit(y[i]) || y[i] == '-') {
                tmp.push_back(y[i]);
                if (y[i + 1] == ' ' || i + 1 >= y.size() || y[i + 1] == '\n') {
                    y_vec.push_back(std::stod(tmp));
                    tmp = "";
                }
            }
        }
        for (int i = 0; i < x_vec.size(); i++) {
            coordinates.push_back(std::make_pair(x_vec[i], y_vec[i]));
        }

        auto temp = std::max_element(coordinates.begin(), coordinates.end(),
            [](const auto& a, const auto& b) {
                return abs(a.first) < (b.first);
            });
        int mod_x = (*temp).first;

        temp = std::max_element(coordinates.begin(), coordinates.end(),
            [](const auto& a, const auto& b) {
                return abs(a.second) < (b.second);
            });
        int mod_y = (*temp).second;

        if (mod_y > mod_x) {
            while (mod_y % 10 != 0)
            {
                mod_y++;
            }
            if (mod_y == 0) {
                limit_x1 = limit_y1 = 5;
            }
            limit_x1 = limit_y1 = mod_y;
            limit_x0 = limit_y0 = -mod_y;
        }
        else {
            while (mod_x % 10 != 0)
            {
                mod_x++;
            }
            if (mod_x == 0) {
                limit_x1 = limit_y1 = 5;
            }
            limit_x1 = limit_y1 = mod_x;
            limit_x0 = limit_y0 = -mod_x;
        }

        double step_x = 1;
        double step_y = 1;

        sf::RenderWindow window(sf::VideoMode(x_size, y_size), "Function plot");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color(255, 255, 255, 0));
            //axis
            sf::RectangleShape line;
            line.setFillColor(sf::Color(0, 0, 0));
            int new_center_x = x_size / 2;
            int new_center_y = y_size / 2;
            //Вертикаль Y
            line.setPosition(border, new_center_y);
            line.setSize(sf::Vector2f(x_size - 2 * border, 4));
            window.draw(line);

            //Горизонталь X
            line.setPosition(new_center_x, border);
            line.setSize(sf::Vector2f(4, y_size - 2 * border));
            window.draw(line);

            sf::Font font;
            if (!font.loadFromFile("..\\..\\..\\file\\font\\arial.ttf")) {
                std::cout << "Ошибка чтения шрифта" << std::endl;
            }
        
            sf::Text text;
            text.setCharacterSize(10);
            text.setFillColor(sf::Color(0, 0, 0));
            text.setFont(font);

            unsigned int count_marker_y = limit_y1 - limit_y0 / step_y;
            unsigned int len_axis_y = y_size - 2 * border;
            for (unsigned u = 0; u <= count_marker_y; u++) {
                //Текст
                int var = limit_y0 + (count_marker_y - u) * step_y;
                std::string s = std::to_string(var);
                text.setString(s);
                text.setPosition(new_center_x + 15, len_axis_y / count_marker_y * u + border - 10);
                window.draw(text);

                line.setFillColor(sf::Color(0, 0, 0));
                //Горизонтальные
                line.setPosition(border, len_axis_y / count_marker_y * u + border);
                line.setSize(sf::Vector2f(x_size - 2 * border, 1));
                window.draw(line);
            }

            //Разметка горизонатльной оси
            unsigned count_marker_x = limit_x1 - limit_x0 / step_x;
            unsigned len_axis_x = x_size - 2 * border;
            for (unsigned u = 0; u <= count_marker_x; ++u) {
                //Текст
                int var = limit_x0 + u * step_x;
                std::string s = std::to_string(var);
                text.setString(s);
                text.setPosition(len_axis_x / count_marker_x * u + border, new_center_y + 15);
                window.draw(text);
                //Вспомогательные линии сетки
                //вертикальные
                line.setPosition(len_axis_x / count_marker_x * u + border, border);
                line.setSize(sf::Vector2f(1, y_size - 2 * border));
                window.draw(line);
            }

            //X
            text.setCharacterSize(20);
            text.setString("X");
            text.setPosition(x_size - border - 15, new_center_y - 25);
            window.draw(text);

            //Y
            text.setString("Y");
            text.setPosition(new_center_x - 15, border);
            window.draw(text);

            double scaling_factor_x = (x_size - 2 * border) / (limit_x1 - limit_x0);
            double scaling_factor_y = (y_size - 2 * border) / (limit_y1 - limit_y0);
            sf::Color color_graph(255, 0, 0);
            for (int i = 0; i < coordinates.size(); i++) {
                double point_x = (coordinates[i].first - limit_x0) * scaling_factor_x + border;
                double point_y = y_size + (limit_y0 - coordinates[i].second) * scaling_factor_y - border;

                sf::CircleShape shape(marker_size);
                shape.setPosition(point_x - marker_size, point_y - marker_size);
                shape.setFillColor(color_graph);
                window.draw(shape);
                if (i > 0) {
                    //make function for calculating a point
                    sf::VertexArray lines(sf::LinesStrip, 2);
                    lines[0].position = sf::Vector2f(point_x, point_y);
                    lines[0].color = sf::Color::Red;
                    lines[1].position = sf::Vector2f((coordinates[i - 1].first - limit_x0) * scaling_factor_x + border,
                        y_size + (limit_y0 - coordinates[i - 1].second) * scaling_factor_y - border);
                    lines[1].color = sf::Color::Red;
                    window.draw(lines);
                }
            }
            // Отрисовка окна	
            window.display();
        }
	}
};

#endif // INCLUDE_DRAWER_HPP_