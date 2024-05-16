#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QResizeEvent>
#include <string>
#include <iostream>
#include <iostream>
#include "utils.h"

// main window class all widgets are in here :D
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create line edit and buttons
    entry = new QLineEdit();
    std::string button_texts[] = {
                    "C", "←", ".", "/",
                    "7", "8", "9", "*",
                    "4", "5", "6", "-",
                    "1", "2", "3", "+",
                    "0", "float", "int", "="};

    for(int i = 0; i < BUTTON_COUNT; ++i) {
        buttons[i] = new QPushButton(button_texts[i].c_str());
    }

    // Create grid layout
    QGridLayout *layout = new QGridLayout(this);
    // 0 Row Line Edit
    layout->addWidget(entry, 0, 0, 1, 4);

    // First row
    layout->addWidget(buttons[0], 1, 0);
    layout->addWidget(buttons[1], 1, 1);
    layout->addWidget(buttons[2], 1, 2);
    layout->addWidget(buttons[3], 1, 3);

    // Second row
    layout->addWidget(buttons[4], 2, 0);
    layout->addWidget(buttons[5], 2, 1);
    layout->addWidget(buttons[6], 2, 2);
    layout->addWidget(buttons[7], 2, 3);

    // Third row
    layout->addWidget(buttons[8], 3, 0);
    layout->addWidget(buttons[9], 3, 1);
    layout->addWidget(buttons[10], 3, 2);
    layout->addWidget(buttons[11], 3, 3);

    // Fourth row
    layout->addWidget(buttons[12], 4, 0);
    layout->addWidget(buttons[13], 4, 1);
    layout->addWidget(buttons[14], 4, 2);
    layout->addWidget(buttons[15], 4, 3);

    // Fifth row
    layout->addWidget(buttons[16], 5, 0);
    layout->addWidget(buttons[17], 5, 1);
    layout->addWidget(buttons[18], 5,2);
    layout->addWidget(buttons[19], 5, 3);

    // Create central widget and set layout
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Create resize support to Widgets. Reize widgets depend on window size
    entry->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    for (size_t i=0; i<BUTTON_COUNT; i++){
        buttons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // Set Widgets colors
    this->setWidgetsStyles();
    // this->setMainStyle();
    this->connectWidgetsEvents();

}

// Button press callback
void MainWindow::pressButton(std::string value){
    std::cout << "Button Pressed" << std::endl;
    this->entry->insert(value.c_str());
}


void MainWindow::clearCal(){
    this->entry->clear();
}

void MainWindow::cutLastChar(){
    std::string text_now = this->entry->text().toStdString();
    this->entry->setText(text_now.substr(0, text_now.length()-1).c_str());
}

void MainWindow::addDecimalPoint(){
    this->entry->insert(".");
}

void MainWindow::addDevision(){
    this->calculate();
    this->entry->insert("/");
}

void MainWindow::addMultiply(){
    this->calculate();
    this->entry->insert("*");
}

void MainWindow::addSubtract(){
    this->calculate();
    this->entry->insert("-");
}

void MainWindow::addAddition(){
    this->calculate();
    this->entry->insert("+");
}

void MainWindow::convertToInt(){
    try{
        std::string value = this->entry->text().toStdString();
        this->entry->setText(Utils::split(value, ".")[0].c_str());
    }
    catch(std::exception &ex){
        std::cout << ex.what();
    }
}

void MainWindow::convertToFloat(){
    try{
        double value = this->entry->text().toDouble();
        this->entry->setText(std::to_string(value).c_str());
    }
    catch(std::exception &ex){
        std::cout << ex.what();
    }
}

std::string MainWindow::getOperator(std::string value){
    std::string op="";
    if (value.find("/")!=-1) op = "/";
    if (value.find("*")!=-1) op = "*";
    if (value.find("-")!=-1) op = "-";
    if (value.find("+")!=-1) op = "+";

    return op;
}

bool MainWindow::isTwoNumbers(std::string value, std::string op){
    std::vector<std::string> split_numbers = Utils::split(value, op);
    if(Utils::isANumber(split_numbers[0]) && Utils::isANumber(split_numbers[1])){
        return true;
    }
    return false;
}

template <typename T>
T MainWindow::getTotal(T num1, T num2, std::string op){
    if (op=="+") return num1 + num2;
    if (op=="-") return num1 - num2;
    if (op=="/") return num1 / num2;
    if (op=="*") return num1 * num2;
    return 0;
}

void MainWindow::calculate(){
    std::string input = this->entry->text().toStdString();
    std::string op = this->getOperator(input);
    if (op=="") return;
    if (this->isTwoNumbers(input, op)){
        std::vector<std::string> split_numbers = Utils::split(input, op);
        if (Utils::isFloat(split_numbers[0]) || Utils::isFloat(split_numbers[1]) || op=="/"){
            long double num1 = std::stold(split_numbers[0]);
            long double num2 = std::stold(split_numbers[1]);
            long double total = this->getTotal<long double>(num1, num2, op);
            this->entry->setText(std::to_string(total).c_str());
        }
        else{
            long long int num1 = std::stoll(split_numbers[0]);
            long long int num2 = std::stoll(split_numbers[1]);
            long long int total = this->getTotal<long long int>(num1, num2, op);
            this->entry->setText(std::to_string(total).c_str());
        }
    }
}

void  MainWindow::connectWidgetsEvents(){
    for (size_t i=0; i<BUTTON_COUNT; i++){
        if (Utils::isANumber(buttons[i]->text().toStdString())){
            connect(buttons[i], &QPushButton::clicked, [=]() {this->pressButton(buttons[i]->text().toStdString().c_str());});
        }
        else if(buttons[i]->text()=="C"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::clearCal) ;
        }
        else if(buttons[i]->text()=="<--"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::cutLastChar);
        }
        else if(buttons[i]->text()=="."){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::addDecimalPoint);
        }
        else if(buttons[i]->text()=="/"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::addDevision);
        }
        else if(buttons[i]->text()=="*"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::addMultiply);
        }
        else if(buttons[i]->text()=="-"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::addSubtract);
        }
        else if(buttons[i]->text()=="+"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::addAddition);
        }
        else if(buttons[i]->text()=="int"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::convertToInt);
        }
        else if(buttons[i]->text()=="float"){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::convertToFloat);
        }
        else if(buttons[i]->text()=="="){
            connect(buttons[i], &QPushButton::clicked, this, &MainWindow::calculate);
        }
    }
}
// Destructer
MainWindow::~MainWindow() {

}

// Custom slot to resize buttons
void MainWindow::resizeEvent(QResizeEvent *event) {
    std::cout << "Resize Event Called" << std::endl;

    int fontSize = event->size().height() / 15;
    QFont font;
    font.setPixelSize(fontSize);
    entry->setFont(font);

    // Calculate font size based on window height
    fontSize = event->size().height() / 20;
    font.setPixelSize(fontSize);
    // Set font size for each button
    for(int i = 0; i < BUTTON_COUNT; ++i) {
        buttons[i]->setFont(font);
    }
}

// need to set widgets styles usings css, idk how to do it stil
/*
void MainWindow::setMainStyle(){
    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);
} 
*/

void MainWindow::setWidgetsStyles(){
    std::string entry_style = "font-weight:bold";
    entry->setStyleSheet(entry_style.c_str());
}

// Button click events
void onButtonClick(QEvent *event){
    std::cout << "Button Pressed" << std::endl;
}


