// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

#include <pandora.hpp>

using namespace std;
using namespace pandora;

class TestRepresentation:public CPPUNIT_NS::TestFixture {
private:

    CPPUNIT_TEST_SUITE(TestRepresentation);

    CPPUNIT_TEST(testCreate);

    CPPUNIT_TEST_SUITE_END ();

    File *f1;

public:

    void setUp();
    void tearDown();
    void testCreate();

};