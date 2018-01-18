from __future__ import print_function
import sys

import click
import eccodes


@click.command()
@click.argument('file_path')
def cli(file_path):
    with open(file_path, 'rb') as f:
        handle = eccodes.codes_grib_new_from_file(f, headers_only=False)
        if handle is None:
            print("ERROR: unable to create handle from file " + file_path)
            sys.exit(-1)

        eccodes.codes_release(handle)


if __name__ == "__main__":
    cli()
