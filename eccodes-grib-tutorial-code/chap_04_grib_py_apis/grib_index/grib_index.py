from __future__ import print_function

import click
import eccodes


@click.command()
@click.argument('file_path')
def cli(file_path):
    index_id = eccodes.codes_index_new_from_file(str(file_path), ["paramId"])

    eccodes.codes_index_add_file(index_id, str(file_path))

    param_size = eccodes.codes_index_get_size(index_id, "paramId")
    print("param id count:", param_size)

    param_id_list = eccodes.codes_index_get(index_id, "paramId")
    print("param id list:", param_id_list)

    eccodes.codes_index_select(index_id, "paramId", '131')

    handle = eccodes.codes_new_from_index(index_id)
    while handle is not None:
        short_name = eccodes.codes_get(handle, "shortName")
        date = eccodes.codes_get(handle, "dataDate")
        type_of_level = eccodes.codes_get(handle, "typeOfLevel")
        level = eccodes.codes_get(handle, "level")

        print(short_name, date, type_of_level, level)
        eccodes.codes_release(handle)
        handle = eccodes.codes_new_from_index(index_id)


if __name__ == "__main__":
    cli()