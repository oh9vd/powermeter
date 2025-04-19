#include "model.h"
class Info
{
  const Model &m;

public:
  Info(const Model &model) : m(model) {}
  void init() {};
  void loop() {};
};