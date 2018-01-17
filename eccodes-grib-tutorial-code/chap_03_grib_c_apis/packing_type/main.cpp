#include <iostream>

#include <eccodes.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout<<"Usage: [command] simple_packing_file_path png_packing_file_path";
        return 1;
    }

    const char* simple_packing_file_path = argv[1];
    const char* png_packing_file_path = argv[2];

    const char* sample_filename = "reduced_gg_pl_grib2";

    int err = 0;
    codes_handle *h = codes_grib_handle_new_from_samples(nullptr,  sample_filename);
    if(h == nullptr)
    {
        cout<<"ERROR: unable to create handle from sample "<<sample_filename<<endl;
        return 1;
    }

    size_t value_size;
    codes_get_size(h, "values", &value_size);

    auto values = new double[value_size];
    double v = 0;
    for(auto i=0; i<value_size; i++)
    {
        values[i] = v;
        v++;
    }
    codes_set_double_array(h, "values", values, value_size);

    size_t packing_type_size;
    codes_get_size(h, "packingType", &packing_type_size);

    codes_set_string(h, "packingType", "grid_simple", &packing_type_size);
    codes_write_message(h, simple_packing_file_path, "wb");

    codes_set_string(h, "packingType", "grid_png", &packing_type_size);
    codes_write_message(h, png_packing_file_path, "wb");

    delete [] values;
    codes_handle_delete(h);

    return 0;
}
