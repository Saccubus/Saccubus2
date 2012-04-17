/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include "../../TestCommon.h"
#include "../../../../saccubus/python/PyBridgeImpl.h"
#include "../../../../saccubus/python/ScriptException.h"
using namespace saccubus::python;

namespace saccubus{
namespace test {
namespace python {

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

/**
 * とりあえず実行できるかどうかのシンプルなテスト
 */
TEST_F(PyBridgeImplTest, SimpleTest)
{
	ASSERT_EQ(0, PyRun_SimpleString("print('hello world')"));
	// WindowsだとPyRun_SimpleFileは動かない。というかFILE構造体を使う関数は使えない。
	// http://docs.python.org/faq/windows.html#pyrun-simplefile-crashes-on-windows-but-not-on-unix-why
	/*
	FILE* fp = fopen(MATERIAL_DIR"test.py", "r");
	ASSERT_EQ(0, PyRun_SimpleFile(fp, MATERIAL_DIR"test.py"));
	fclose(fp);
	fp = fopen(MATERIAL_DIR"test_failure.py", "r");
	ASSERT_EQ(-1, PyRun_SimpleFile(fp, MATERIAL_DIR"test_failure.py"));
	fclose(fp);
	*/
}

TEST_F(PyBridgeImplTest, InvalidFileTest)
{
	ASSERT_THROW(session->loadFile("not_exists"), ScriptException); //そんなのない
	ASSERT_THROW(session->loadFile(MATERIAL_DIR"test_failure.py"), ScriptException); //文法がおかしい
}

TEST_F(PyBridgeImplTest, DictTest)
{
	ASSERT_NO_THROW(session->loadFile(MATERIAL_DIR"test.py"));
	std::vector<std::pair<std::string, std::string> > args;
	args.push_back(std::pair<std::string, std::string>("first", "1"));
	args.push_back(std::pair<std::string, std::string>("second", "2"));
	std::map<std::string, std::string> result = session->executeMethodDict("test_succeed_dict", args);
	ASSERT_EQ(std::string("3"), result["result"]);
}

TEST_F(PyBridgeImplTest, BoolTest)
{
	ASSERT_NO_THROW(session->loadFile(MATERIAL_DIR"test.py"));
	std::vector<std::pair<std::string, std::string> > args;
	args.push_back(std::pair<std::string, std::string>("two_plus_two", "4"));
	args.push_back(std::pair<std::string, std::string>("five", "5"));
	ASSERT_FALSE(session->executeMethodBool("test_not_equal", args));
}

TEST_F(PyBridgeImplTest, FailTest)
{
	ASSERT_NO_THROW(session->loadFile(MATERIAL_DIR"test.py"));
	ASSERT_THROW(session->executeMethodDict("test_run_fail", std::vector<std::pair<std::string, std::string> >()), ScriptException);
}

}}}
