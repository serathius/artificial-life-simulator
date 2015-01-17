#ifndef VIEWMODEL_H_
#define VIEWMODEL_H_

#include <vector>

#include "model/world.h"


class ViewModel
{
private:
   std::vector<WorldObject*> objects_;

public:
    ViewModel(){};
    ViewModel(const std::vector<WorldObject*>& objects);
    void draw();
};


#endif /* VIEWMODEL_H_ */
