#pragma once
#include "QtTest\qtest.h"

class PhysicsEngineTest : public QObject
{
	Q_OBJECT
	private slots:
	void initTestCase();
	void testXMLRead();
	void testXMLReadFailure();
	void testRayCollision();
	void testAABBCollision();
};

QTEST_MAIN(PhysicsEngineTest)