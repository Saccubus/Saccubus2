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
	std::auto_ptr<Session> session;
public:
	void SetUp(){
		bridge = new PyBridgeImpl(log_err);
		session = this->bridge->createSession();
	}
	void TearDown(){
		delete bridge;
	}
};

TEST_F(PyBridgeImplTest, InvalidFileTest)
{
	ASSERT_THROW(session->loadFile("not_exists"), ScriptException); //そんなのない
	ASSERT_THROW(session->loadFile(MATERIAL_DIR"test_failure.py"), ScriptException); //文法がおかしい
}

TEST_F(PyBridgeImplTest, DictTest)
{
	session->loadFile(MATERIAL_DIR"test.py");
	std::map<std::string, std::string> map;
	map["first"] = "1";
	map["second"] = "2";
	std::map<std::string, std::string> result = session->executeMethodDict("test_succeed_dict", map);
	ASSERT_EQ(std::string("3"), result["result"]);
}

TEST_F(PyBridgeImplTest, BoolTest)
{
	session->loadFile(MATERIAL_DIR"test.py");
	std::map<std::string, std::string> map;
	map["two_plus_two"] = "4";
	map["five"] = "5";
	ASSERT_FALSE(session->executeMethodBool("test_not_equal", map));
}

TEST_F(PyBridgeImplTest, FailTest)
{
	session->loadFile(MATERIAL_DIR"test.py");
	ASSERT_THROW(session->executeMethodDict("test_run_fail", std::map<std::string, std::string>()), ScriptException);
}




