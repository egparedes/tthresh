// cppimport

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

//#include "../src/tthresh.hpp"
#include "../src/compress.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

bool py_compress()
{
    // data = compress(d, input_file, compressed_file, io_type, target, target_value, skip_bytes, verbose_flag, debug_flag);
    return true;
}
 
std::vector<std::uint64_t> py_encode_array(py::buffer b, double sse, bool verbose)
{
    py::buffer_info b_info = b.request();
    
    dimensions d;
    std::copy(std::begin(b_info.shape), std::end(b_info.shape), std::back_inserter(d.s));
    std::reverse(std::begin(d.s), std::end(d.s));

    core_struct core_info{true, -1., 0};
    size_t size = std::accumulate(d.s.begin(), d.s.end(), 1, [](int a, int b)
                                  { return a * b; });
    double *c = (double *)b_info.ptr;
    py::print(d.s[0], d.s[1], d.s[2]);
    std::vector<uint64_t> result = encode_array(d, c, size, sse, core_info, verbose);

    return result;
}

PYBIND11_MODULE(pytthresh, m)
{
    // m.def("square", &square);
    m.def("compress", &py_compress, "compress docstring");
    m.def("encode_array", &py_encode_array, "encode docstring");
}

/*
<%
import pybind11

setup_pybind11(cfg)


cfg["include_dirs"] = [pybind11.get_include(), pybind11.get_include(True), "../external"]
#cfg['sources'] = ['../external/compress.hpp']

# cfg['dependencies'] = ['file1.h', 'file2.h']
# cfg['extra_link_args'] = ['...']
# cfg['extra_compile_args'] = ['...']
# cfg['libraries'] = ['...']

%>
*/
