#include "Playlist.h"
#include "Composition.h"
#include "Popurry.h"
#include <fstream>
#include <iostream>
#include <vector>

Playlist::Playlist() {
  size = 0;
  Mass.clear();
}

Playlist::Playlist(int sizeIn) {
  if (sizeIn >= 0) {
    size = sizeIn;
    for (int i = 0; i < size; i++)
      Mass.push_back(new Composition);
  }
}

Playlist::Playlist(const Playlist &obj) {
  size = obj.size;
  for (int i = 0; i < size; i++){
    if (obj.Mass[i]->getType() == "composition")
      Mass.push_back(new Composition);
    else
      Mass.push_back(new Popurry);
    *Mass[i] = *obj.Mass[i];
    }
  }

Playlist::~Playlist() { delAll(); }

void Playlist::setComp(Composition &comp, int i) {
  if (i < size && i >= 0){
    Mass[i] = new Composition(comp);
    }
}

void Playlist::setComp(Popurry &comp, int i) {
  if (i < size && i >= 0){
    Mass[i] = new Popurry(comp);
    }
}

void Playlist::addComp(Composition &comp) {
  size++;
  Mass.push_back(new Composition(comp));
}

void Playlist::addComp(Popurry &comp) {
  size++;
  Mass.push_back(new Popurry(comp));
}

Composition* Playlist::getComp(int i) const { return Mass[i]; };

int Playlist::getSize() const { return size; }

void Playlist::delComp(int i) {
  for (int j = i; j < size-1; j++)
    Mass[j] = Mass[j+1];
  size--;
}

void Playlist::delAll() {
  Mass.resize(0);
  size = 0;
}

vector<vector<vector<int>>> A;
vector<vector<vector<int>>> PStart;
vector<vector<vector<int>>> PEnd;
int N[11][11];
int N1[11][11];
int koefMoodSH, koefMoodCI;

void Playlist::Step(int n, int n1, int moodSHEnd, int moodCIEnd, int i, int j) const{
  if (n1*N[i][j] <= N1[i][j]*n){
    N[i][j] = n;
    N1[i][j] = n1;
    if (i*koefMoodSH < moodSHEnd*koefMoodSH)
      Step(n + A[i+koefMoodSH][j].size(), n1+1, moodSHEnd, moodCIEnd, i+koefMoodSH, j);
    if (j*koefMoodCI < moodCIEnd*koefMoodCI)
      Step(n + A[i][j+koefMoodCI].size(), n1+1, moodSHEnd, moodCIEnd, i, j+koefMoodCI);
    for (int k = 0; k < PStart[i][j].size(); k++){
      int i2 = Mass[PStart[i][j][k]]->getMoodSadHappyEnd(),
          j2 = Mass[PStart[i][j][k]]->getMoodCalmIntenseEnd();
      if (i2*koefMoodSH <= moodSHEnd*koefMoodSH &&
          j2*koefMoodCI <= moodCIEnd*koefMoodCI &&
          i2*koefMoodSH >= i*koefMoodSH &&
          j2*koefMoodCI >= j*koefMoodCI){
        Step(n + A[i2][j2].size() + 1, n1, moodSHEnd, moodCIEnd, i2, j2);
          }      
    }
  }
}

Playlist Playlist::getWay(int moodSHStart, int moodCIStart, int moodSHEnd,
                          int moodCIEnd) const {
  int iStart = -1, iEnd = -1;
  Playlist Ans;
  
  for (int i = 0; i < size; i++) {
    if (Mass[i]->getMoodSadHappy() == moodSHStart &&
        Mass[i]->getMoodCalmIntense() == moodCIStart)
      iStart = i;
    if (Mass[i]->getMoodSadHappy() == moodSHEnd &&
        Mass[i]->getMoodCalmIntense() == moodCIEnd && Mass[i]->getType() == "composition")
      iEnd = i;
  }

  if (iStart != -1 && iEnd != -1) {
    
    A.resize(11);
    PStart.resize(11);
    PEnd.resize(11);
    for (int i = 0; i < 11; i++){
      A[i].resize(11);
      PStart[i].resize(11);
      PEnd[i].resize(11);
    }
    for (int i = 0; i < 11; i++)
      for (int j = 0; j < 11; j++) {
        A[i][j].resize(0);
        PStart[i][j].resize(0);
        PEnd[i][j].resize(0);
      }

    int startMoodSH = Mass[iStart]->getMoodSadHappy(),
        startMoodCI = Mass[iStart]->getMoodCalmIntense(),
        endMoodSH = Mass[iEnd]->getMoodSadHappy(),
        endMoodCI = Mass[iEnd]->getMoodCalmIntense();

    if (startMoodSH <= endMoodSH)
      koefMoodSH = 1;
    else
      koefMoodSH = -1;
    if (startMoodCI <= endMoodCI)
      koefMoodCI = 1;
    else
      koefMoodCI = -1;

    for (int i = 0; i < size; i++)
      if (Mass[i]->getType() == "composition")
        A[Mass[i]->getMoodSadHappy()][Mass[i]->getMoodCalmIntense()].push_back(i);
      else if (Mass[i]->getType() == "popurry"){
        PStart[Mass[i]->getMoodSadHappy()][Mass[i]->getMoodCalmIntense()].push_back(i);
        PEnd[Mass[i]->getMoodSadHappyEnd()][Mass[i]->getMoodCalmIntenseEnd()].push_back(i);
      }

    int i, j;
    for (int i = 0; i < 11; i++)
      for (int j = 0; j < 11; j++){
        N[i][j] = 0;
        N1[i][j] = 0;
      }
    
    Step(A[moodSHStart][moodCIStart].size(), 0, moodSHEnd, moodCIEnd, moodSHStart, moodCIStart);

    i = moodSHEnd;
    j = moodCIEnd;

    Playlist Ans2;
    
    while (i != startMoodSH || j != startMoodCI) {
      for (int k = 0; k < A[i][j].size(); k++)
        Ans.addComp(*Mass[A[i][j][k]]);

      if (N[i - koefMoodSH][j] == N[i][j] - A[i][j].size())
        i -= koefMoodSH;
      else if (N[i][j - koefMoodCI] == N[i][j] - A[i][j].size())
        j -= koefMoodCI;
      else{
        bool flag = true;
        for (int k = 0; k < PEnd[i][j].size() && flag; k++){
          int i2 = Mass[PEnd[i][j][k]]->getMoodSadHappy(), 
              j2 = Mass[PEnd[i][j][k]]->getMoodCalmIntense();
          if (N[i2][j2] == N[i][j] - A[i][j].size()){
            Ans.addComp(*Mass[PEnd[i][j][k]]);
            i = i2;
            j = j2;
            flag = false;
          }
        }
      }
    }
    for (int k = 0; k < A[i][j].size(); k++)
        Ans.addComp(*Mass[A[i][j][k]]);
  }
  return Ans;
}

void Playlist::fileInput(string file) {
  ifstream File(file);
  
  if (File.is_open()) {
    bool flag = true;
    delAll();
    File >> size;
    if (File.fail() || size < 0)
      flag = false;

    int moodSH, moodCI, moodSHEnd, moodCIEnd;
    string title, autor, type;
    for (int i = 0; i < size && flag; i++) {
      
      File >> type;
      File >> title;
      File >> autor;
      if (title == "\n" || autor == "\n")
        flag = false;
      File >> moodSH;
      if (File.fail() || moodSH < 1 || moodSH > 10)
        flag = false;
      File >> moodCI;
      if (File.fail() || moodCI < 1 || moodCI > 10)
        flag = false;
      
      if (type == "composition"){
        Mass.push_back(new Composition(title, autor, moodSH, moodCI));
      } else {
        File >> moodSHEnd;
      if (File.fail() || moodSHEnd < 1 || moodSHEnd > 10){flag = false;}
      File >> moodCIEnd;
      if (File.fail() || moodCIEnd < 1 || moodCIEnd > 10){flag = false;}
        Mass.push_back(new Popurry(title, autor, moodSH, moodCI, moodSHEnd, moodCIEnd));
      }
      }
    if (!flag) {
      delAll();
    }
  }
}

void Playlist::fileOutput(string file) const {
  ofstream File(file);
  if (File.is_open()) {
    File << size;
    for (int i = 0; i < size; i++) {
      File << endl << Mass[i]->getType();
      File << endl << Mass[i]->getTitle();
      File << endl << Mass[i]->getAutor();
      File << endl << Mass[i]->getMoodSadHappy();
      File << endl << Mass[i]->getMoodCalmIntense();
      if (Mass[i]->getType() == "popurry"){
      File << endl << Mass[i]->getMoodSadHappyEnd();
      File << endl << Mass[i]->getMoodCalmIntenseEnd();  
      }
    }
  }
}

bool Playlist::isEqual(const Playlist &obj) const {
  bool flag = (size == obj.size);  
  if (size == 6){
  std::cout << Mass[5]->getTitle() << endl;
  std::cout << obj.Mass[5]->getTitle() << endl;
    }
  for (int i = 0; i < size && flag; i++) {
    flag = flag && (Mass[i]->getType() == obj.Mass[i]->getType());
    flag = flag && (Mass[i]->getTitle() == obj.Mass[i]->getTitle());
    flag = flag && (Mass[i]->getAutor() == obj.Mass[i]->getAutor());
    flag = flag && (Mass[i]->getMoodSadHappy() == obj.Mass[i]->getMoodSadHappy());
    flag = flag &&
           (Mass[i]->getMoodCalmIntense() == obj.Mass[i]->getMoodCalmIntense());
    
    if (Mass[i]->getType() == "popurry" && obj.Mass[i]->getType() == "popurry"){
    flag = flag && (Mass[i]->getMoodSadHappyEnd() == obj.Mass[i]->getMoodSadHappyEnd());
    flag = flag &&
           (Mass[i]->getMoodCalmIntenseEnd() == obj.Mass[i]->getMoodCalmIntenseEnd());  
      }
  }
  return flag;
}