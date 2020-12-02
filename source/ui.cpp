#include "ui.hpp"
#include "moc_ui.cpp"
 Win::Win(QWidget* parent) :QWidget(parent) {
	setWindowTitle("Plot builder");
	label = new QLabel("Choose a photo with digits or press the exit button", this);
	exitButton = new QPushButton("Exit", this);
	chooseButton = new QPushButton("Choose file", this);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(label);
	layout->addWidget(chooseButton);
	layout->addWidget(exitButton);
	connect(exitButton, SIGNAL(clicked(bool)),
		this, SLOT(close()));
	connect(chooseButton, SIGNAL(clicked(bool)),
		this, SLOT(clicked_choose()));
}

void Win::clicked_choose() {
	QString path_ = QFileDialog::getOpenFileName(this, QObject::tr("Choose file"), QDir::homePath(),
		QObject::tr("Photo (*.png);;All files (*.*)"));
	this->set_path(path_);
    auto p = this->photo_processing();
    std::string x = p.first;
    std::string y = p.second;
    function_plot_drawer object;
    object.main_cicle(x, y);
}

void Win::set_path(const QString& path_) {
	path = path_;
}

QString Win::get_path() {
    return path;
}

std::pair<std::string, std::string> Win::photo_processing() {
    std::string path_to_photo = get_path().toUtf8().constData();
    std::string outText;
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("C:\\DATA\\GitHub_Stas\\projekt\\file\\tessdata\\", "eng")) {
        throw std::exception("Could not initialize tesseract.");
    }
    Pix* image = pixRead(path_to_photo.c_str());
    api->SetImage(image);
    outText = api->GetUTF8Text();
    api->End();
    pixDestroy(&image);
    //Проверка считывания
     for (int i = 0; i < outText.size(); i++) {  
        // if (((outText[i] > '9') || (outText[i] < '0')) && ((outText[i] != '-')
           //  || (outText[i] != ' ') || (outText[i] != '\n') || (outText[i] != '.'))) {
           //  std::cout << outText << std::endl;
            // throw std::exception("Input is not a number or Tesseract interpretted it wrong. Try again.");
        // }
     }
     std::cout << "Input is: " << std::endl << outText << std::endl << std::endl;

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
   //  for (auto el : x_vec) {
        // std::cout << el << std::endl;
   //  }

     //Извлечь y
    /* for (int i = 0; i < y.size(); i++) {
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
     }*/
     std::cout << "That is x " << x << std::endl << std::endl;
     std::cout << "That is y " << y << std::endl << std::endl;
     return std::make_pair(x, y);
}

