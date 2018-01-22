#include <iostream>

#include <eccodes.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout<<"Usage: "<<argv[0]<<" grib_file_path";
        return 1;
    }

    const char* file_path = argv[1];

    FILE* in = fopen(file_path, "rb");
    if(!in)
    {
        cout<<"ERROR: unable to open file "<<file_path<<endl;
        return 1;
    }

    int err = 0;
    codes_handle *h = nullptr;

    while((h=codes_handle_new_from_file(nullptr, in, PRODUCT_GRIB, &err)) != nullptr)
    {
        long data_date = -1;
        codes_get_long(h, "dataDate", &data_date);

        long type_of_level = -1;
        codes_get_long(h, "typeOfLevel", &type_of_level);

        long level = -1;
        codes_get_long(h, "level", &level);

        size_t size;
        codes_get_size(h, "values", &size);

        double *values = new double[size];
        codes_get_double_array(h, "values", values, &size);

        cout<<data_date<<" "<<type_of_level<<" "<<level<<" "<<size<<" "<<values[size-1]<<endl;

        delete [] values;
        codes_handle_delete(h);
    }

    fclose(in);

    return 0;
}