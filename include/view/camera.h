
#ifndef CAMERA_H_
#define CAMERA_H_

namespace view
{

    class Coordinates
    {
    public:
        float x;
        float y;
        float z;
        Coordinates();
        Coordinates(float, float, float);

    };


}
view::Coordinates get_orthogonal(float x, float y, float z);


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
