
#include <nix/hdf5/Attribute.hpp>
#include <nix/hdf5/ExceptionHDF5.hpp>
#include <H5Ipublic.h>

namespace nix {
namespace hdf5 {


Attribute::Attribute() : BaseHDF5() {
}

Attribute::Attribute(hid_t hid) : BaseHDF5(hid) {
}

Attribute::Attribute(const Attribute &other) : BaseHDF5(other) {
}


void Attribute::read(H5::DataType mem_type, const NDSize &size, void *data) {
    herr_t status = H5Aread(hid, mem_type.getId(), data);
    H5Error::check(status, "Attribute::read(): Could not read data");
}

void Attribute::read(H5::DataType mem_type, const NDSize &size, std::string *data) {
    StringWriter writer(size, data);
    read(mem_type, size, *writer);
    writer.finish();

    DataSpace space = getSpace();

    herr_t status = H5Dvlen_reclaim(mem_type.getId(), space.h5id(), H5P_DEFAULT, *writer);
    H5Error::check(status, "Attribute::read(): Could not reclaim variable length data");
}

void Attribute::write(H5::DataType mem_type, const NDSize &size, const void *data) {
    herr_t status = H5Awrite(hid, mem_type.getId(), data);
    H5Error::check(status, "Attribute::write(): Could not write data");
}

void Attribute::write(H5::DataType mem_type, const NDSize &size, const std::string *data) {
    StringReader reader(size, data);
    write(mem_type, size, *reader);
}


DataSpace Attribute::getSpace() const {

    hid_t space = H5Aget_space(hid);
    if (space < 0) {
        throw H5Exception("Attribute::getSpace(): Dould not get data space");
    }

    DataSpace ds(space);
    H5Idec_ref(space);

    return ds;
}

NDSize Attribute::extent() const {
    return getSpace().extent();
}

} //nix::hdf5::
} //nix::