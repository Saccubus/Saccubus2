/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include "../../../TestCommon.h"
#include "../../../../src/saccubus/layer/item/Comment.h"
#include "../../../nicomo/model/Comment.h"

namespace saccubus{
namespace test {
namespace layer {
namespace item {

class MailOperationTest : public ::testing::Test
{
public:
	void SetUp(){
	}
	void TearDown(){
	}
};

#define COLOROP(_ispremium,_mail, _color, _shadow) \
	do {\
		saccubus::layer::item::Comment com(nullptr, nullptr, false, false, _ispremium, saccubus::layer::item::Comment::Normal,0.0f, "test", _mail);\
		ASSERT_EQ(_color, com.color());\
		ASSERT_EQ(_shadow,com.shadowColor());\
	} while(false);

#define COLOROP_NOT(_ispremium,_mail, _color, _shadow) \
	do {\
		saccubus::layer::item::Comment com(nullptr, nullptr, false, false, _ispremium, saccubus::layer::item::Comment::Normal,0.0f, "test", _mail);\
		ASSERT_NE(_color, com.color());\
	} while(false);


TEST_F(MailOperationTest, ColorTest)
{
	COLOROP(false, "red", 0xFF0000U, 0x000000U);
	COLOROP(false, "black", 0x000000U, 0xFFFFFFU);

	COLOROP(true, "red", 0xFF0000U, 0x000000U);
	COLOROP(true, "black", 0x000000U, 0xFFFFFFU);
}
TEST_F(MailOperationTest, PremiumColorTest)
{
	COLOROP(true, "purple2", 0x6633CCU, 0x000000U);
	COLOROP(true, "white2", 0xCCCC99U, 0x000000U);
	COLOROP(true, "niconicowhite", 0xCCCC99U, 0x000000U);
	COLOROP(true, "#123456", 0x123456U, 0x000000U);
}

TEST_F(MailOperationTest, PermissionTest)
{
	COLOROP_NOT(false, "purple2", 0x6633CCU, 0x000000U);
	COLOROP_NOT(false, "white2", 0xCCCC99U, 0x000000U);
	COLOROP_NOT(false, "niconicowhite", 0xCCCC99U, 0x000000U);
	COLOROP_NOT(false, "#123456", 0x123456U, 0x000000U);
}

TEST_F(MailOperationTest, PremiumColorCodeTest)
{
	COLOROP(true, "#123456", 0x123456U, 0x000000U);
	COLOROP(true, "#FFFFFF", 0xFFFFFFU, 0x000000U);
}

#undef COLOROP
#undef COLOROP_NOT

#define OPPLACE(_mail, pos) \
	do {\
		saccubus::layer::item::Comment com(nullptr, nullptr, false, false, false, saccubus::layer::item::Comment::Normal,0.0f, "test", _mail);\
		ASSERT_EQ(saccubus::layer::item::Comment::pos, com.placeY());\
	} while(false);\

TEST_F(MailOperationTest, PlaceYTest)
{
	OPPLACE("shita", Bottom);
	OPPLACE("ue", Top);
	OPPLACE("naka", Middle);
}

#undef OPPLACE

#define OPTIME(_mail, pos) \
	do {\
		ASSERT_EQ(saccubus::layer::item::Comment::pos, com.placeY());\
	} while(false);\

TEST_F(MailOperationTest, TimeTest)
{
	saccubus::layer::item::Comment com(
			nullptr, nullptr, false, false, false, saccubus::layer::item::Comment::Forked,
			0.0f,
			"test", "@10");\
		ASSERT_FLOAT_EQ(10.0, com.to()-com.from());
}


TEST_F(MailOperationTest, EtcTest)
{
#define SWITCH_FROM(_A,_B,name,meth) \
	do {\
		nicomock::model::Comment orig,def;\
		orig.mail(#name);\
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);\
		saccubus::layer::item::Comment comDef(nullptr, nullptr, nullptr, &def);\
		ASSERT_EQ(_A, comDef.meth());\
		ASSERT_EQ(_B, com.meth());\
	} while(false);

	SWITCH_FROM(false, true, full, full);
	SWITCH_FROM(false, true, sage, sage);
	SWITCH_FROM(false, true, patissier, patissier);
	SWITCH_FROM(true, false, invisible, visibility);
	SWITCH_FROM(false, true, from_button, fromButton);

#undef SWICTH_FROM
}

TEST_F(MailOperationTest, BrokenCommandTest)
{
	nicomock::model::Comment orig,def;
	orig.premium(true);
	orig.mail("#123456");
	{
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		ASSERT_EQ(0x123456, com.color());
	}
	orig.mail("#12ker3");
	{
		saccubus::layer::item::Comment com(nullptr, nullptr, nullptr, &orig);
		saccubus::layer::item::Comment comDef(nullptr, nullptr, nullptr, &def);
		ASSERT_EQ(comDef.color(), com.color());
	}
}

}}}}
