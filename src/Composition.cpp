#include "Composition.h"

Composition::Composition() {
  title = "No Info";
  autor = "No Info";
  moodSH = 1;
  moodCI = 1;
}

Composition::Composition(string titleIn, string autorIn, int moodSHIn,
                         int moodCIIn) {
  title = titleIn;
  autor = autorIn;
  moodSH = moodSHIn;
  if (moodSH < 1 || moodSH > 10)
    moodSH = 1;
  moodCI = moodCIIn;
  if (moodCI < 1 || moodCI > 10)
    moodCI = 1;
}

Composition::Composition(const Composition &obj) {
  title = obj.title;
  autor = obj.autor;
  moodSH = obj.moodSH;
  moodCI = obj.moodCI;
}

Composition::~Composition() {
  title.clear();
  autor.clear();
}

void Composition::setTitle(string titleIn) { title = titleIn; }

void Composition::setAutor(string autorIn) { autor = autorIn; }

bool Composition::setMoodSadHappy(int moodSHIn) {
  if (moodSHIn < 1 || moodSHIn > 10)
    return false;
  else {
    moodSH = moodSHIn;
    return true;
  }
}

bool Composition::setMoodCalmIntense(int moodCIIn) {
  if (moodCIIn < 1 || moodCIIn > 10)
    return false;
  else {
    moodCI = moodCIIn;
    return true;
  }
}

string Composition::getTitle() const { return title; }

string Composition::getAutor() const { return autor; }

int Composition::getMoodSadHappy() const { return moodSH; }

int Composition::getMoodCalmIntense() const { return moodCI; }

Composition& Composition::operator=(const Composition &obj){
  title = obj.getTitle();
  autor = obj.getAutor();
  moodSH = obj.getMoodSadHappy();
  moodCI = obj.getMoodCalmIntense();

  return *this;
}

string Composition::getType() const{
  return "composition";
}

bool Composition::setMoodSadHappyEnd(int moodSHIn) {
  if (moodSHIn < 1 || moodSHIn > 10)
    return false;
  else {
    moodSH = moodSHIn;
    return true;
  }
}

bool Composition::setMoodCalmIntenseEnd(int moodCIIn) {
  if (moodCIIn < 1 || moodCIIn > 10)
    return false;
  else {
    moodCI = moodCIIn;
    return true;
  }
}

int Composition::getMoodSadHappyEnd() const { return moodSH; }

int Composition::getMoodCalmIntenseEnd() const { return moodCI; }