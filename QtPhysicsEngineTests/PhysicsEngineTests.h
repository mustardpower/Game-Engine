#pragma once

#include <QtTest\qtest.h>

class PhysicsEngineTests : public QObject
{
	Q_OBJECT
	private slots:
	void initTestCase();
	void testXMLRead();
	void testXMLReadFailure();
	void testXMLRoundTrip();
	void testRayCollision();
	void testAABBCollision();
	void testLinePlaneCollision();
	void testUnitConversion();
	void cleanupTestCase();
};
