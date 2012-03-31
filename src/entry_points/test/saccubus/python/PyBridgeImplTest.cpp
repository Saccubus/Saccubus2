/*
 * PyBridgeImplTest.cpp
 *
 *  Created on: 2012/03/31
 *      Author: psi
 */

#include "../../TestCommon.h"
#include "../../../../saccubus/python/PyBridgeImpl.h"
#include "../../../../saccubus/python/ScriptException.h"
using namespace saccubus::python;

class PyBridgeImplTest : public ::testing::Test{
protected:
	PyBridgeImpl* bridge;
public:
	void SetUp(){
		bridge = new PyBridgeImpl(log_err);
	}
	void TearDown(){
		delete bridge;
	}
};

TEST_F(PyBridgeImplTest, InvalidFileTest)
{
	std::auto_ptr<Session> session = this->bridge->createSession();
	bool caught = false;
	try {
		session->loadFile("not_exists");
	}catch(ScriptException& exc){
		caught |= true;
	} catch (...){
		GTEST_FATAL_FAILURE_("Unknwon exception caught!");
	}
	ASSERT_TRUE(caught);
}

TEST_F(PyBridgeImplTest, EvalTest)
{
	std::auto_ptr<Session> session = this->bridge->createSession();
	session->loadFile(MATERIAL_DIR"test.py");
	session->executeMethod("os.path", "join", std::map<std::string, std::string>());
}




