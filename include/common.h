#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>

struct None { };

template <typename First,typename Second>
struct Pair {
  First first;
  Second second;
};

template <typename List>
struct LogData
{
  List list;
};

template <typename Begin,typename Value>
LogData<Pair<Begin,const Value &>>
operator<<(LogData<Begin> begin,const Value &value)
{
    return {{begin.list,value}};
}

template <typename Begin,size_t n>
LogData<Pair<Begin,const char *>>
operator<<(LogData<Begin> begin,const char (&value)[n])
{
    return {{begin.list,value}};
}

inline void printList(std::ostream &os, None)
{

}

template <typename Begin,typename Last>
void printList(std::ostream &os,const Pair<Begin,Last> &data)
{
  printList(os,data.first);
  os << data.second;
}

template <typename List>
void log(const char *file,int line,const LogData<List> &data)
{
  std::cout << file << " (" << line << "): ";
  printList(std::cout,data.list);
  std::cout << std::endl;
}

#ifndef NDEBUG
  #define LOG(x) (log(__FILE__,__LINE__,LogData<None>() << x))
#else
  #define LOG(x)
#endif

#endif /* COMMON_H_ */
