from __future__ import print_function
import click
import eccodes


@click.command()
@click.argument('output_file_path')
def cli(output_file_path):
    handle = eccodes.codes_grib_new_from_samples('regular_ll_pl_grib2')

    value_size = eccodes.codes_get_size(handle, 'values')
    values = []
    for i in range(0, value_size):
        values.append(i)
    eccodes.codes_set_values(handle, values)

    with open(output_file_path, 'wb') as output_file:
        eccodes.codes_write(handle, output_file)

    eccodes.codes_release(handle)


if __name__ == "__main__":
    cli()
