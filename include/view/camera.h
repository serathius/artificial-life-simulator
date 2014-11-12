/*
 * camera.h
 *
 *  Created on: 12 lis 2014
 *      Author: matfil
 */

#ifndef CAMERA_H_
#define CAMERA_H_



class Camera
{
private:
    struct Coordinates
        {
            float x;
            float y;
            float z;
        };
    Coordinates position;
    Coordinates target;
    void look();

public:
    void move(float,float,float);
    void set_position(float,float,float);
    void set_target(float,float,float);

};



#endif /* CAMERA_H_ */
