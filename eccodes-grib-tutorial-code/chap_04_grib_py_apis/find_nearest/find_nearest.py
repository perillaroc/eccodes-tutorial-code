from __future__ import print_function

import click
import eccodes


@click.command()
@click.argument('file_path')
def cli(file_path):
    with open(file_path, 'rb') as f:
        handle = eccodes.codes_grib_new_from_file(f, headers_only=False)
        while handle is not None:
            date = eccodes.codes_get(handle, "dataDate")
            type_of_level = eccodes.codes_get(handle, "typeOfLevel")
            level = eccodes.codes_get(handle, "level")

            points = eccodes.codes_grib_find_nearest(handle, 39.92, 116.46, False, 1)
            point = points[0]

            print(date, type_of_level, level, " :", point.lat, point.lon, point.value, point.distance)

            eccodes.codes_release(handle)
            handle = eccodes.codes_grib_new_from_file(f, headers_only=False)


if __name__ == "__main__":
    cli()
