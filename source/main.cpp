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
 //       system("pause");
        return 1;
    }
}
