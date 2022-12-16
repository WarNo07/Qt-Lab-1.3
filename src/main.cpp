#include "Composition.h"
#include "Playlist.h"
#include "Popurry.h"
#include "FirstWindow.h"
#include <assert.h>
#include <iostream>
//#include "Composition.cpp"
//#include "Playlist.cpp"
#include <QApplication>

using namespace std;

void printPlaylist(Playlist* Ans) {
  for (int i = 0; i < Ans->getSize(); i++) {
    cout << i << endl;
    cout << Ans->getComp(i)->getType() << endl;
    cout << Ans->getComp(i)->getTitle() << endl;
    cout << Ans->getComp(i)->getAutor() << endl;
    cout << Ans->getComp(i)->getMoodSadHappy() << endl;
    cout << Ans->getComp(i)->getMoodCalmIntense() << endl;
    if (Ans->getComp(i)->getType() == "popurry"){
    cout << Ans->getComp(i)->getMoodSadHappyEnd() << endl;
    cout << Ans->getComp(i)->getMoodCalmIntenseEnd() << endl;  
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
  cout << "Test Composition:" << endl;
  Composition first;

  assert(first.getTitle() == "No Info");
  assert(first.getAutor() == "No Info");
  assert(first.getMoodSadHappy() == 1);
  assert(first.getMoodCalmIntense() == 1);

  first.setTitle("Music1");
  first.setAutor("Autor1");

  assert(!first.setMoodSadHappy(15));
  assert(!first.setMoodCalmIntense(15));

  assert(first.getTitle() == "Music1");
  assert(first.getAutor() == "Autor1");
  assert(first.getMoodSadHappy() == 1);
  assert(first.getMoodCalmIntense() == 1);

  assert(first.setMoodSadHappy(5));
  assert(first.setMoodCalmIntense(5));
  assert(first.getMoodSadHappy() == 5);
  assert(first.getMoodCalmIntense() == 5);

  Composition second("Music2", "Autor2", 5, 7);

  assert(second.getTitle() == "Music2");
  assert(second.getAutor() == "Autor2");
  assert(second.getMoodSadHappy() == 5);
  assert(second.getMoodCalmIntense() == 7);

  Composition third(second);

  assert(third.getTitle() == "Music2");
  assert(third.getAutor() == "Autor2");
  assert(third.getMoodSadHappy() == 5);
  assert(third.getMoodCalmIntense() == 7);

  cout << "Composition class is correct!" << endl;
  cout << "Test Popurry:" << endl;

  Popurry firstP;
  
  assert(firstP.getTitle() == "No Info");
  assert(firstP.getAutor() == "No Info");
  assert(firstP.getMoodSadHappy() == 1);
  assert(firstP.getMoodCalmIntense() == 1);
  assert(firstP.getMoodSadHappyEnd() == 1);
  assert(firstP.getMoodCalmIntenseEnd() == 1);

  assert(first.setMoodSadHappyEnd(5));
  assert(first.setMoodCalmIntenseEnd(5));
  assert(first.getMoodSadHappyEnd() == 5);
  assert(first.getMoodCalmIntenseEnd() == 5);

  Popurry secondP("Music2", "Autor2", 5, 7, 6, 8);
  assert(secondP.getTitle() == "Music2");
  assert(secondP.getAutor() == "Autor2");
  assert(secondP.getMoodSadHappy() == 5);
  assert(secondP.getMoodCalmIntense() == 7);
  assert(secondP.getMoodSadHappyEnd() == 6);
  assert(secondP.getMoodCalmIntenseEnd() == 8);

  Popurry thirdP(secondP);
  assert(thirdP.getTitle() == "Music2");
  assert(thirdP.getAutor() == "Autor2");
  assert(thirdP.getMoodSadHappy() == 5);
  assert(thirdP.getMoodCalmIntense() == 7);
  assert(thirdP.getMoodSadHappyEnd() == 6);
  assert(thirdP.getMoodCalmIntenseEnd() == 8);
  
  cout << "Popurry class is correct!" << endl;
  cout << "Test Playlist:" << endl;

  Playlist firstPlaylist(5);
  assert(firstPlaylist.getSize() == 5);
  
  firstPlaylist.addComp(firstP);
  assert(firstPlaylist.getSize() == 6);
  
  firstPlaylist.delComp(1);
  assert(firstPlaylist.getSize() == 5);
  
  
  Playlist secondPlaylist(firstPlaylist);
  
  assert(secondPlaylist.isEqual(firstPlaylist));
  
  secondPlaylist.setComp(third, 0);
  assert(!secondPlaylist.isEqual(firstPlaylist));
  
  firstPlaylist.delAll();
  assert(firstPlaylist.getSize() == 0);

  Playlist thirdPlaylist;
  thirdPlaylist.fileInput("testIn.txt");
  thirdPlaylist.fileOutput("testOut.txt");
  firstPlaylist.fileInput("testOut.txt");

  printPlaylist(&firstPlaylist);
  
  assert(thirdPlaylist.isEqual(firstPlaylist));

  cout << "Algorithm test" << endl;
  Playlist fourthPlaylist(firstPlaylist.getWay(3, 3, 5, 5));
  printPlaylist(&fourthPlaylist);

  cout << "Playlist class is correct!" << endl;

  QApplication a(argc, argv);
  FirstWindow w;
  w.show();
  return a.exec();
}