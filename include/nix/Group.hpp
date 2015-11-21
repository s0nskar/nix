// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#ifndef NIX_GROUP_HPP
#define NIX_GROUP_HPP

#include <nix/base/EntityWithSources.hpp>
#include <nix/base/IGroup.hpp>
#include <nix/DataArray.hpp>
#include <nix/Platform.hpp>


namespace nix {

class NIXAPI Group : public base::EntityWithSources<base::IGroup> {

public:

    /**
     * @brief Constructor that creates an uninitialized Group.
     *
     * Calling any method on an uninitialized group will throw a {@link nix::UninitializedEntity}
     * exception. The following code illustrates how to check if a group is initialized:
     *
     * ~~~
     * Group g = ...;
     * if (g) {
     *     // g is initialised
     * } else {
     *     // g is uninitialized
     * }
     * ~~~
     */
    Group()
        : EntityWithSources() { }

    /**
     * @brief Copy constructor.
     *
     * Copying of all NIX front facing objects like Group is a rather cheap operation.
     * Semantically this is equivalent to the creation of another reference to the original
     * object.
     *
     * @param other     The group to copy.
     */
    Group(const Group &other)
        : EntityWithSources(other.impl()) {
    }

    /**
     * @brief Constructor that creates a new group from a shared pointer to
     * an implementation instance.
     *
     * This constructor should only be used in the back-end.
     */
    Group(const std::shared_ptr<base::IGroup> &p_impl)
        : EntityWithSources(p_impl) {
    }

    /**
     * @brief Constructor with move semantics that creates a new group from a shared pointer to
     * an implementation instance.
     *
     * This constructor should only be used in the back-end.
     */
    Group(std::shared_ptr<base::IGroup> &&ptr)
        : EntityWithSources(std::move(ptr)) {
    }

    //--------------------------------------------------
    // Methods concerning references.
    //--------------------------------------------------
    // TODO syntactic sugar for creating dataArrays, tags, multiTags
    /**
     * @brief Checks whether a DataArray is referenced by the group.
     *
     * @param id        The id of the DataArray to check.
     *
     * @return True if the data array is referenced, false otherwise.
     */
    bool hasDataArray(const std::string &id) const {
        return backend()->hasDataArray(id);
    }

    /**
     * @brief Checks whether a DataArray is referenced by the group.
     *
     * @param data_array The DataArray to check.
     *
     * @return True if the data array is referenced, false otherwise.
     */
    bool hasDataArray(const DataArray &data_array) const;

    /**
     * @brief Gets the number of referenced DataArray entities of the tag.
     *
     * @return The number of referenced data arrays.
     */
    ndsize_t dataArrayCount() const {
        return backend()->dataArrayCount();
    }

    /**
     * @brief Gets a specific referenced DataArray from the tag.
     *
     * @param id        The id of the referenced DataArray.
     *
     * @return The referenced data array.
     */
    DataArray getDataArray(const std::string &id) const {
        return backend()->getDataArray(id);
    }

    /**
     * @brief Gets a referenced DataArray by its index.
     *
     * @param index     The index of the DataArray.
     *
     * @return The referenced data array.
     */
    DataArray getDataArray(size_t index) const;

    /**
     * @brief Add a DataArray to the list of referenced data of the group.
     *
     * @param data_array The DataArray to add.
     */
    void addDataArray(const DataArray &data_array);

    /**
     * @brief Add a DataArray to the list of referenced data of the group.
     *
     * @param id        The id of the DataArray to add.
     */
    void addDataArray(const std::string &id);

    /**
     * @brief Remove a DataArray from the list of referenced data of the group.
     *
     * This method just removes the association between the data array and the
     * tag, the data array itself will not be removed from the file.
     *
     * @param data_array The DataArray to remove.
     *
     * @returns True if the DataArray was removed, false otherwise.
     */
    bool removeDataArray(const DataArray &data_array);

    /**
     * @brief Remove a DataArray from the list of referenced data of the group.
     *
     * This method just removes the association between the data array and the
     * tag, the data array itself will not be removed from the file.
     *
     * @param id        The id of the DataArray to remove.
     *
     * @returns True if the DataArray was removed, false otherwise.
     */
    bool removeDataArray(const std::string &id) {
        return backend()->removeDataArray(id);
    }

    /**
     * @brief Get referenced data arrays associated with this group.
     *
     * The parameter filter can be used to filter data arrays by various
     * criteria.
     *
     * @param filter    A filter function.
     *
     * @return A vector containing the matching data arrays.
     */
    std::vector<DataArray> dataArrays(const util::Filter<DataArray>::type &filter) const;

    /**
     * @brief Get all referenced data arrays associated with this group.
     *
     * Always uses filter that accepts all dataArrays.
     *
     * @return The filtered DataArrays as a vector
     */
    std::vector<DataArray> dataArrays() const
    {
        return dataArrays(util::AcceptAll<DataArray>());
    }

    /**
     * @brief Sets all referenced DataArray entities.
     *
     * Previously referenced data arrays, that are not in the references vector
     * will be removed.
     *
     * @param data_arrays    All referenced arrays.
     */
    void dataArrays(const std::vector<DataArray> &data_arrays) {
        backend()->dataArrays(data_arrays);
    }

    /**
     * @brief Assignment operator for none.
     */
    Group &operator=(const none_t &t) {
        ImplContainer::operator=(t);
        return *this;
    }

    /**
     * @brief Output operator
     */
    NIXAPI friend std::ostream &operator<<(std::ostream &out, const Group &ent);
};

} // namespace nix

#endif //NIX_GROUP_HPP
