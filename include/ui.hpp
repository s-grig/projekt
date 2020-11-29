#ifndef menu_hpp
#define menu_hpp
#include <QtGui>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>
#include <exception>
#include <drawer.hpp>

class Win : public QWidget {
	Q_OBJECT
public:
	Win(QWidget* parent = 0);
	QString get_path();
	void set_path(const QString& path_);
	std::pair<std::string, std::string> photo_processing();
public slots:
	void clicked_choose();
private:
	QLabel* label;
	QPushButton* exitButton;
	QPushButton* chooseButton;
	QString path;
};
#endif
