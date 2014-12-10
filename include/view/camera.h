
#ifndef CAMERA_H_
#define CAMERA_H_

#include "view/coordinates3d.h"

view::Vector get_orthogonal(const view::Vector&);


class Camera
{
private:
    view::Coordinates position;
    view::Coordinates target;
    float near, far;
    float width, height;
    void look();

public:
    Camera();
    void move(view::Vector&);
    void move_to(view::Coordinates);
    void set_depth(float);
    void set_perspective(float, float, float);
    void set_position(view::Coordinates);
    void set_target(view::Coordinates);
    void set_zoom(float);
};



#endif /* CAMERA_H_ */
