
#include <memory>
#include <functional>

void update(const AbsoluteTime&)
{

}


OrganismBody::OrganismBody ( std::function fun) : draw(fun)
{

}
