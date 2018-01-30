from contextlib import contextmanager
from pathlib import Path
from re import compile as re_compile

# TODO refactor to make sure a header's set of declarations appear after its included dependencies...

'''
#include "foo.h"   => match.group(1) == "foo.h"
'''
find_local_include = re_compile(r"#include \"(.*)\"")

'''
#include <vector> => match.group(1) == "vector"
'''
find_global_include = re_compile(r"#include <(.*)>")


@contextmanager
def master_header(version_path, filename):
    local_headers = dict()
    global_headers = set()
    headers_path = version_path/'headers'
    yield (headers_path, local_headers, global_headers)
    with open(version_path/filename, 'w') as header_file:
        for header in global_headers:
            header_file.write(f"#include <{header}>\n")
        for declaration in local_headers.values():
            header_file.write(declaration)


def include(master_header, local_header):
    headers_path, local_headers, global_headers = master_header
    if local_header not in local_headers:
        local_dependencies = []
        with open(local_header) as local_header_file:
            all_code_minus_includes = ""
            for line in local_header_file:
                if line.startswith("#include"):
                    match = find_local_include.match(line)
                    if match:
                        header = match.group(1)
                        header_path = headers_path/header
                        local_dependencies.append(header_path)
                        if header_path not in local_headers:
                            include(master_header, header_path)
                    else:
                        match = find_global_include.match(line)
                        if match:
                            header = match.group(1)
                            if header not in global_headers:
                                global_headers.add(header)
                else:
                    all_code_minus_includes += line
        # TODO do something with local dependencies to insure proper ordering of inclusion of declarations
        local_headers[local_header] = all_code_minus_includes


def viper_h(version_dir):
    version_path = Path(version_dir)
    headers_path = version_path/'headers'
    with master_header(version_path, "viper.h") as viper_h:
        for header in headers_path.glob('*.h'):
            include(viper_h, header)


if __name__ == "__main__":
    viper_h("14")
    viper_h("17")


