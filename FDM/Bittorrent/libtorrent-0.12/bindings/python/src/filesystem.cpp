/*
  Free Download Manager Copyright (c) 2003-2007 FreeDownloadManager.ORG
*/

  

   

#include <boost/python.hpp>
#include <boost/filesystem/path.hpp>

using namespace boost::python;

struct path_to_python
{
    static PyObject* convert(boost::filesystem::path const& p)
    {
        return incref(object(p.string()).ptr());
    }
};

struct path_from_python
{
    path_from_python()
    {
        converter::registry::push_back(
            &convertible, &construct, type_id<boost::filesystem::path>()
        );
    }

    static void* convertible(PyObject* x)
    {
        return PyString_Check(x) ? x : 0;
    }

    static void construct(PyObject* x, converter::rvalue_from_python_stage1_data* data)
    {
        void* storage = ((converter::rvalue_from_python_storage<
            boost::filesystem::path
        >*)data)->storage.bytes;
        new (storage) boost::filesystem::path(PyString_AsString(x));
        data->convertible = storage;
    }
};

void bind_filesystem()
{
    to_python_converter<boost::filesystem::path, path_to_python>();
    path_from_python();

    boost::filesystem::path::default_name_check(boost::filesystem::native);
}

