#ifndef popurry_h
#define popurry_h

#include "Composition.h"

class Popurry: public Composition
{
public:
    Popurry();
    Popurry(string titleIn, string autorIn, int moodSHIn, int moodCIIn,
            int moodSHInEnd, int moodCIInEnd);
    Popurry(const Popurry& obj);
    ~Popurry();

    bool setMoodSadHappyEnd(int moodSHInEnd);
    bool setMoodCalmIntenseEnd(int moodCIInEnd);
    int getMoodSadHappyEnd() const;
    int getMoodCalmIntenseEnd() const;

    Popurry& operator=(const Popurry &obj);
    string getType() const;

private:
  int moodSHEnd;
  int moodCIEnd;
};

#endif