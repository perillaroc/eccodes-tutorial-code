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

    int err = 0;

    codes_index* index = nullptr;
    index = codes_index_new(nullptr, "paramId", &err);
    if (err)
    {
        cout<<"error: "<<codes_get_error_message(err)<<endl;
        exit(err);
    }

    err = codes_index_add_file(index, file_path);

    if (err)
    {
        cout<<"error: " << codes_get_error_message(err)<<endl;
        exit(err);
    }
    cout<<"end indexing..."<<endl;

    size_t param_id_size;
    codes_index_get_size(index,"paramId", &param_id_size);

    auto param_id_array= new long[param_id_size];
    codes_index_get_long(index, "paramId", param_id_array, &param_id_size);

    for(int i=0; i < param_id_size; i++)
    {
        auto param_id = param_id_array[i];
        codes_index_select_long(index, "paramId", param_id);

        codes_handle* h = nullptr;
        int count = 0;
        while ((h = codes_handle_new_from_index(index, &err)) != nullptr)
        {
            count++;
            if (err)
            {
                printf("error: %d\n",err);
                exit(err);
            }

            size_t short_name_length;
            codes_get_length(h, "shortName", &short_name_length);
            auto short_name = new char[short_name_length];
            codes_get_string(h, "shortName", short_name, &short_name_length);

            long level;
            codes_get_long(h,"level",&level);

            long number;
            codes_get_long(h,"number",&number);

            long step;
            codes_get_long(h,"step",&step);

            printf("shortName=%s ",short_name);
            printf("level=%ld ",level);
            printf("number=%ld ",number);
            printf("step=%ld \n",step);
            codes_handle_delete(h);
            delete [] short_name;
        }
    }

    codes_index_delete(index);

    return 0;
}