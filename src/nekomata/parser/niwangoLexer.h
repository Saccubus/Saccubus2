/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : d:/Dropbox/saccubus/Saccubus/src/nekomata/parser\\niwango.g
 *     -                            On : 2013-06-10 19:55:14
 *     -                 for the lexer : niwangoLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer 
niwangoLexer

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pniwangoLexer, which is returned from a call to niwangoLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 *
 * The methods in pniwangoLexer are  as follows:
 *
 *  - 
 void
      pniwangoLexer->T__22(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__23(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__24(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__25(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__26(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__27(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__28(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__29(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__30(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__31(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__32(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__33(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__34(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__35(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__36(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__37(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__38(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__39(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__40(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__41(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__42(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__43(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__44(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__45(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__46(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__47(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__48(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__49(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__50(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__51(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__52(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__53(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__54(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__55(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->T__56(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->IDENT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->LETTER(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->STRING_SINGLE(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->STRING_SINGLE_ELEMENT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->STRING_DOUBLE(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->STRING_DOUBLE_ELEMENT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->ESC_SEQ(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->HEX_LITERAL(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->OCT_LITERAL(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->NUM_LITERAL(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->DIGIT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->NONZERO_DIGIT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->EXPONENT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->HEX_DIGIT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->OCT_DIGIT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->EOL(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->WS(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->COMMENT(pniwangoLexer)
 *  - 
 void
      pniwangoLexer->Tokens(pniwangoLexer)
 * 
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_niwangoLexer_H
#define _niwangoLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct niwangoLexer_Ctx_struct niwangoLexer, * pniwangoLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */


/** Context tracking structure for 
niwangoLexer

 */
struct niwangoLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;

     void
     (*mT__22)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__23)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__24)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__25)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__26)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__27)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__28)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__29)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__30)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__31)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__32)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__33)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__34)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__35)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__36)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__37)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__38)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__39)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__40)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__41)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__42)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__43)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__44)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__45)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__46)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__47)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__48)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__49)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__50)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__51)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__52)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__53)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__54)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__55)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mT__56)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mIDENT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mLETTER)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mSTRING_SINGLE)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mSTRING_SINGLE_ELEMENT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mSTRING_DOUBLE)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mSTRING_DOUBLE_ELEMENT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mESC_SEQ)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mHEX_LITERAL)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mOCT_LITERAL)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mNUM_LITERAL)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mDIGIT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mNONZERO_DIGIT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mEXPONENT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mHEX_DIGIT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mOCT_DIGIT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mEOL)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mWS)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mCOMMENT)	(struct niwangoLexer_Ctx_struct * ctx);

     void
     (*mTokens)	(struct niwangoLexer_Ctx_struct * ctx);

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct niwangoLexer_Ctx_struct * ctx);
    void	    (*free)   (struct niwangoLexer_Ctx_struct * ctx);
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pniwangoLexer niwangoLexerNew         (
pANTLR3_INPUT_STREAM
 instream);
ANTLR3_API pniwangoLexer niwangoLexerNewSSD      (
pANTLR3_INPUT_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
lexer
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__22      22
#define T__23      23
#define T__24      24
#define T__25      25
#define T__26      26
#define T__27      27
#define T__28      28
#define T__29      29
#define T__30      30
#define T__31      31
#define T__32      32
#define T__33      33
#define T__34      34
#define T__35      35
#define T__36      36
#define T__37      37
#define T__38      38
#define T__39      39
#define T__40      40
#define T__41      41
#define T__42      42
#define T__43      43
#define T__44      44
#define T__45      45
#define T__46      46
#define T__47      47
#define T__48      48
#define T__49      49
#define T__50      50
#define T__51      51
#define T__52      52
#define T__53      53
#define T__54      54
#define T__55      55
#define T__56      56
#define COMMENT      4
#define DIGIT      5
#define EOL      6
#define ESC_SEQ      7
#define EXPONENT      8
#define HEX_DIGIT      9
#define HEX_LITERAL      10
#define IDENT      11
#define LETTER      12
#define NONZERO_DIGIT      13
#define NUM_LITERAL      14
#define OCT_DIGIT      15
#define OCT_LITERAL      16
#define STRING_DOUBLE      17
#define STRING_DOUBLE_ELEMENT      18
#define STRING_SINGLE      19
#define STRING_SINGLE_ELEMENT      20
#define WS      21
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for niwangoLexer
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
