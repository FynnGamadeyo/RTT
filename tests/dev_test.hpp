/***************************************************************************
  tag: Peter Soetens  Mon Jan 10 15:59:18 CET 2005  logger_test.hpp

                        dev_test.hpp -  description
                           -------------------
    begin                : Mon January 10 2005
    copyright            : (C) 2005 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef DEVTEST_H
#define DEVTEST_H

class DevTest
{
public:
	DevTest(){ setUp(); };
	~DevTest(){ tearDown(); };
    void setUp();
    void tearDown();

    void testClasses();
    void testNaming();
};

#endif
