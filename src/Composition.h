#ifndef _composition_h
#define _composition_h

#include <string>

using namespace std;

class Composition {
public:
  Composition();
  Composition(string titleIn, string autorIn, int moodSHIn, int moodCIIn);
  Composition(const Composition &obj);
  virtual ~Composition();
  void setTitle(string titleIn);
  void setAutor(string autorIn);
  bool setMoodSadHappy(int moodSHIn);
  bool setMoodCalmIntense(int moodCIIn);
  string getTitle() const;
  string getAutor() const;
  int getMoodSadHappy() const;
  int getMoodCalmIntense() const;
  Composition& operator=(const Composition &obj);

  virtual string getType() const;

  virtual bool setMoodSadHappyEnd(int moodSHIn);
  virtual bool setMoodCalmIntenseEnd(int moodCIIn);
  virtual int getMoodSadHappyEnd() const;
  virtual int getMoodCalmIntenseEnd() const;

private:
  string title;
  string autor;
  int moodSH; // (Sad - Happy) denoted by numbers from 1 to 10 where 1 is Sad
              // and 10 is Happy
  int moodCI; // (Calm - Intense) denoted by numbers from 1 to 10 where 1 is
              // Calm and 10 is Intense
};

#endif