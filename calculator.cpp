#include "calculator.h"
#include<QLabel>
#include<QGridLayout>
#include<QDebug>
#include "exprtk.cpp"
//http://www.partow.net/programming/exprtk/index.html exprtk referencd
//https://medium.com/codex/how-to-deploy-your-qt-cross-platform-applications-to-macos-operating-system-using-macdeployqt-281614688dcf --for deployment
// macdeployqt path  /Users/navaneethb/Qt/6.3.1/macos/bin/macdeployqt
// pass -dmg to create dmg file

Calculator::Calculator(QWidget *parent):QWidget(parent){
    QVector<QPushButton*> buttons;
    QPushButton * equal = new QPushButton("=");

    QPushButton * clear = new QPushButton("AC");
    textFeild = new QLineEdit("0");
    //textFeild->setReadOnly(true);

    textFeild->setFixedWidth(150);

    QVector<QChar> buttonNames{'0','1','2','3','4','5','6','7','8','9','+','-','*','/','%','.','(',')'};
    auto *grid = new QGridLayout(this);
    QChar currentNum;
     int currentRow=0;
     int column=0;

     //adding merical buttons
     for(int i=0;i<buttonNames.size();i++){
        if(i%4==0){
            currentRow = currentRow+1;
            column=0;
        }

      currentNum = buttonNames[i];

      buttons.append(new QPushButton(currentNum));
       //adding listener to the button
      connect(buttons[i],&QPushButton::clicked,this,[this,currentNum](){
          this->onButtonClick(currentNum);
          //qInfo()<<"here"<<currentNum;
      });

    //adding button to grid layout
     grid->addWidget(buttons[i],currentRow,column);


      column = column+1;
    }


    grid->addWidget(textFeild,0,0);


    grid->addWidget(equal,currentRow+1,0);
    grid->addWidget(clear,currentRow+1,1);

    connect(equal,&QPushButton::clicked,this,&Calculator::compute);
    connect(clear,&QPushButton::clicked,this,&Calculator::onClear);
    setLayout(grid);
}

void Calculator::keyPressEvent(QKeyEvent *event)
     {

    qInfo()<<event->key();
        if(event->key()==Qt::Key::Key_Backspace || event->key()==Qt::Key::Key_Back){
            if(!expressionstring.isEmpty()){
                expressionstring.remove(expressionstring.size()-1,1);
                textFeild->setText(expressionstring);
            }
        }

     }

void Calculator::compute(){
    QString qstr = textFeild->displayText();
    int error;
    typedef double T;
    typedef exprtk::expression<T>   expression_t;
    //typedef exprtk::symbol_table<T> symbol_table_t;

    typedef exprtk::parser<T>       parser_t;
    std::string expression_string = qstr.toStdString();
    expression_t expression;
    parser_t parser;
    bool done = parser.compile(expression_string,expression);

    if(done){
        QString val = QString::number(expression.value());
        textFeild->setText(val);
        expressionstring.clear();
        expressionstring.append(val);

    }
    else{
        //qInfo()<<"ERROR"<<expression.results().count();
       textFeild->setText("NAN");
       expressionstring.clear();
    }

}

void Calculator::onClear(){
    expressionstring.clear();
    textFeild->setText(expressionstring);
}

void Calculator::onButtonClick(const QChar &str){


    expressionstring.append(str);
    textFeild->setText(expressionstring);
    //qInfo()<<str;
}
