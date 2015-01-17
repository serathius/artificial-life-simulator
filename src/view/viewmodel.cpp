#include "view/viewmodel.h"

void ViewModel::draw()
{
  for (auto object: objects_)
  {
    object->draw();
  }
}

ViewModel::ViewModel(const std::vector<WorldObject *> &objects)
{
  objects_ = objects;
}
