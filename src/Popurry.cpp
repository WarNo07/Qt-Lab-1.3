#include "Popurry.h"

Popurry::Popurry() {
  this->setTitle("No Info");
  this->setAutor("No Info");
  this->setMoodSadHappy(1);
  this->setMoodCalmIntense(1);
  moodSHEnd = 1;
  moodCIEnd = 1;
}

Popurry::Popurry(string titleIn, string autorIn, int moodSHIn,
                         int moodCIIn, int moodSHInEnd, int moodCIInEnd) {
  this->setTitle(titleIn);
  this->setAutor(autorIn);
  if (!this->setMoodSadHappy(moodSHIn)) this->setMoodSadHappy(1);
  if (!this->setMoodCalmIntense(moodCIIn)) this->setMoodCalmIntense(1);
  moodSHEnd = moodSHInEnd;
  if (moodSHEnd < 1 || moodSHEnd > 10) moodSHEnd = 1;
  moodCIEnd = moodCIInEnd;
  if (moodCIEnd < 1 || moodCIEnd > 10) moodCIEnd = 1;
}

Popurry::Popurry(const Popurry &obj) {
  this->setTitle(obj.getTitle());
  this->setAutor(obj.getAutor());
  this->setMoodSadHappy(obj.getMoodSadHappy());
  this->setMoodCalmIntense(obj.getMoodCalmIntense());
  moodSHEnd = obj.moodSHEnd;
  moodCIEnd = obj.moodCIEnd;
}

Popurry::~Popurry() {
}

bool Popurry::setMoodSadHappyEnd(int moodSHInEnd) {
  if (moodSHInEnd < 1 || moodSHInEnd > 10)
    return false;
  else {
    moodSHEnd = moodSHInEnd;
    return true;
  }
}

bool Popurry::setMoodCalmIntenseEnd(int moodCIInEnd) {
  if (moodCIInEnd < 1 || moodCIInEnd > 10)
    return false;
  else {
    moodCIEnd = moodCIInEnd;
    return true;
  }
}

int Popurry::getMoodSadHappyEnd() const { return moodSHEnd; }

int Popurry::getMoodCalmIntenseEnd() const { return moodCIEnd; }

Popurry& Popurry::operator=(const Popurry &obj){
  this->setTitle(this->getTitle());
  this->setAutor(this->getAutor());
  this->setMoodSadHappy(this->getMoodSadHappy());
  this->setMoodCalmIntense(this->getMoodCalmIntense());
  moodSHEnd = obj.moodSHEnd;
  moodCIEnd = obj.moodCIEnd;
  return *this;
}

string Popurry::getType() const{
  return "popurry";
}