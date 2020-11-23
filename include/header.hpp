/*#include <SFML/Graphics.hpp>

#ifndef INCLUDE_HEADER_HPP_

#define INCLUDE_HEADER_HPP_

class function_plot {
	std::vector<std::pair<int, int>> coordinates;
	unsigned int x_size = 1000;
	unsigned int y_size = 800;
	int border = 0;

	int new_center_x;
	int new_center_y;

	double limit_x0 = -10;
	double limit_x1 = 10;
	double limit_y0 = -10;
	double limit_y1 = 10;

	double step_x = 1;
	double step_y = 1;

	double scaling_factor_x; //Пиксел в натуре
	double scaling_factor_y;
public:

	void main_cicle() {
		sf::RenderWindow window(sf::VideoMode(x_size, y_size), "Funtion plot");
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(sf::Color(255, 255, 255, 0));
			window.display();
		}
	}

	void draw_coordinate_plane() {
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
        if (!font.loadFromFile("D:\\Github\\arial.ttf")) {
            std::cout << "Ошибка чтения шрифта" << std::endl;
        }

        sf::Text text;
        text.setCharacterSize(10);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setFont(font);

        unsigned count_marker_y = limit_y1 - limit_y0 / step_y;
        unsigned len_axis_y = y_size - 2 * border;
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
	}

    void draw_plot(){

    }

	double scaling_factor_x() {
		return (x_size - 2 * border) / (limit_x1 - limit_x0);
	}

	double scaling_factor_y() {
		return (y_size - 2 * border) / (limit_y1 - limit_y0);
	}

	double calc_point_x(std::vector<std::pair<int, int>> coordinates_) {
		return (coordinates_[i].first - limit_x0) * scaling_factor_x + border;
	}

	double calc_point_y(std::vector<std::pair<int, int>> coordinates_) {
		return y_size + (limit_y0 - coordinates_[i].second) * scaling_factor_y - border;
	}
};

#endif // INCLUDE_HEADER_HPP_*/