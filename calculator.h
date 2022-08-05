#include<QWidget>
#include<QVector>
#include<QPushButton>
#include<QLineEdit>
#include<QKeyEvent>
#ifndef CALCULATOR_H
#define CALCULATOR_H

#endif // CALCULATOR_H
class Calculator:public QWidget{

    Q_OBJECT

    private:
        QVector<QPushButton> numberButtons;
        QLineEdit *textFeild;
        QString expressionstring;


      protected:
        void keyPressEvent(QKeyEvent *event) override;

    public: Calculator(QWidget *parent=nullptr);



    void onButtonClick(const QChar &str);

    void compute();

    void onClear();


};
