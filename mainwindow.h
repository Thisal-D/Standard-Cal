#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

const int BUTTON_COUNT = 20;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPushButton *buttons[BUTTON_COUNT];
    QLineEdit * entry;
    void resizeEvent(QResizeEvent *);
    void onButtonClick(QEvent *);
    void setWidgetsStyles();
    void setMainStyle();
    void pressButton(std::string);
    void connectWidgetsEvents();
    void clearCal();
    void cutLastChar();
    void addDecimalPoint();
    void addDevision();
    void addMultiply();
    void addSubtract();
    void addAddition();
    void convertToInt();
    void convertToFloat();  
    void calculate();
    std::string getOperator(std::string);
    bool isTwoNumbers(std::string, std::string);
    template <typename T> T getTotal(T, T, std::string);
};
#endif // MAINWINDOW_H
