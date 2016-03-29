/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
#include <nekomata/Nekomata.h>
#include <nekomata/parser/Parser.h>
#include "MockSystem.h"

#define QUEUE_SRC(__neko__, __msg__) \
	(__neko__).queueMessage(\
		std::shared_ptr<nekomata::system::Message>(\
				new nekomata::system::Script(\
						0, nekomata::parser::Parser::fromString((__msg__))->parseProgram())));

#define INIT_NEKO(__neko__) \
	nekomata::logging::Logger __lg__( cinamo::Logger(std::cout, cinamo::Logger::TRACE_) );\
	MockSystem __mock__(__lg__);\
	Nekomata __neko__(__mock__, __lg__);

#define END_NEKO(__neko__, __val__)\
	__neko__.seek(100000);
