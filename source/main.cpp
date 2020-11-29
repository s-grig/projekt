//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
#include <iostream>
#include <string>
#include <exception>
#include <drawer.hpp>
#include <ui.hpp>
#include <QApplication>
#include <exception>


int main(int argc, char* argv[]) {
    try {
        QApplication app(argc, argv);
        Win win(0);
        win.resize(150, 150);
        win.show();
        return app.exec();
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
   /* std::string path_to_photo = win.get_path().toUtf8().constData();
    std::string outText;
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    //api->SetVariable("tessedit_char_whitelist", "0123456789-.");
    try {
        if (api->Init("C:\\vcpkg\\buildtrees\\tesseract\\src\\4.1.1-3a7d5a1d2b.clean\\tessdata", "eng")) {
            throw std::exception("Could not initialize tesseract.");
        }
        Pix* image = pixRead(path_to_photo.c_str());
        api->SetImage(image);
        outText = api->GetUTF8Text();
        api->End();

        //Проверка считывания
        for (int i = 0; i < outText.size(); i++) {
            if (((outText[i] > '9') || (outText[i] < '0') && ((outText[i] != '-')
                || (outText[i] != ' ') || (outText[i] != '\n') || (outText[i] != '.')))) {
                std::cout << outText << std::endl;
                throw std::exception("Input is not a number or Tesseract interpretted it wrong. Try again.");
            }
        }
        std::cout << "Input is "<< outText << std::endl << std::endl;

        //Проверка наличия всех координат
        std::string x, y, tmp;
        std::vector<int> x_vec, y_vec;
        x = outText.substr(0, outText.find('\n'));
        y = outText.substr(x.length() + 1, outText.find('\n', x.length() + 1) - 1);
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
        if (x.size() != y.size()) {
            std::cout << "That is x " << x << std::endl;
            std::cout << "That is y " << y << std::endl;
            throw std::exception("Input is not a number or Tesseract interpretted it wrong. Try again.");
        }
        std::cout << "that is x " << x << std::endl << std::endl;
        std::cout << "that is y " << y << std::endl << std::endl;
        pixDestroy(&image);

        function_plot_drawer object;
        object.main_cicle(x, y);
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }*/
}
