/*
 * camera.h
 *
 *  Created on: 12 lis 2014
 *      Author: matfil
 */

#ifndef CAMERA_H_
#define CAMERA_H_

namespace view
{

    struct Coordinates
    {
        float x;
        float y;
        float z;

    };


}
view::Coordinates get_orthagonal(float x, float y, float z);


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
    void move(float,float,float);
    void set_depth(float);
    void set_perspective(float,float,float);
    void set_position(float,float,float);
    void set_target(float,float,float);
    void set_zoom(float);
};



#endif /* CAMERA_H_ */
