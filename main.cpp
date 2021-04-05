#include "PeriodicDatabase.h"

int main(int argc, char** argv)
{
    PeriodicDatabase pd("periodic_table.db");
    pd.createTable();
    
    if(argc == 6)
    {
        if(strcmp(argv[1], "-a") == 0)
        {
            int atomicNum = atoi(argv[2]);
            const char* symbol = argv[3];
            const char* name = argv[4];
            double weight = atof(argv[5]);

            pd.insertElement(atomicNum, symbol, name, weight);
        }
    }

    else if(argc == 3)
    {
        if(strcmp(argv[1], "-s") == 0)
        {
            int atomicNum = atoi(argv[2]);
            std::string* element = pd.getElement("PERIODIC", atomicNum);
            for(int i = 0; element[i] != "\0"; i++)
            {
                std::cout<<element[i]<<std::endl;
            }

            delete[] element;
        }
    }

    else
    {
        std::string* element = pd.getElement("PERIODIC", 1);
        for(int i = 0; element[i] != "\0"; i++)
        {
            std::cout<<element[i]<<std::endl;
        }

        delete[] element;
    }

    return 0;
}
