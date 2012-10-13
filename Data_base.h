#ifndef DATA_BASE
#define DATA_BASE

#include <vector>

#include "Position.h"


class CData_base
{
public:
  std::vector<CPosition> data;

  void add_position(CPosition & pos);
  void save() const;
  void load();
  
};

std::vector<CPosition>::iterator in_base(CPosition & position, CData_base & base);

#endif //DATA_BASE
