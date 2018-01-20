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
    codes_handle *h = codes_handle_new_from_file(0, in, PRODUCT_GRIB, &err);
    if(h == nullptr)
    {
        cout<<"ERROR: unable to create handle from file "<<file_path<<endl;
        return 1;
    }

    codes_handle_delete(h);
    fclose(in);

    return 0;
}