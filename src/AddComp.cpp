#include "AddComp.h"
#include "ui_AddComp.h"
#include <QMessageBox>
#include <fstream>

using namespace std;

AddComp::AddComp(QWidget *parent) : QDialog(parent), ui(new Ui::AddComp) {
  ui->setupUi(this);
}

AddComp::~AddComp() { delete ui; }

void AddComp::add(string pos) {
  bool flag1, flag2;
  string title = ui->lineEdit_4->text().toStdString();
  string autor = ui->lineEdit_5->text().toStdString();
  int moodSH = ui->lineEdit_6->text().toInt(&flag1);
  int moodCI = ui->lineEdit_7->text().toInt(&flag2);
  if (title == "")
    QMessageBox::critical(this, "Add Composition", "Title is empty");
  else if (autor == "")
    QMessageBox::critical(this, "Add Composition", "Autor is empty");
  else if (!flag1 || moodSH < 1 || moodSH > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Sad/Happy)");
  else if (!flag2 || moodCI < 1 || moodCI > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Calm/Intense)");
  else {
    ofstream fout("saveComp.txt", ofstream::out | ofstream::trunc);
    fout << pos << endl
         << "composition" << endl
         << title << endl
         << autor << endl
         << moodSH << endl
         << moodCI << endl;
    fout.close();
    this->close();
  }
}

void AddComp::on_pushButton_clicked() {
  add(ui->lineEdit_3->text().toStdString());
}

void AddComp::on_pushButton_2_clicked() { add("End"); }
