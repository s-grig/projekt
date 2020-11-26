#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

int main()
{
    char* outText;
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init("C:\\vcpkg\\buildtrees\\tesseract\\src\\4.1.1-3a7d5a1d2b.clean\\tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    api->SetVariable("tessedit_char_whitelist", "0123456789-.");
    // Open input image with leptonica library
    Pix* image = pixRead("C:\\DATA\\Github_Stas\\1111.png");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    //printf("OCR output:\n%s", outText);
    std::cout << std::endl;
    // Destroy used object and release memory
    api->End();
    std::string str(outText);
    std::string x, y;
    x = str.substr(0, str.find('\n'));
    y = str.substr(x.length() + 1);
    std::cout << str << std::endl << std::endl;
    std::cout << "that is x "  << x << std::endl << std::endl;
    std::cout << "that is y " << y << std::endl << std::endl;
    delete[] outText;
    pixDestroy(&image); 

  /* std::vector<std::pair<int, int>> coordinates;
   for (int i = 0; i < 5; i++) {
      coordinates.push_back(std::make_pair(5*i, i));
   }
   coordinates.push_back(std::make_pair(1, 25));
   coordinates.push_back(std::make_pair(3, 15));
   coordinates.push_back(std::make_pair(10, 12));
   coordinates.push_back(std::make_pair(15, 5));
   unsigned int x_size = 1000;
   unsigned int y_size = 800;
   int border = 0;

   double limit_x0 = -10;
   double limit_x1 = 10;
   double limit_y0 = -10;
   double limit_y1 = 10;

   auto tmp =  std::max_element(coordinates.begin(), coordinates.end(),
       [](const auto& a, const auto& b) {
           return abs(a.first) < (b.first);
       });
   int mod_x = (*tmp).first;

   tmp = std::max_element(coordinates.begin(), coordinates.end(),
       [](const auto& a, const auto& b) {
           return abs(a.second) < (b.second);
       });
   int mod_y = (*tmp).second;

   if (mod_y > mod_x) {
       while (mod_y % 5 != 0)
       {
           mod_y++;
       } 
       if (mod_y == 0) {
           limit_x1 = limit_y1 = 5;
       }
       limit_x1 = limit_y1 = mod_y;
       limit_x0 = limit_y0 = - mod_y;
   } else{
       while (mod_x % 5 != 0)
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

   sf::RenderWindow window(sf::VideoMode(x_size, y_size), "Funtion plot");

    // ������� ���� ����������. �����������, ���� ������� ����
    while (window.isOpen()) {
        // ������������ ������� ������� � �����
        sf::Event event;
        while (window.pollEvent(event)) {
            // ������������ ����� �� �������� � ����� ������� ����?
            if (event.type == sf::Event::Closed)
                // ����� ��������� ���
                window.close();
        }
        window.clear(sf::Color(255, 255, 255, 0));
        //axis
        sf::RectangleShape line;
        line.setFillColor(sf::Color(0, 0, 0));
        int new_center_x = x_size / 2;
        int new_center_y = y_size / 2;
        //��������� Y
        line.setPosition(border, new_center_y);
        line.setSize(sf::Vector2f(x_size - 2 *border, 4));
        window.draw(line);

        //����������� X
        line.setPosition(new_center_x, border);
        line.setSize(sf::Vector2f(4, y_size - 2 * border));
        window.draw(line);

        sf::Font font;
        if (!font.loadFromFile("D:\\Github\\arial.ttf")) {
            std::cout << "������ ������ ������" << std::endl;
        }

        sf::Text text;
        text.setCharacterSize(10); 
        text.setFillColor(sf::Color(0, 0, 0));
        text.setFont(font);

        unsigned count_marker_y = limit_y1 - limit_y0 / step_y;
        unsigned len_axis_y = y_size - 2 * border;
        for (unsigned u = 0; u <= count_marker_y; u++) {
            //�����
            int var = limit_y0 + (count_marker_y - u) * step_y;
            std::string s = std::to_string(var);
            text.setString(s);
            text.setPosition(new_center_x + 15, len_axis_y / count_marker_y * u + border - 10);
            window.draw(text);

            line.setFillColor(sf::Color(0, 0, 0));
            //��������������
            line.setPosition(border, len_axis_y / count_marker_y * u + border);
            line.setSize(sf::Vector2f(x_size - 2 * border, 1));
            window.draw(line);
        }

        //�������� �������������� ���
        unsigned count_marker_x = limit_x1 - limit_x0 / step_x;
        unsigned len_axis_x = x_size - 2 * border;
        for (unsigned u = 0; u <= count_marker_x; ++u) {
            //�����
            int var = limit_x0 + u * step_x;
            std::string s = std::to_string(var);
            text.setString(s);
            text.setPosition(len_axis_x / count_marker_x * u + border, new_center_y + 15);
            window.draw(text);

            //��������������� ����� �����
            //������������
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
        text.setPosition(new_center_x  - 15, border);
        window.draw(text);

        double scaling_factor_x = (x_size - 2 * border)  / (limit_x1 - limit_x0); //������ � ������
        double scaling_factor_y = (y_size - 2 * border) / (limit_y1 - limit_y0);
        unsigned int marker_size = 3;

        sf::Color color_graph(255, 0, 0);
        for (int i = 0; i < coordinates.size(); i++) {
          //colors0.erase(colors0.begin());
            double point_x_old = (coordinates[i].first - limit_x0) * scaling_factor_x + border;
            double point_y_old = y_size + (limit_y0 - coordinates[i].second) * scaling_factor_y - border;

            sf::CircleShape shape(marker_size);
            shape.setPosition(point_x_old - marker_size, point_y_old - marker_size);
            shape.setFillColor(color_graph);
            window.draw(shape);
            if (i > 0) {
                //make function for calculating a point
                sf::VertexArray lines(sf::LinesStrip, 2);
                lines[0].position = sf::Vector2f(point_x_old, point_y_old);
                lines[0].color = sf::Color::Red;
                lines[1].position = sf::Vector2f((coordinates[i - 1].first - limit_x0) * scaling_factor_x + border,
                    y_size + (limit_y0 - coordinates[i - 1].second) * scaling_factor_y - border);
                lines[1].color = sf::Color::Red;
                window.draw(lines);
            }
        }
        // ��������� ����	
        window.display(); 
    }*/
   return 0;
}
