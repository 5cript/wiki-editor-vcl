//---------------------------------------------------------------------------
#pragma once

#ifndef Q_MOC_RUN
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#endif

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
//---------------------------------------------------------------------------
#define SEQUENCE_FACTORY_0(...) \
     ((__VA_ARGS__)) SEQUENCE_FACTORY_1
#define SEQUENCE_FACTORY_1(...) \
     ((__VA_ARGS__)) SEQUENCE_FACTORY_0
#define SEQUENCE_FACTORY_0_END
#define SEQUENCE_FACTORY_1_END

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
		 9,8,7,6,5,4,3,2,1,0

#define EAT(...) \
	__VA_ARGS__

#define TUPSIZE(TUP) \
	PP_NARG(EAT TUP)


#define MEMBER_CAT(r, data, elem) BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 0, elem) BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem);
#define FUSION_CAT(r, data, elem) (BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 0, elem), BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem))
#define INIT_LIST(r, data, elem) (BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem) { \
	BOOST_PP_IF(BOOST_PP_EQUAL(TUPSIZE(elem), 3), \
		BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 2, elem), \
	) \
})
#define CTOR_PARMS(r, data, elem) (BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 0, elem) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem), _))
#define INIT_LIST2(r, data, elem) (BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem) {BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(TUPSIZE(elem), 1, elem), _)})
#define JSON_OBJECT_IMPL(NAME, SEQ, SEQ_CUT) \
struct NAME : JSON::Stringifiable <NAME> \
			, JSON::Parsable <NAME> \
{ \
	BOOST_PP_SEQ_FOR_EACH(MEMBER_CAT,, SEQ) \
	\
	NAME() \
		: BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(INIT_LIST,, SEQ)) \
    {} \
    \
    NAME(BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(CTOR_PARMS,, SEQ))) \
        : BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_FOR_EACH(INIT_LIST2,, SEQ)) \
    {} \
}; \
BOOST_FUSION_ADAPT_STRUCT(NAME, SEQ_CUT)

#define JSON_OBJECT(NAME, SEQ) \
	JSON_OBJECT_IMPL(NAME, BOOST_PP_CAT(SEQUENCE_FACTORY_0 SEQ,_END), \
						   BOOST_PP_SEQ_FOR_EACH(FUSION_CAT,,BOOST_PP_CAT(SEQUENCE_FACTORY_0 SEQ,_END)))

//---------------------------------------------------------------------------
JSON_OBJECT
(
	BackupOptions,
	(int, intervalSec, 30)
	(int, maxBackups, 120)
)

JSON_OBJECT
(
	SettingsHolder,
	(BackupOptions, backupOptions)
)
//---------------------------------------------------------------------------
SettingsHolder loadSettings();
void saveSettings(SettingsHolder const& settings);
void setupSettings();
//---------------------------------------------------------------------------
