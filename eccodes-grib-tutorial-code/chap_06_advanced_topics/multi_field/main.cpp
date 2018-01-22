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

    const char* sample_filename = "regular_ll_pl_grib2";
    int err = 0;
    codes_handle *h = codes_grib_handle_new_from_samples(nullptr,  sample_filename);
    if(h == nullptr)
    {
        cout<<"ERROR: unable to create handle from file "<<file_path<<endl;
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
    // codes_set_long(h, "bitsPerValue", 16);
    codes_set_double_array(h, "values", values, value_size);


    codes_multi_handle* multi_handle = codes_grib_multi_handle_new(nullptr);

    const int start_section = 4;

    for (int step = 12; step <= 120; step += 12)
    {
        codes_set_long(h, "step", step);

        codes_grib_multi_handle_append(h, start_section, multi_handle);
    }


    FILE* output_file=fopen(file_path, "wb");
    if(!output_file)
    {
        cerr<<"ERROR: unable to open output file " << file_path <<endl;
        exit(1);
    }


    codes_grib_multi_handle_write(multi_handle, output_file);
    fclose(output_file);

    delete [] values;
    codes_handle_delete(h);
    codes_grib_multi_handle_delete(multi_handle);

    return 0;
}
