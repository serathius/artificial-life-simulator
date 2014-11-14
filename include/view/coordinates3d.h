
#ifndef COORDINATES3D_H_
#define COORDINATES3D_H_

namespace view
{
    class Vector;

    class Coordinates
    {
    public:
        float x;
        float y;
        float z;
        Coordinates();
        Coordinates(float, float, float);

        view::Coordinates operator+(const view::Vector&) const;
        view::Vector operator-(const view::Coordinates&) const;
        bool operator==(const view::Coordinates&) const;

    };

    class Vector
    {
    public:
        float x;
        float y;
        float z;

        Vector();
        Vector(float, float, float);

        const float length();
        void normalize ();

        const view::Vector operator * (const float);

    };

}


#endif /* COORDINATES3D_H_ */
