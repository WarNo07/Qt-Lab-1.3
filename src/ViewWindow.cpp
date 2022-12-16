#include "Playlist.h"
#include "ui_ViewWindow.h"
#include "ViewWindow.h"
#include <QStandardItem>
#include <QStandardItemModel>

ViewWindow::ViewWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ViewWindow) {
  ui->setupUi(this);
}

ViewWindow::~ViewWindow() { delete ui; }

void ViewWindow::on_pushButton_clicked() { hide(); }

void ViewWindow::insertData(Playlist collection, int size) const {
  QStandardItemModel *model = new QStandardItemModel;
  QStandardItem *item;
  for (int i = 0; i < size; i++) {
    item = new QStandardItem(QString("#" + QString::number(i + 1)));
    model->appendRow(item);
    item = new QStandardItem(
        QString(QString::fromStdString(collection.getComp(i)->getType())));
    model->appendRow(item);
    item = new QStandardItem(
        QString(QString::fromStdString(collection.getComp(i)->getTitle())));
    model->appendRow(item);
    item = new QStandardItem(
        QString(QString::fromStdString(collection.getComp(i)->getAutor())));
    model->appendRow(item);
    item = new QStandardItem(
        QString("MoodSH: " +
                QString::number(collection.getComp(i)->getMoodSadHappy())));
    model->appendRow(item);
    item = new QStandardItem(
        QString("MoodCI: " +
                QString::number(collection.getComp(i)->getMoodCalmIntense())));
    model->appendRow(item);

    if (collection.getComp(i)->getType() == "popurry") {
      item = new QStandardItem(QString(
          "MoodSH 2: " +
          QString::number(collection.getComp(i)->getMoodSadHappyEnd())));
      model->appendRow(item);
      item = new QStandardItem(QString(
          "MoodCI 2: " +
          QString::number(collection.getComp(i)->getMoodCalmIntenseEnd())));
      model->appendRow(item);
    }
    item = new QStandardItem(QString("   "));
    model->appendRow(item);
  }
  ui->listView->setModel(model);
}
