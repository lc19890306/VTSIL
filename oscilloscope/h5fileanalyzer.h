#ifndef H5FILEANALYZER_H
#define H5FILEANALYZER_H

#include "H5Cpp.h"

#include <QStringList>
#include <iostream>
#include <string>

#ifndef H5_NO_NAMESPACE
using namespace H5;
#ifndef H5_NO_STD
using std::cout;
using std::endl;
#endif  // H5_NO_STD
#endif

class H5FileAnalyzer
{
public:
    H5FileAnalyzer(const int &, const QStringList &);

    virtual ~H5FileAnalyzer();

    void clean();

    double *getPoints() const
    {
        return points;
    }

    int getDim() const
    {
        return dim;
    }

private:
    double *points;
    int dim;
    bool clean_flag;
};

#endif // H5FILEANALYZER_H
