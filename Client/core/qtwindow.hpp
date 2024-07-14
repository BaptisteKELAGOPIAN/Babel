#ifndef QTWINDOW_H
#define QTWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <iostream>
#include <string>

class Qtwindow {
public:
    Qtwindow(){};
    ~Qtwindow(){};
    void init()
    {
        int argc = 0;
        char **argv = nullptr;
        QApplication a(argc, argv);

        QMainWindow window;
        QLabel *label = new QLabel(QString::fromStdString("oui"), &window);

        QLineEdit *lineEdit = new QLineEdit(&window);

        QPushButton *button = new QPushButton("OK", &window);

        // QObject::connect(button, &QPushButton::clicked, [=](){ myFunction(lineEdit->text()); });

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(label);
        layout->addWidget(lineEdit);
        layout->addWidget(button);

        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        window.setCentralWidget(widget);

        window.show();

        a.exec();
        return;
    }
    void update(std::string message)
    {
        std::cout << message << std::endl;
        // label->setText(QString::fromStdString(message));
        // label->update();
    }

private: 
};

#endif // QTWINDOW_H