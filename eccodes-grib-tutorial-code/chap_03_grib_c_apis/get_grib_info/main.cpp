#include <iostream>

#include <grib_api.h>

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
    grib_handle *h = nullptr;

    while((h=grib_handle_new_from_file(nullptr, in, &err)) != nullptr)
    {
        long data_date = -1;
        grib_get_long(h, "dataDate", &data_date);

        long type_of_level = -1;
        grib_get_long(h, "typeOfLevel", &type_of_level);

        long level = -1;
        grib_get_long(h, "level", &level);

        size_t size;
        grib_get_size(h, "values", &size);

        double *values = new double[size];
        grib_get_double_array(h, "values", values, &size);

        cout<<data_date<<" "<<type_of_level<<" "<<level<<" "<<size<<" "<<values[size-1]<<endl;

        delete [] values;
        grib_handle_delete(h);
    }

    fclose(in);

    return 0;
}