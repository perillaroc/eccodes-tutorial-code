#include <iostream>

#include <eccodes.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout<<"Usage: "<<argv[0]<<" grib1_path grib2_path";
        return 1;
    }

    const char* grib1_path = argv[1];
    const char* grib2_path = argv[2];

    const char* sample_filename = "regular_ll_pl_grib2";
    int err = 0;
    codes_handle *h = codes_grib_handle_new_from_samples(nullptr,  sample_filename);
    if(h == nullptr)
    {
        cout<<"ERROR: unable to create handle from sample "<<sample_filename<<endl;
        return 1;
    }

    size_t short_name_size;
    codes_get_size(h, "shortName", &short_name_size);

    codes_set_string(h, "shortName", "10u", &short_name_size);

    size_t value_size;
    codes_get_size(h, "values", &value_size);

    auto values = new double[value_size];
    double v = 0;
    for(auto i=0; i<value_size; i++)
    {
        values[i] = v;
        v++;
    }
    // codes_set_long(h, "bitsPerValue", 16);
    codes_set_double_array(h, "values", values, value_size);

    codes_write_message(h, grib2_path, "wb");

    codes_set_long(h, "edition", 1);

    codes_write_message(h, grib1_path, "wb");

    delete [] values;
    codes_handle_delete(h);

    return 0;
}
