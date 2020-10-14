#include "fivewins.h"
#include "ui_fivewins.h"

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

