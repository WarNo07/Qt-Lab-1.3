#include "AddComp.h"
#include "AddPop.h"
#include "FirstWindow.h"
#include "ViewWindow.h"
#include "ui_FirstWindow.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

FirstWindow::FirstWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::FirstWindow) {
  ui->setupUi(this);
  if (plt.getSize() == 0) {
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
  }
}

FirstWindow::~FirstWindow() { delete ui; }

Playlist getComp(Playlist &p) {
  ifstream File("saveComp.txt");
  if (File.is_open()) {
    string title, autor, type, pos;
    int moodSH, moodCI, moodSHEnd, moodCIEnd;
    File >> pos;
    File >> type;
    File >> title;
    File >> autor;
    File >> moodSH;
    File >> moodCI;

    if (type == "composition") {
      Composition a(title, autor, moodSH, moodCI);
      if (pos == "End")
        p.addComp(a);
      else
        p.setComp(a, stoi(pos));
    } else {
      File >> moodSHEnd;
      File >> moodCIEnd;
      Popurry a(title, autor, moodSH, moodCI, moodSHEnd, moodCIEnd);
      if (pos == "End") {
        p.addComp(a);
      } else {
        p.setComp(a, stoi(pos));
      }
    }
  }
  return p;
}

void FirstWindow::on_pushButton_13_clicked() {
  AddComp window;
  window.setModal(true);
  window.show();
  window.exec();
  plt = getComp(plt);
  ui->lineEdit_5->setEnabled(true);
  ui->lineEdit_7->setEnabled(true);
  ui->pushButton_4->setDisabled(false);
  ui->pushButton_5->setDisabled(false);
  ui->pushButton_6->setDisabled(false);
  ui->pushButton_7->setDisabled(false);
  ui->pushButton_9->setDisabled(false);
}

void FirstWindow::on_pushButton_14_clicked() {
  AddPop window;
  window.setModal(true);
  window.show();
  window.exec();
  plt = getComp(plt);
  ui->lineEdit_5->setEnabled(true);
  ui->lineEdit_7->setEnabled(true);
  ui->pushButton_4->setDisabled(false);
  ui->pushButton_5->setDisabled(false);
  ui->pushButton_6->setDisabled(false);
  ui->pushButton_7->setDisabled(false);
  ui->pushButton_9->setDisabled(false);
}

void FirstWindow::on_pushButton_4_clicked() {
  string pos = ui->lineEdit_5->text().toStdString();
  ui->lineEdit_5->clear();
  plt.delComp(atoi(pos.c_str()));
  if (plt.getSize() == 0) {
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
  }
  QMessageBox::information(this, "Delete Music", "You delete Music");
}

void FirstWindow::on_pushButton_5_clicked() {
  if (plt.getSize()) {
    plt.delAll();
    ui->lineEdit_5->setEnabled(false);
    ui->lineEdit_7->setEnabled(false);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_7->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    QMessageBox::information(this, "Clear", "You delete all Playlist");
  }
}

void FirstWindow::on_pushButton_6_clicked() {
  if (plt.getSize()) {
    QMessageBox::information(this, "Size",
                             "The size of the Playlist is " +
                                 QString::number(plt.getSize()));
  }
}

void FirstWindow::on_pushButton_7_clicked() {
  if (plt.getSize() != 0) {
    ViewWindow window;
    window.setModal(true);
    window.insertData(plt, plt.getSize());
    window.show();
    window.exec();
  }
}

void FirstWindow::on_pushButton_8_clicked() {
  plt.fileInput(ui->lineEdit_6->text().toStdString());
  ui->lineEdit_6->clear();
  ui->lineEdit_5->setEnabled(true);
  ui->lineEdit_7->setEnabled(true);
  ui->pushButton_4->setDisabled(false);
  ui->pushButton_5->setDisabled(false);
  ui->pushButton_6->setDisabled(false);
  ui->pushButton_7->setDisabled(false);
  ui->pushButton_9->setDisabled(false);
  QMessageBox::information(this, "Input from file", "Input from file");
}

void FirstWindow::on_pushButton_9_clicked() {
  if (plt.getSize()) {
    plt.fileOutput(ui->lineEdit_7->text().toStdString());
    ui->lineEdit_7->clear();
    QMessageBox::information(this, "Output to file", "Uutput to file");
  }
}

void FirstWindow::on_pushButton_clicked() {

  bool flag1, flag2, flag3, flag4;
  int moodSH = ui->lineEdit_8->text().toInt(&flag1),
      moodCI = ui->lineEdit_9->text().toInt(&flag2),
      moodSHEnd = ui->lineEdit_10->text().toInt(&flag3),
      moodCIEnd = ui->lineEdit_11->text().toInt(&flag4);
  if (!flag1 || moodSH < 1 || moodSH > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Sad/Happy)");
  else if (!flag2 || moodCI < 1 || moodCI > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood (Calm/Intense)");
  else if (!flag3 || moodSHEnd < 1 || moodSHEnd > 10)
    QMessageBox::critical(this, "Add Composition", "Wrong Mood 2 (Sad/Happy)");
  else if (!flag4 || moodCIEnd < 1 || moodCIEnd > 10)
    QMessageBox::critical(this, "Add Composition",
                          "Wrong Mood 2 (Calm/Intense)");
  else {
    Playlist plt2(plt.getWay(moodSH, moodCI, moodSHEnd, moodCIEnd));
    if (plt2.getSize()) {
      ViewWindow window;
      window.setModal(true);
      window.insertData(plt2, plt2.getSize());
      window.show();
      window.exec();
    }
  }
}
