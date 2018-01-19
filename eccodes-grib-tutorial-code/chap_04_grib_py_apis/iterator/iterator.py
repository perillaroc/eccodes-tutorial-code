from __future__ import print_function

import click
import eccodes


@click.command()
@click.argument('file_path')
def cli(file_path):
    with open(file_path, 'rb') as f:
        handle = eccodes.codes_grib_new_from_file(f, headers_only=False)
        date = eccodes.codes_get(handle, "dataDate")
        type_of_level = eccodes.codes_get(handle, "typeOfLevel")
        level = eccodes.codes_get(handle, "level")

        iter_id = eccodes.codes_grib_iterator_new(handle, 0)

        while 1:
            result = eccodes.codes_grib_iterator_next(iter_id)
            if not result:
                break

            [lat, lon, value] = result
            print(lat, lon, value)

        eccodes.codes_grib_iterator_delete(iter_id)
        eccodes.codes_release(handle)


if __name__ == "__main__":
    cli()
