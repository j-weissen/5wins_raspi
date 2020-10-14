#include "fivewins.h"
#include "ui_fivewins.h"

//git test

fiveWins::fiveWins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fiveWins)
{
    ui->setupUi(this);
}

fiveWins::~fiveWins()
{
    delete ui;
}

