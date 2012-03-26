/*
 * Logger.h
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <ostream>
#include <cstdarg>
#include <string>

namespace saccubus {
namespace logging{
/**
 * FIXME: 猫又と被ってる。括りだしたいけど、
 * 猫又の方はソースコードロケーション機能付き。
 */

/**
 * ロガー。
 *
 * ログを書き出す先を抽象化して、
 * ログレベル管理やプリティプリントなどの
 * ユーティリティを付加したクラス。
 */
class Logger {
public:
	enum Level{
		TRACE_=0,
		VERBOSE_=1,
		DEBUG_=2,
		INFO_=3,
		WARN_=4,
		ERROR_=5,
	};
private:
	std::ostream& stream;
	enum Level level;
	void msg(enum Level level, const std::string& tag, const std::string& fmt, std::va_list args);
public:
	Logger(std::ostream& stream, enum Level level);
	virtual ~Logger();
public:
	bool t();
	void t(const std::string& tag, const std::string& fmt, ...);
	bool v();
	void v(const std::string& tag, const std::string& fmt, ...);
	bool d();
	void d(const std::string& tag, const std::string& fmt, ...);
	bool i();
	void i(const std::string& tag, const std::string& fmt, ...);
	void w(const std::string& tag, const std::string& fmt, ...);
	void e(const std::string& tag, const std::string& fmt, ...);
};

}}
#endif /* LOGGER_H_ */
