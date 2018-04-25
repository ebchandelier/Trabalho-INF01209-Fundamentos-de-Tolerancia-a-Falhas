import os
from collections import namedtuple
import sys


def parse_errors(program_logs_folder_path, output_csv_file_path):
    sdcs_folder_path = program_logs_folder_path + "/sdcs/"

    # List with sub. dirs. of different dates.
    sub_dirs = next(os.walk(sdcs_folder_path))[1]

    SDC = namedtuple('SDC', 'name filename line_number value')

    # Key is the line number, content is a list of SDCs.
    sdcs_dict = {}

    # Parsing.
    for sub_dir in sub_dirs:  # For each sub. dir:
        # Get all log folders.
        path = sdcs_folder_path + sub_dir + "/"
        log_dirs = next(os.walk(path))[1]
        for log_dir in log_dirs:  # For each log folder.
            # Opens the log file.
            files = os.listdir(path + log_dir)
            file_name = [name for name in files
                         if name.startswith("carolfi-flipvalue")][0]
            file_path = path + log_dir + "/" + file_name
            with open(file_path, 'r') as log_file:
                lines = log_file.readlines()

                # Finds section with symbol information.
                i = 0
                while(not lines[i].startswith("symbol name")):
                    i += 1

                # Reads the values.
                name = lines[i][13:len(lines[i]) - 1]
                filename = lines[i + 1][17:len(lines[i + 1]) - 1]
                line_number = lines[i + 2][13:len(lines[i + 2]) - 1]
                value = lines[i + 3][7:len(lines[i + 3]) - 1]

                if(line_number not in sdcs_dict):  # First insertion.
                    sdcs_dict[line_number] = []
                # Adds to the list.
                sdcs_dict[line_number].append(
                    SDC(name, filename, line_number, value))

    # Writes SDCs informations in a file.
    with open(output_csv_file_path, 'w') as out_file:
        out_file.write('name,filename,line_number,SDCs_count\n')
        for line_number, sdcs_list in sdcs_dict.items():
            sdc = sdcs_list[0]
            n_sdcs = len(sdcs_list)
            out_file.write(sdc.name + "," + sdc.filename + "," +
                           sdc.line_number + "," + str(n_sdcs) + "\n")


def main():
    if(len(sys.argv) != 3):
        raise Exception(
            str("\n\nInvalid arguments: expected 2, received " +
                str(len(sys.argv) - 1) + "\n\n" +
                "Arg. 1: path of the folder containing the folders hangs, "
                "masked and sdcs.\n" +
                "Arg. 2: output csv file name\n\n"))

    parse_errors(sys.argv[1], sys.argv[2])


if __name__ == "__main__":
    main()
