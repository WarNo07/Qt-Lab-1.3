#ifndef _playlist_h
#define _playlist_h
#include "Composition.h"
#include "Popurry.h"
#include <vector>

using namespace std;

class Playlist {
public:
  Playlist();
  Playlist(int sizeIn);
  Playlist(const Playlist &obj);
  ~Playlist();

  void setComp(Composition &comp, int i);  
  void setComp(Popurry &comp, int i);
  void addComp(Composition &comp);
  void addComp(Popurry &comp);
  Composition* getComp(int i) const;
  int getSize() const;
  void delComp(int i);
  void delAll();
  Playlist getWay(int moodSHStart, int moodCIStart, int moodSHEnd,
                  int moodCIEnd) const;

  void fileInput(string file);
  void fileOutput(string file) const;
  bool isEqual(const Playlist &obj) const;

private:
  int size;
  void Step(int n, int n1, int moodSHEnd, int moodCIEnd, int i, int j) const;
  vector<Composition *> Mass;
};

#endif