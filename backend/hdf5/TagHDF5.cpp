// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include "TagHDF5.hpp"
#include <nix/util/util.hpp>
#include "DataArrayHDF5.hpp"
#include "BlockHDF5.hpp"
#include "FeatureHDF5.hpp"

using namespace nix::base;

namespace nix {
namespace hdf5 {


TagHDF5::TagHDF5(const std::shared_ptr<IFile> &file, const std::shared_ptr<IBlock> &block, const H5Group &group)
    : BaseTagHDF5(file, block, group)
{
}


TagHDF5::TagHDF5(const std::shared_ptr<IFile> &file, const std::shared_ptr<IBlock> &block, const H5Group &group,
                 const std::string &id, const std::string &type, const std::string &name,
                 const std::vector<double> &position)
    : TagHDF5(file, block, group, id, type, name, position, util::getTime())
{
}


TagHDF5::TagHDF5(const std::shared_ptr<IFile> &file, const std::shared_ptr<IBlock> &block, const H5Group &group,
                 const std::string &id, const std::string &type, const std::string &name,
                 const std::vector<double> &position, const time_t time)
    : BaseTagHDF5(file, block, group, id, type, name, time)
{
    this->position(position);
}


std::vector<std::string> TagHDF5::units() const {
    std::vector<std::string> units;
    group().getData("units", units);
    return units;
}


void TagHDF5::units(const std::vector<std::string> &units) {
    group().setData("units", units);
    forceUpdatedAt();
}


void TagHDF5::units(const none_t t) {
    if (group().hasData("units")) {
        group().removeData("units");
    }
    forceUpdatedAt();
}


std::vector<double> TagHDF5::position() const {
    std::vector<double> position;

    if (group().hasData("position")) {
        group().getData("position", position);
    }

    return position;
}


void TagHDF5::position(const std::vector<double> &position) {
    group().setData("position", position);
}


std::vector<double> TagHDF5::extent() const {
    std::vector<double> extent;
    group().getData("extent", extent);
    return extent;
}


void TagHDF5::extent(const std::vector<double> &extent) {
    group().setData("extent", extent);
}


void TagHDF5::extent(const none_t t) {
    if (group().hasData("extent")) {
        group().removeData("extent");
    }
    forceUpdatedAt();
}


// Other methods and functions


TagHDF5::~TagHDF5()
{
}

} // ns nix::hdf5
} // ns nix