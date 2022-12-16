#include "AddPop.h"
#include "ui_AddPop.h"
#include <QMessageBox>
#include <fstream>

using namespace std;

AddPop::AddPop(QWidget *parent) : QDialog(parent), ui(new Ui::AddPop) {
  ui->setupUi(this);
}

AddPop::~AddPop() { delete ui; }

void AddPop::add(string pos) {
  bool flag1, flag2, flag3, flag4;
  string title = ui->lineEdit_4->text().toStdString();
  string autor = ui->lineEdit_5->text().toStdString();
  int moodSH = ui->lineEdit_6->text().toInt(&flag1);
  int moodCI = ui->lineEdit_7->text().toInt(&flag2);
  int moodSHEnd = ui->lineEdit_8->text().toInt(&flag3);
  int moodCIEnd = ui->lineEdit_9->text().toInt(&flag4);
  if (title == "")
    QMessageBox::critical(this, "Add Composition", "Title is empty");
  else if (autor == "")
    QMessageBox::critical(this, "Add Composition", "Autor is empty");
  else if (!flag1 || moodSH < 1 || moodSH > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Sad/Happy)");
  else if (!flag2 || moodCI < 1 || moodCI > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Calm/Intense)");
  else if (!flag3 || moodSHEnd < 1 || moodSHEnd > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood 2 (Sad/Happy)");
  else if (!flag4 || moodCIEnd < 1 || moodCIEnd > 10)
    QMessageBox::critical(this, "Add Composition",
                          "Wrong Mood 2 (Calm/Intense)");
  else {
    ofstream fout("saveComp.txt", ofstream::out | ofstream::trunc);
    fout << pos << endl
         << "composition" << endl
         << title << endl
         << autor << endl
         << moodSH << endl
         << moodCI << endl
         << moodSHEnd << endl
         << moodCIEnd << endl;
    fout.close();
    this->close();
  }
}

void AddPop::on_pushButton_clicked() {
  add(ui->lineEdit_3->text().toStdString());
}

// Add paa to Head
void AddPop::on_pushButton_2_clicked() { add("End"); }