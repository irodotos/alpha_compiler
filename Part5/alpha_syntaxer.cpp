/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yyalpha.yacc"

#include "symbol_table.hpp"
#include "quad.hpp"


	int yyerror( char *ErrorMessage);
	int curr_scope = 0;
	extern int yylineno;
	extern int yylex(void);

	ScopeType prev_block;
	bool isReturn=false;
	int inFunction=0;
	bool Insert = false;
	std::stack<int> scopeoffsetstack;
	std::stack<int> functionjumpstack;
	std::stack<std::vector<unsigned int>> functionretstack;
	bool isBackpatch = 0;



#line 93 "alpha_syntaxer.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "alpha_syntaxer.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PLUS = 3,                       /* PLUS  */
  YYSYMBOL_ASSIGNMENT = 4,                 /* ASSIGNMENT  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_MULTIPLICATION = 6,             /* MULTIPLICATION  */
  YYSYMBOL_DIVISION = 7,                   /* DIVISION  */
  YYSYMBOL_MODULO = 8,                     /* MODULO  */
  YYSYMBOL_PLUS_PLUS = 9,                  /* PLUS_PLUS  */
  YYSYMBOL_MINUS_MINUS = 10,               /* MINUS_MINUS  */
  YYSYMBOL_UMINUS = 11,                    /* UMINUS  */
  YYSYMBOL_EQUAL = 12,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 13,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER_THAN = 14,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN = 15,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_OR_EQUAL = 16,          /* GREATER_OR_EQUAL  */
  YYSYMBOL_LESS_OR_EQUAL = 17,             /* LESS_OR_EQUAL  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_FUNCTION = 22,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 23,                    /* RETURN  */
  YYSYMBOL_BREAK = 24,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 25,                  /* CONTINUE  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_LOCAL = 29,                     /* LOCAL  */
  YYSYMBOL_TRUE = 30,                      /* TRUE  */
  YYSYMBOL_FALSE = 31,                     /* FALSE  */
  YYSYMBOL_NIL = 32,                       /* NIL  */
  YYSYMBOL_LEFT_BRACE = 33,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 34,               /* RIGHT_BRACE  */
  YYSYMBOL_LEFT_BRACKET = 35,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 36,             /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_PAREN = 37,                /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 38,               /* RIGHT_PAREN  */
  YYSYMBOL_SEMICOLON = 39,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_COLON = 41,                     /* COLON  */
  YYSYMBOL_COLON_COLON = 42,               /* COLON_COLON  */
  YYSYMBOL_DOT = 43,                       /* DOT  */
  YYSYMBOL_DOT_DOT = 44,                   /* DOT_DOT  */
  YYSYMBOL_COMM_LINE = 45,                 /* COMM_LINE  */
  YYSYMBOL_COMM_BLOCK = 46,                /* COMM_BLOCK  */
  YYSYMBOL_UNDEFINED = 47,                 /* UNDEFINED  */
  YYSYMBOL_NEWLINE = 48,                   /* NEWLINE  */
  YYSYMBOL_INTCONST = 49,                  /* INTCONST  */
  YYSYMBOL_REALCONST = 50,                 /* REALCONST  */
  YYSYMBOL_IDENT = 51,                     /* IDENT  */
  YYSYMBOL_STRINGCONST = 52,               /* STRINGCONST  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_stmt = 55,                      /* stmt  */
  YYSYMBOL_stmts = 56,                     /* stmts  */
  YYSYMBOL_expr = 57,                      /* expr  */
  YYSYMBOL_and_prefix = 58,                /* and_prefix  */
  YYSYMBOL_or_prefix = 59,                 /* or_prefix  */
  YYSYMBOL_not_equal_prefix = 60,          /* not_equal_prefix  */
  YYSYMBOL_equal_prefix = 61,              /* equal_prefix  */
  YYSYMBOL_Q = 62,                         /* Q  */
  YYSYMBOL_term = 63,                      /* term  */
  YYSYMBOL_assignexpr = 64,                /* assignexpr  */
  YYSYMBOL_65_1 = 65,                      /* $@1  */
  YYSYMBOL_primary = 66,                   /* primary  */
  YYSYMBOL_lvalue = 67,                    /* lvalue  */
  YYSYMBOL_member = 68,                    /* member  */
  YYSYMBOL_call = 69,                      /* call  */
  YYSYMBOL_callsuffix = 70,                /* callsuffix  */
  YYSYMBOL_normcall = 71,                  /* normcall  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_methodcall = 73,                /* methodcall  */
  YYSYMBOL_74_3 = 74,                      /* $@3  */
  YYSYMBOL_elist = 75,                     /* elist  */
  YYSYMBOL_objectdef = 76,                 /* objectdef  */
  YYSYMBOL_indexed = 77,                   /* indexed  */
  YYSYMBOL_indexedelem = 78,               /* indexedelem  */
  YYSYMBOL_block = 79,                     /* block  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_func_name = 81,                 /* func_name  */
  YYSYMBOL_func_prefix = 82,               /* func_prefix  */
  YYSYMBOL_func_args = 83,                 /* func_args  */
  YYSYMBOL_84_5 = 84,                      /* $@5  */
  YYSYMBOL_func_body = 85,                 /* func_body  */
  YYSYMBOL_funcdef = 86,                   /* funcdef  */
  YYSYMBOL_const = 87,                     /* const  */
  YYSYMBOL_idlist = 88,                    /* idlist  */
  YYSYMBOL_89_6 = 89,                      /* $@6  */
  YYSYMBOL_idlists = 90,                   /* idlists  */
  YYSYMBOL_91_7 = 91,                      /* $@7  */
  YYSYMBOL_ifprefix = 92,                  /* ifprefix  */
  YYSYMBOL_elseprefix = 93,                /* elseprefix  */
  YYSYMBOL_ifstmt = 94,                    /* ifstmt  */
  YYSYMBOL_whilestart = 95,                /* whilestart  */
  YYSYMBOL_whilecond = 96,                 /* whilecond  */
  YYSYMBOL_whilestmt = 97,                 /* whilestmt  */
  YYSYMBOL_N = 98,                         /* N  */
  YYSYMBOL_M = 99,                         /* M  */
  YYSYMBOL_forprefix = 100,                /* forprefix  */
  YYSYMBOL_101_8 = 101,                    /* $@8  */
  YYSYMBOL_forstmt = 102,                  /* forstmt  */
  YYSYMBOL_returnstmt = 103,               /* returnstmt  */
  YYSYMBOL_104_9 = 104,                    /* $@9  */
  YYSYMBOL_105_10 = 105                    /* $@10  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   529

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    85,   102,   103,   104,   105,   106,   112,
     118,   119,   120,   124,   125,   128,   129,   134,   139,   144,
     149,   154,   155,   156,   157,   158,   167,   176,   194,   213,
     216,   232,   249,   260,   271,   272,   273,   279,   298,   321,
     344,   368,   392,   395,   395,   431,   435,   436,   437,   438,
     441,   501,   532,   544,   547,   548,   554,   560,   563,   574,
     583,   590,   591,   594,   594,   605,   605,   614,   627,   632,
     635,   645,   657,   658,   666,   675,   675,   681,   682,   685,
     717,   717,   728,   735,   750,   751,   752,   753,   754,   755,
     758,   758,   775,   778,   778,   795,   798,   817,   823,   826,
     832,   838,   858,   868,   874,   877,   877,   893,   905,   905,
     916,   916
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PLUS", "ASSIGNMENT",
  "MINUS", "MULTIPLICATION", "DIVISION", "MODULO", "PLUS_PLUS",
  "MINUS_MINUS", "UMINUS", "EQUAL", "NOT_EQUAL", "GREATER_THAN",
  "LESS_THAN", "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "IF", "ELSE", "WHILE",
  "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT",
  "LOCAL", "TRUE", "FALSE", "NIL", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PAREN", "RIGHT_PAREN",
  "SEMICOLON", "COMMA", "COLON", "COLON_COLON", "DOT", "DOT_DOT",
  "COMM_LINE", "COMM_BLOCK", "UNDEFINED", "NEWLINE", "INTCONST",
  "REALCONST", "IDENT", "STRINGCONST", "$accept", "program", "stmt",
  "stmts", "expr", "and_prefix", "or_prefix", "not_equal_prefix",
  "equal_prefix", "Q", "term", "assignexpr", "$@1", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "$@2", "methodcall", "$@3",
  "elist", "objectdef", "indexed", "indexedelem", "block", "$@4",
  "func_name", "func_prefix", "func_args", "$@5", "func_body", "funcdef",
  "const", "idlist", "$@6", "idlists", "$@7", "ifprefix", "elseprefix",
  "ifstmt", "whilestart", "whilecond", "whilestmt", "N", "M", "forprefix",
  "$@8", "forstmt", "returnstmt", "$@9", "$@10", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-170)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-111)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     162,   222,   -15,   -15,   -31,  -170,  -170,   -36,   -30,    -4,
       6,   222,   -26,  -170,  -170,  -170,  -170,   114,   193,  -170,
      -9,  -170,  -170,  -170,  -170,    28,   162,  -170,   288,  -170,
    -170,   222,   222,  -170,  -170,  -170,     3,  -170,   -14,  -170,
    -170,    13,  -170,  -170,   162,  -170,    38,  -170,  -170,  -170,
    -170,  -170,    66,   -11,   -14,   -11,   222,    56,  -170,  -170,
     222,    32,  -170,  -170,  -170,  -170,   162,   222,   466,     1,
       8,  -170,   348,    57,  -170,  -170,  -170,   222,   222,   222,
     222,   222,  -170,  -170,   222,   222,   222,   222,  -170,  -170,
    -170,   222,   222,   497,   497,  -170,  -170,   222,  -170,    48,
      50,    96,  -170,  -170,  -170,   222,   222,    51,  -170,    70,
      87,   222,   162,   222,    69,   375,   222,   304,  -170,    75,
     272,  -170,   222,  -170,    78,  -170,    76,    61,    61,  -170,
    -170,  -170,    46,    46,    46,    46,   512,   482,   418,   222,
    -170,    77,   222,   434,   -20,  -170,    65,  -170,  -170,  -170,
     162,   391,  -170,    18,    76,  -170,    25,  -170,  -170,   222,
     466,  -170,   222,  -170,    34,  -170,   466,  -170,  -170,  -170,
      80,  -170,  -170,  -170,  -170,   450,    49,  -170,   222,    82,
    -170,   162,   222,  -170,  -170,    54,    74,  -170,  -170,   332,
    -170,  -170,  -170,  -170,    82,  -170
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      14,     0,     0,     0,     0,   100,   105,    78,   108,     0,
       0,     0,     0,    88,    89,    87,    75,    69,     0,    12,
       0,    84,    85,    50,    86,     0,    14,     2,     0,    34,
      34,     0,     0,    29,    15,    42,    45,    53,    46,    47,
      10,     0,    11,    49,     0,     4,     0,     5,   103,     6,
       7,    36,     0,    38,     0,    40,     0,     0,    77,    79,
       0,     0,     8,     9,    37,    51,    14,     0,    67,     0,
       0,    72,     0,     0,    52,     1,    13,     0,     0,     0,
       0,     0,    33,    32,     0,     0,     0,     0,    30,    31,
       3,     0,     0,    26,    25,    39,    41,     0,    63,     0,
       0,     0,    59,    61,    62,     0,    69,     0,    80,     0,
      98,     0,     0,    69,     0,     0,    69,     0,   111,     0,
       0,    71,     0,    70,     0,    35,    48,    16,    17,    18,
      19,    20,    21,    23,    22,    24,    27,    28,     0,    69,
      54,     0,     0,     0,     0,    56,    92,    82,    83,    97,
       0,     0,   102,     0,     0,    96,     0,   109,    76,     0,
      68,    73,    69,    55,     0,    65,    44,    57,    58,    90,
       0,    99,   101,   103,   104,     0,     0,    64,    69,    95,
      81,     0,     0,    74,    60,     0,     0,    91,   103,     0,
      66,    93,   107,   106,    95,    94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,   -42,   -23,    -1,  -170,  -170,  -170,  -170,    90,
    -170,  -170,  -170,  -170,    79,  -170,    95,  -170,  -170,  -170,
    -170,  -170,  -105,  -170,  -170,    -7,    17,  -170,  -170,  -170,
    -170,  -170,  -170,   -13,  -170,  -170,  -170,   -67,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -169,  -170,  -170,  -170,  -170,
    -170,  -170,  -170
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    91,
      33,    34,   101,    35,    36,    37,    38,   102,   103,   139,
     104,   178,    69,    39,    70,    71,    40,    66,    59,    41,
     109,   146,   148,    42,    43,   170,   179,   187,   194,    44,
     150,    45,    46,   112,    47,   113,   182,    48,    57,    49,
      50,    60,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   144,   110,    76,   181,    73,    56,   -43,   153,  -110,
      64,   156,    95,    96,    12,    58,    68,    72,   168,   192,
     122,   105,    52,   106,    97,    65,    98,    20,    75,   107,
      93,    94,    99,   100,   164,    62,    23,   121,    97,   114,
      98,   122,    74,   119,   123,    63,    99,   100,   124,    77,
     108,    78,    79,    80,    81,   115,   173,   176,   122,   117,
    -111,  -111,  -111,  -111,   174,   122,   120,    79,    80,    81,
     152,   118,   177,   185,   122,   111,   127,   128,   129,   130,
     131,    53,    55,   132,   133,   134,   135,   184,     7,   122,
     136,   137,   190,   116,   122,   126,   138,    54,    54,   140,
     142,   141,   145,    16,   143,    68,   149,   154,   171,   158,
     151,    67,    68,   162,   165,    68,   169,   161,   180,     1,
      92,   160,   186,     2,     3,   191,   147,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,   188,
       0,   166,    11,    12,    13,    14,    15,    67,     0,    17,
       0,    18,     0,     0,     0,     0,    20,     0,   175,     0,
       0,    68,     0,    21,    22,    23,    24,     1,     0,     0,
       0,     2,     3,     0,     0,     0,     0,    68,     0,     0,
       4,   189,     5,     6,     7,     8,     9,    10,     0,     0,
      11,    12,    13,    14,    15,    16,     0,    17,     1,    18,
       0,    19,     2,     3,    20,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,     7,     0,     0,     0,     0,
       0,    11,    12,    13,    14,    15,     0,     1,    17,     0,
      18,     2,     3,     0,     0,    20,     0,     0,     0,     0,
       0,     0,    21,    22,    23,    24,     0,     0,     0,     0,
      11,    12,    13,    14,    15,     0,     0,    17,     0,    18,
       0,     0,     0,     0,    20,     0,     0,     0,     0,     0,
       0,    21,    22,    23,    24,    77,     0,    78,    79,    80,
      81,     0,     0,     0,    82,    83,    84,    85,    86,    87,
       0,    77,     0,    78,    79,    80,    81,     0,    88,    89,
      82,    83,    84,    85,    86,    87,     0,    77,     0,    78,
      79,    80,    81,   159,    88,    89,    82,    83,    84,    85,
      86,    87,     0,     0,     0,     0,     0,    90,     0,     0,
      88,    89,     0,     0,     0,    77,     0,    78,    79,    80,
      81,     0,     0,   157,    82,    83,    84,    85,    86,    87,
       0,    77,     0,    78,    79,    80,    81,     0,    88,    89,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,   193,     0,     0,    88,    89,     0,     0,    77,     0,
      78,    79,    80,    81,     0,     0,   125,    82,    83,    84,
      85,    86,    87,     0,    77,     0,    78,    79,    80,    81,
       0,    88,    89,    82,    83,    84,    85,    86,    87,     0,
       0,     0,     0,   155,     0,     0,     0,    88,    89,     0,
       0,    77,     0,    78,    79,    80,    81,     0,     0,   172,
      82,    83,    84,    85,    86,    87,     0,    77,     0,    78,
      79,    80,    81,     0,    88,    89,    82,    83,    84,    85,
      86,    87,     0,    77,   163,    78,    79,    80,    81,     0,
      88,    89,    82,    83,    84,    85,    86,    87,     0,    77,
     167,    78,    79,    80,    81,     0,    88,    89,    82,    83,
      84,    85,    86,    87,   183,    77,     0,    78,    79,    80,
      81,     0,    88,    89,    82,    83,    84,    85,    86,    87,
      77,     0,    78,    79,    80,    81,     0,     0,    88,  -111,
    -111,    84,    85,    86,    87,    77,     0,    78,    79,    80,
      81,     0,     0,     0,    82,    83,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       1,   106,    44,    26,   173,    18,    37,     4,   113,    39,
      11,   116,     9,    10,    29,    51,    17,    18,    38,   188,
      40,    35,    37,    37,    35,    51,    37,    42,     0,    43,
      31,    32,    43,    44,   139,    39,    51,    36,    35,    52,
      37,    40,    51,    66,    36,    39,    43,    44,    40,     3,
      37,     5,     6,     7,     8,    56,    38,   162,    40,    60,
      14,    15,    16,    17,    39,    40,    67,     6,     7,     8,
     112,    39,    38,   178,    40,    37,    77,    78,    79,    80,
      81,     2,     3,    84,    85,    86,    87,    38,    22,    40,
      91,    92,    38,    37,    40,    38,    97,     2,     3,    51,
       4,    51,    51,    33,   105,   106,    19,    38,   150,    34,
     111,    33,   113,    37,    37,   116,    51,   124,    38,     5,
      30,   122,    40,     9,    10,    51,   109,   194,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,   181,
      -1,   142,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    37,    -1,    -1,    -1,    -1,    42,    -1,   159,    -1,
      -1,   162,    -1,    49,    50,    51,    52,     5,    -1,    -1,
      -1,     9,    10,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      18,   182,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,     5,    37,
      -1,    39,     9,    10,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    22,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    -1,     5,    35,    -1,
      37,     9,    10,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    35,    -1,    37,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    17,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    26,    27,
      12,    13,    14,    15,    16,    17,    -1,     3,    -1,     5,
       6,     7,     8,    41,    26,    27,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      26,    27,    -1,    -1,    -1,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    39,    12,    13,    14,    15,    16,    17,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    26,    27,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    26,    27,    -1,    -1,     3,    -1,
       5,     6,     7,     8,    -1,    -1,    38,    12,    13,    14,
      15,    16,    17,    -1,     3,    -1,     5,     6,     7,     8,
      -1,    26,    27,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    26,    27,    -1,
      -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,    38,
      12,    13,    14,    15,    16,    17,    -1,     3,    -1,     5,
       6,     7,     8,    -1,    26,    27,    12,    13,    14,    15,
      16,    17,    -1,     3,    36,     5,     6,     7,     8,    -1,
      26,    27,    12,    13,    14,    15,    16,    17,    -1,     3,
      36,     5,     6,     7,     8,    -1,    26,    27,    12,    13,
      14,    15,    16,    17,    34,     3,    -1,     5,     6,     7,
       8,    -1,    26,    27,    12,    13,    14,    15,    16,    17,
       3,    -1,     5,     6,     7,     8,    -1,    -1,    26,    12,
      13,    14,    15,    16,    17,     3,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     9,    10,    18,    20,    21,    22,    23,    24,
      25,    28,    29,    30,    31,    32,    33,    35,    37,    39,
      42,    49,    50,    51,    52,    54,    55,    56,    57,    58,
      59,    60,    61,    63,    64,    66,    67,    68,    69,    76,
      79,    82,    86,    87,    92,    94,    95,    97,   100,   102,
     103,    57,    37,    67,    69,    67,    37,   101,    51,    81,
     104,   105,    39,    39,    57,    51,    80,    33,    57,    75,
      77,    78,    57,    86,    51,     0,    56,     3,     5,     6,
       7,     8,    12,    13,    14,    15,    16,    17,    26,    27,
      39,    62,    62,    57,    57,     9,    10,    35,    37,    43,
      44,    65,    70,    71,    73,    35,    37,    43,    37,    83,
      55,    37,    96,    98,    86,    57,    37,    57,    39,    56,
      57,    36,    40,    36,    40,    38,    38,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    72,
      51,    51,     4,    57,    75,    51,    84,    79,    85,    19,
      93,    57,    55,    75,    38,    38,    75,    39,    34,    41,
      57,    78,    37,    36,    75,    37,    57,    36,    38,    51,
      88,    55,    38,    38,    39,    57,    75,    38,    74,    89,
      38,    98,    99,    34,    38,    75,    40,    90,    55,    57,
      38,    51,    98,    39,    91,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    59,    60,    61,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    65,    64,    66,    66,    66,    66,    66,
      67,    67,    67,    67,    68,    68,    68,    68,    69,    69,
      69,    70,    70,    72,    71,    74,    73,    75,    75,    75,
      76,    76,    77,    77,    78,    80,    79,    81,    81,    82,
      84,    83,    85,    86,    87,    87,    87,    87,    87,    87,
      89,    88,    88,    91,    90,    90,    92,    93,    94,    94,
      95,    96,    97,    98,    99,   101,   100,   102,   104,   103,
     105,   103
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     2,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     1,
       2,     2,     2,     2,     0,     3,     2,     2,     2,     2,
       2,     2,     1,     0,     4,     1,     1,     1,     3,     1,
       1,     2,     2,     1,     3,     4,     3,     4,     4,     2,
       6,     1,     1,     0,     4,     0,     6,     1,     3,     0,
       3,     3,     1,     3,     5,     0,     4,     1,     0,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     3,     0,     0,     4,     0,     4,     1,     2,     4,
       1,     3,     3,     0,     0,     0,     8,     7,     0,     4,
       0,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmts  */
#line 81 "yyalpha.yacc"
               {}
#line 1396 "alpha_syntaxer.cpp"
    break;

  case 3: /* stmt: expr SEMICOLON  */
#line 85 "yyalpha.yacc"
                     {
auto i = (yyvsp[-1].expression);
		if ((yyvsp[-1].expression)->inLogical && isBackpatch == 0) {
		    backpatch((yyvsp[-1].expression)->falselist, nextquad() + 2);
		    backpatch((yyvsp[-1].expression)->truelist, nextquad());
		    auto t = (yyvsp[-1].expression);

		expr* temp = newexpr(arithexpr_e);
		temp->sym = istempexpr((yyvsp[-1].expression)) ? (yyvsp[-1].expression)->sym : new_temp();
		/* $1->sym = istempexpr($expr) ? $expr->sym : new_temp(); */
			emit(assign , temp , newexpr_constbool(true) , NULL ,  0 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , temp  , newexpr_constbool(false) , NULL , 0 , yylineno);
		}
		isBackpatch = 0;
		zero_tmp_counter();
	}
#line 1418 "alpha_syntaxer.cpp"
    break;

  case 4: /* stmt: ifstmt  */
#line 102 "yyalpha.yacc"
                 {zero_tmp_counter();}
#line 1424 "alpha_syntaxer.cpp"
    break;

  case 5: /* stmt: whilestmt  */
#line 103 "yyalpha.yacc"
                    {zero_tmp_counter();}
#line 1430 "alpha_syntaxer.cpp"
    break;

  case 6: /* stmt: forstmt  */
#line 104 "yyalpha.yacc"
                  {zero_tmp_counter();}
#line 1436 "alpha_syntaxer.cpp"
    break;

  case 7: /* stmt: returnstmt  */
#line 105 "yyalpha.yacc"
                     {zero_tmp_counter();}
#line 1442 "alpha_syntaxer.cpp"
    break;

  case 8: /* stmt: BREAK SEMICOLON  */
#line 106 "yyalpha.yacc"
                          {
			if(!is_in_loop()){yyerror("ERROR:: BREAK outside loop ");}
			insert_break(nextquad());
			emit(jump, NULL, NULL, NULL, 0, yylineno);
			zero_tmp_counter();
						}
#line 1453 "alpha_syntaxer.cpp"
    break;

  case 9: /* stmt: CONTINUE SEMICOLON  */
#line 112 "yyalpha.yacc"
                            {
			if(!is_in_loop()){yyerror("ERROR:: CONTINUE outside loop ");}
			insert_cont(nextquad());
			emit(jump, NULL, NULL, NULL, 0, yylineno);
			zero_tmp_counter();
						}
#line 1464 "alpha_syntaxer.cpp"
    break;

  case 10: /* stmt: block  */
#line 118 "yyalpha.yacc"
                {zero_tmp_counter();}
#line 1470 "alpha_syntaxer.cpp"
    break;

  case 11: /* stmt: funcdef  */
#line 119 "yyalpha.yacc"
                  {zero_tmp_counter();}
#line 1476 "alpha_syntaxer.cpp"
    break;

  case 12: /* stmt: SEMICOLON  */
#line 120 "yyalpha.yacc"
                    {zero_tmp_counter();}
#line 1482 "alpha_syntaxer.cpp"
    break;

  case 16: /* expr: expr PLUS expr  */
#line 129 "yyalpha.yacc"
                        {
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = recycle_temp((yyvsp[-2].expression),(yyvsp[0].expression));
		emit(add, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0 , yylineno);
	}
#line 1492 "alpha_syntaxer.cpp"
    break;

  case 17: /* expr: expr MINUS expr  */
#line 134 "yyalpha.yacc"
                          {
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = recycle_temp((yyvsp[-2].expression),(yyvsp[0].expression));
		emit(sub, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0 , yylineno);
	}
#line 1502 "alpha_syntaxer.cpp"
    break;

  case 18: /* expr: expr MULTIPLICATION expr  */
#line 139 "yyalpha.yacc"
                                  {
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = recycle_temp((yyvsp[-2].expression),(yyvsp[0].expression));
		emit(mul, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0 , yylineno);
	}
#line 1512 "alpha_syntaxer.cpp"
    break;

  case 19: /* expr: expr DIVISION expr  */
#line 144 "yyalpha.yacc"
                            {
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = recycle_temp((yyvsp[-2].expression),(yyvsp[0].expression));
		emit(div_, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0 , yylineno);
	}
#line 1522 "alpha_syntaxer.cpp"
    break;

  case 20: /* expr: expr MODULO expr  */
#line 149 "yyalpha.yacc"
                          {
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = recycle_temp((yyvsp[-2].expression),(yyvsp[0].expression));
		emit(mod, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0 , yylineno);
	}
#line 1532 "alpha_syntaxer.cpp"
    break;

  case 21: /* expr: expr GREATER_THAN expr  */
#line 154 "yyalpha.yacc"
                                { (yyval.expression)= relop( (yyvsp[-2].expression),if_greater, (yyvsp[0].expression)); }
#line 1538 "alpha_syntaxer.cpp"
    break;

  case 22: /* expr: expr GREATER_OR_EQUAL expr  */
#line 155 "yyalpha.yacc"
                                    { (yyval.expression)= relop( (yyvsp[-2].expression),if_greatereq, (yyvsp[0].expression)); }
#line 1544 "alpha_syntaxer.cpp"
    break;

  case 23: /* expr: expr LESS_THAN expr  */
#line 156 "yyalpha.yacc"
                             { (yyval.expression) = relop( (yyvsp[-2].expression),if_less, (yyvsp[0].expression));}
#line 1550 "alpha_syntaxer.cpp"
    break;

  case 24: /* expr: expr LESS_OR_EQUAL expr  */
#line 157 "yyalpha.yacc"
                                 { (yyval.expression)= relop( (yyvsp[-2].expression),if_lesseq, (yyvsp[0].expression)); }
#line 1556 "alpha_syntaxer.cpp"
    break;

  case 25: /* expr: equal_prefix expr  */
#line 158 "yyalpha.yacc"
                                      { 
			(yyval.expression)= relop( (yyvsp[-1].expression),if_eq, (yyvsp[0].expression));
			backpatch((yyval.expression)->falselist , nextquad()+2);
			backpatch((yyval.expression)->truelist , nextquad());
			/* $$->sym =  recycle_temp($1,$2); */
			/* emit(assign , $$ , newexpr_constbool(true) , NULL ,  -1 , yylineno); */
			/* emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno); */
			/* emit(assign , $$  , newexpr_constbool(false) , NULL , -1 , yylineno); */
	}
#line 1570 "alpha_syntaxer.cpp"
    break;

  case 26: /* expr: not_equal_prefix expr  */
#line 167 "yyalpha.yacc"
                                              {
			(yyval.expression)= relop( (yyvsp[-1].expression),if_noteq, (yyvsp[0].expression));
			backpatch((yyval.expression)->falselist , nextquad()+2);
			backpatch((yyval.expression)->truelist , nextquad());
			/* $$->sym =  recycle_temp($1,$2); */
			/* emit(assign , $$ , newexpr_constbool(true) , NULL ,  -1 , yylineno); */
			/* emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno); */
			/* emit(assign , $$  , newexpr_constbool(false) , NULL , -1 , yylineno); */
	}
#line 1584 "alpha_syntaxer.cpp"
    break;

  case 27: /* expr: and_prefix Q expr  */
#line 176 "yyalpha.yacc"
                                     {
			if ((yyvsp[0].expression)->truelist.size() == 0 && (yyvsp[0].expression)->falselist.size() == 0) {
			    /* $3->type = logicalop_e; */
			    (yyvsp[0].expression)->truelist.push_back(nextquad());
			    (yyvsp[0].expression)->falselist.push_back(nextquad() + 1);
			    if ((yyvsp[0].expression)->not_c) {
				(yyvsp[0].expression)->truelist.swap((yyvsp[0].expression)->falselist);
				(yyvsp[0].expression)->not_c = false;
			    }
			    emit(if_eq, NULL,(yyvsp[0].expression), newexpr_constbool(1),  0, yylineno);
			    emit(jump, NULL, NULL, NULL, 0, yylineno);
			}
			backpatch((yyvsp[-2].expression)->truelist, (yyvsp[-1].intVal));
			(yyval.expression)->falselist = mergelists((yyvsp[-2].expression)->falselist, (yyvsp[0].expression)->falselist);
			(yyval.expression)->truelist = (yyvsp[0].expression)->truelist;
			/* $$->type = logicalop_e; */
			(yyval.expression)->inLogical=true;
	}
#line 1607 "alpha_syntaxer.cpp"
    break;

  case 28: /* expr: or_prefix Q expr  */
#line 194 "yyalpha.yacc"
                                   {
			if ((yyvsp[0].expression)->truelist.size() == 0 && (yyvsp[0].expression)->falselist.size() == 0) {
			    /* $3->type = logicalop_e; */
			    (yyvsp[0].expression)->truelist.push_back(nextquad());
			    (yyvsp[0].expression)->falselist.push_back(nextquad() + 1);

			    if ((yyvsp[0].expression)->not_c) {
				(yyvsp[0].expression)->truelist.swap((yyvsp[0].expression)->falselist);
				(yyvsp[0].expression)->not_c = false;
			    }
			    emit(if_eq,NULL, (yyvsp[0].expression), newexpr_constbool(1),  0, yylineno);
			    emit(jump, NULL, NULL, NULL, 0, yylineno);
			}
			backpatch((yyvsp[-2].expression)->falselist, (yyvsp[-1].intVal));
			(yyval.expression)->truelist = mergelists((yyvsp[-2].expression)->truelist, (yyvsp[0].expression)->truelist);
			(yyval.expression)->falselist = (yyvsp[0].expression)->falselist;
			/* $$->type = logicalop_e; */
			(yyval.expression)->inLogical=true;
	}
#line 1631 "alpha_syntaxer.cpp"
    break;

  case 29: /* expr: term  */
#line 213 "yyalpha.yacc"
               {(yyval.expression)=(yyvsp[0].expression);}
#line 1637 "alpha_syntaxer.cpp"
    break;

  case 30: /* and_prefix: expr AND  */
#line 216 "yyalpha.yacc"
                     {
		if ((yyvsp[-1].expression)->truelist.size() == 0 && (yyvsp[-1].expression)->falselist.size() == 0) {
		    /* $1->type = logicalop_e; */
		    (yyvsp[-1].expression)->truelist.push_back(nextquad());
		    (yyvsp[-1].expression)->falselist.push_back(nextquad() + 1);
		    if ((yyvsp[-1].expression)->not_c) {
			(yyvsp[-1].expression)->truelist.swap((yyvsp[-1].expression)->falselist);
			(yyvsp[-1].expression)->not_c = false;
		    }
		    emit(if_eq,  NULL,(yyvsp[-1].expression), newexpr_constbool(1), 0, yylineno);
		    emit(jump, NULL, NULL, NULL, 0, yylineno);
			/* $1->type=logicalop_e; */
		}
	}
#line 1656 "alpha_syntaxer.cpp"
    break;

  case 31: /* or_prefix: expr OR  */
#line 232 "yyalpha.yacc"
                   {


		if((yyvsp[-1].expression)->truelist.size()==0 && (yyvsp[-1].expression)->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			(yyvsp[-1].expression)->truelist.push_back(nextquad());
			(yyvsp[-1].expression)->falselist.push_back( nextquad()+1);
			if ((yyvsp[-1].expression)->not_c){(yyvsp[-1].expression)->truelist.swap((yyvsp[-1].expression)->falselist);(yyvsp[-1].expression)->not_c=false;}

			emit(if_eq,NULL ,(yyvsp[-1].expression),newexpr_constbool(1),0,yylineno);
			emit(jump , NULL , NULL , NULL , 0 , yylineno);
			(yyvsp[-1].expression)->inLogical=true;
		}

	}
#line 1676 "alpha_syntaxer.cpp"
    break;

  case 32: /* not_equal_prefix: expr NOT_EQUAL  */
#line 249 "yyalpha.yacc"
                                {
		if((yyvsp[-1].expression)->truelist.size()==0 && (yyvsp[-1].expression)->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			(yyvsp[-1].expression)->truelist.push_back(nextquad());
			(yyvsp[-1].expression)->falselist.push_back( nextquad()+1);
			if ((yyvsp[-1].expression)->not_c){(yyvsp[-1].expression)->truelist.swap((yyvsp[-1].expression)->falselist);(yyvsp[-1].expression)->not_c=false;}
			(yyvsp[-1].expression)->inLogical=true;
		}
	}
#line 1690 "alpha_syntaxer.cpp"
    break;

  case 33: /* equal_prefix: expr EQUAL  */
#line 260 "yyalpha.yacc"
                        {
		if((yyvsp[-1].expression)->truelist.size()==0 && (yyvsp[-1].expression)->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			(yyvsp[-1].expression)->truelist.push_back(nextquad());
			(yyvsp[-1].expression)->falselist.push_back( nextquad()+1);
			if ((yyvsp[-1].expression)->not_c){(yyvsp[-1].expression)->truelist.swap((yyvsp[-1].expression)->falselist);(yyvsp[-1].expression)->not_c=false;}
			(yyvsp[-1].expression)->inLogical=true;
		}
	}
#line 1704 "alpha_syntaxer.cpp"
    break;

  case 34: /* Q: %empty  */
#line 271 "yyalpha.yacc"
    {(yyval.intVal)=nextquad();}
#line 1710 "alpha_syntaxer.cpp"
    break;

  case 35: /* term: LEFT_PAREN expr RIGHT_PAREN  */
#line 272 "yyalpha.yacc"
                                  {(yyval.expression)=(yyvsp[-1].expression);}
#line 1716 "alpha_syntaxer.cpp"
    break;

  case 36: /* term: MINUS expr  */
#line 273 "yyalpha.yacc"
                                  {
		check_arithm((yyvsp[0].expression), "ERROR:: Not an arirthemic expression!");
		(yyval.expression) = newexpr(arithexpr_e);
		(yyval.expression)->sym = istempexpr((yyvsp[0].expression)) ? (yyvsp[0].expression)->sym : new_temp();
		emit(uminus, (yyval.expression), (yyvsp[0].expression), NULL, 0 , yylineno);
	}
#line 1727 "alpha_syntaxer.cpp"
    break;

  case 37: /* term: NOT expr  */
#line 279 "yyalpha.yacc"
                   {


		if((yyvsp[0].expression)->truelist.size()==0 && (yyvsp[0].expression)->falselist.size()==0){
			/* $expr->type=logicalop_e; */
			(yyvsp[0].expression)->truelist.push_back(nextquad());
			(yyvsp[0].expression)->falselist.push_back( nextquad()+1);
			emit(if_eq, NULL , (yyvsp[0].expression),newexpr_constbool(true) ,0,yylineno);
			emit(jump , NULL , NULL , NULL , 0, yylineno);
}

			(yyvsp[0].expression)->truelist.swap((yyvsp[0].expression)->falselist);
			backpatch((yyvsp[0].expression)->falselist , nextquad()+2);
			backpatch((yyvsp[0].expression)->truelist , nextquad());
			(yyvsp[0].expression)->not_c=true;
			/* if ($expr->sym ==NULL){SymbolTableEntry } */
			(yyvsp[0].expression)->inLogical=true;
		(yyval.expression)=(yyvsp[0].expression);
	}
#line 1751 "alpha_syntaxer.cpp"
    break;

  case 38: /* term: PLUS_PLUS lvalue  */
#line 298 "yyalpha.yacc"
                          {
		if((yyvsp[0].expression) != NULL && (yyvsp[0].expression)->sym != NULL ){
			if ((yyvsp[0].expression)->sym->get_type() == func_USER || (yyvsp[0].expression)->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {


				check_arithm((yyvsp[0].expression) , "Not an arithmetic expression!");
				if ((yyvsp[0].expression)->type == tableitem_e) {
					(yyval.expression) = emit_iftableitem((yyvsp[0].expression));
					emit(add,(yyval.expression), (yyval.expression), newexpr_constnum(1),0,yylineno );
					emit(tablesetelem,(yyvsp[0].expression),  (yyvsp[0].expression)->index,(yyval.expression),0,yylineno );
				}
				else {
					emit(add,(yyvsp[0].expression), (yyvsp[0].expression), newexpr_constnum(1),0,yylineno );
					(yyval.expression) = newexpr(arithexpr_e);
					(yyval.expression)->sym = new_temp();
					emit(assign,(yyval.expression), (yyvsp[0].expression), NULL,0,yylineno);
				}
			}
		}
	}
#line 1779 "alpha_syntaxer.cpp"
    break;

  case 39: /* term: lvalue PLUS_PLUS  */
#line 321 "yyalpha.yacc"
                           {
		if((yyvsp[-1].expression) != NULL && (yyvsp[-1].expression)->sym != NULL ){
			if ((yyvsp[-1].expression)->sym->get_type() == func_USER || (yyvsp[-1].expression)->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {

				check_arithm((yyvsp[-1].expression) , "Not an arithmetic expression!");
				(yyval.expression) = newexpr(var_e);
				(yyval.expression)->sym = new_temp();
				if ((yyvsp[-1].expression)->type == tableitem_e) {
					expr* val = emit_iftableitem((yyvsp[-1].expression));
					emit(assign,(yyval.expression), val, NULL,0,yylineno );
					emit(add,val, val, newexpr_constnum(1),0,yylineno );
					emit(tablesetelem, (yyvsp[-1].expression),  (yyvsp[-1].expression)->index,val,0,yylineno );
				}
				else {
					emit(assign,(yyval.expression), (yyvsp[-1].expression), NULL,0,yylineno);
					emit(add, (yyvsp[-1].expression) ,(yyvsp[-1].expression), newexpr_constnum(1),0,yylineno);
				}
			}
		}
	}
#line 1807 "alpha_syntaxer.cpp"
    break;

  case 40: /* term: MINUS_MINUS lvalue  */
#line 344 "yyalpha.yacc"
                             {
		if((yyvsp[0].expression) != NULL && (yyvsp[0].expression)->sym != NULL ){
			if ((yyvsp[0].expression)->sym->get_type() == func_USER || (yyvsp[0].expression)->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {


				check_arithm((yyvsp[0].expression) , "Not an arithmetic expression!");
				if ((yyvsp[0].expression)->type == tableitem_e) {
					(yyval.expression) = emit_iftableitem((yyvsp[0].expression));
					emit(sub,(yyval.expression), (yyval.expression), newexpr_constnum(1),0,yylineno );
					emit(tablesetelem,(yyvsp[0].expression),  (yyvsp[0].expression)->index,(yyval.expression),0,yylineno );
				}
				else {
					emit(sub,(yyvsp[0].expression), (yyvsp[0].expression), newexpr_constnum(1),0,yylineno );
					(yyval.expression) = newexpr(arithexpr_e);
					(yyval.expression)->sym = new_temp();
					emit(assign,(yyval.expression), (yyvsp[0].expression), NULL,0,yylineno);

				}
			}
		}
	}
#line 1836 "alpha_syntaxer.cpp"
    break;

  case 41: /* term: lvalue MINUS_MINUS  */
#line 368 "yyalpha.yacc"
                             {
		if((yyvsp[-1].expression) != NULL && (yyvsp[-1].expression)->sym != NULL ){
			if ((yyvsp[-1].expression)->sym->get_type() == func_USER || (yyvsp[-1].expression)->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {
				check_arithm((yyvsp[-1].expression) , "Not an arithmetic expression!");
				(yyval.expression) = newexpr(var_e);
				(yyval.expression)->sym = new_temp();
				if ((yyvsp[-1].expression)->type == tableitem_e) {
					expr* val = emit_iftableitem((yyvsp[-1].expression));
					emit(assign,(yyval.expression), val, NULL,0,yylineno );
					emit(sub,val, val, newexpr_constnum(1),0,yylineno );
					emit(tablesetelem, (yyvsp[-1].expression),  (yyvsp[-1].expression)->index,val,0,yylineno );
				}
				else {
					emit(assign,(yyval.expression), (yyvsp[-1].expression), NULL,0,yylineno);
					emit(sub, (yyvsp[-1].expression) ,(yyvsp[-1].expression), newexpr_constnum(1),0,yylineno);

				}
			}

		}
	}
#line 1865 "alpha_syntaxer.cpp"
    break;

  case 43: /* $@1: %empty  */
#line 395 "yyalpha.yacc"
                   {
		
		if((yyvsp[0].expression) != NULL && (yyvsp[0].expression)->sym != NULL ){
			if ((yyvsp[0].expression)->sym->get_type() == func_USER || (yyvsp[0].expression)->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
	    }
	}
#line 1878 "alpha_syntaxer.cpp"
    break;

  case 44: /* assignexpr: lvalue $@1 ASSIGNMENT expr  */
#line 402 "yyalpha.yacc"
                          {

		if ((yyvsp[-3].expression) != NULL && (yyvsp[0].expression)->inLogical) {
		    backpatch((yyvsp[0].expression)->falselist, nextquad() + 2);
		    backpatch((yyvsp[0].expression)->truelist, nextquad());

		    (yyval.expression) = newexpr(boolexpr_e);
		    (yyvsp[0].expression) = newexpr(assignexpr_e);
		    (yyval.expression)->sym = (yyvsp[0].expression)->sym = new_temp();

		    emit(assign, (yyval.expression), newexpr_constbool(true), NULL, 0, yylineno);
		    emit(jump, NULL, NULL, NULL, nextquad() + 2, yylineno);
		    emit(assign, (yyval.expression), newexpr_constbool(false), NULL, 0, yylineno);
		    isBackpatch = true;
		}
auto a = (yyvsp[-3].expression);
		if ((yyvsp[-3].expression) != NULL && (yyvsp[-3].expression)->type == tableitem_e) {
		    emit(tablesetelem, (yyvsp[-3].expression), (yyvsp[-3].expression)->index, (yyvsp[0].expression), 0, yylineno);
		    (yyval.expression) = emit_iftableitem((yyvsp[-3].expression));
		    (yyval.expression)->type = assignexpr_e;
		} else {
		    emit(assign, (yyvsp[-3].expression), (yyvsp[0].expression), NULL, 0, yylineno);
		    (yyval.expression) = newexpr(assignexpr_e);
		    (yyval.expression)->sym = new_temp();
		    emit(assign, (yyval.expression), (yyvsp[-3].expression), NULL, 0, yylineno);
		}
}
#line 1910 "alpha_syntaxer.cpp"
    break;

  case 45: /* primary: lvalue  */
#line 431 "yyalpha.yacc"
                {
				
		(yyval.expression) = emit_iftableitem((yyvsp[0].expression));
				}
#line 1919 "alpha_syntaxer.cpp"
    break;

  case 48: /* primary: LEFT_PAREN funcdef RIGHT_PAREN  */
#line 437 "yyalpha.yacc"
                                         {(yyval.expression) = (yyvsp[-1].expression);}
#line 1925 "alpha_syntaxer.cpp"
    break;

  case 50: /* lvalue: IDENT  */
#line 441 "yyalpha.yacc"
               { 
		Insert = true;
		SymbolTableEntry *temp;
		std::string var_name = yylval.stringVal;
		if (isReturn == true) {
		    Insert = false;
		    if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		    } else if ((temp = lookUp(var_name, curr_scope)) !=
			       NULL) { /* look in all previus scopes starting with the
					  curr_scope -1 until zero */
			Insert = false;
			if (temp->get_type() != func_USER &&
			    temp->get_scope() < get_min_legal_scope()) {
			    yyerror("ERROR:: You cant access the IDENT ");
			}
		    } else if ((temp = lookUpScope(var_name, 0)) != NULL) {

		    } else {
			yyerror("ERROR:: There is no name for the var/func you try to return ");
		    }
		} else {

		    if ((temp = lookUpScope(var_name, curr_scope)) !=
			NULL) { /* look in the same scope => formal arguments and variable in
				   the scope/function */
			Insert = false;
		    } else if ((temp = lookUp(var_name, curr_scope)) !=
			       NULL) { /* look in all previus scopes starting with the
					  curr_scope -1 until zero */
			Insert = false;
			if (temp->get_type() != func_USER &&
			    temp->get_scope() < get_min_legal_scope()) {
			    yyerror("ERROR:: You cant access the IDENT ");
			}
		    } else if ((temp = lookUpScope(var_name, 0)) !=
			       NULL) { /* look in global scope */
			Insert = false;
		    }
		}

		if (Insert == true) {
		    if (curr_scope == 0) {
			insert(var_name, curr_scope, yylineno, var_GLOBAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    } else {
			insert(var_name, curr_scope, yylineno, var_LOCAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    }
		}
		if (temp == NULL) {
		    (yyval.expression) = NULL;
		} else {
		    (yyval.expression) = Symbol_to_Expr(temp);
		}
	}
#line 1989 "alpha_syntaxer.cpp"
    break;

  case 51: /* lvalue: LOCAL IDENT  */
#line 501 "yyalpha.yacc"
                      {

		std::string var_name = yylval.stringVal;
		SymbolTableEntry *temp;
		// elenxos an iparxi idi sto scope ident idio => anaferomaste se afto to ident
		if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		}
		// elenxos an einai idi lib function => error
		else if ((temp = lookUpLIB(var_name)) != NULL) {
		    yyerror("ERROR:: Assigning local libfunc outside GLOBAL scope ");
		}
		// dimiourgiena neo ident kai to vazi stin table => insert in table
		else {
		    if (curr_scope == 0) {
			insert(var_name, curr_scope, yylineno, var_GLOBAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    } else {
			insert(var_name, curr_scope, yylineno, var_LOCAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    }
		}
		if (temp == NULL) {
		    (yyval.expression) = NULL;
		} else {
		    (yyval.expression) = Symbol_to_Expr(temp);
		}
}
#line 2025 "alpha_syntaxer.cpp"
    break;

  case 52: /* lvalue: COLON_COLON IDENT  */
#line 532 "yyalpha.yacc"
                    {
		std::string var_name = yylval.stringVal;
		SymbolTableEntry *temp;
		if ((temp = lookUpScope(var_name, 0)) == NULL) {
		    yyerror("ERROR:: No GLOBAL whith this name ");
		}
		if (temp == NULL) {
		    (yyval.expression) = NULL;
		} else {
		    (yyval.expression) = Symbol_to_Expr(temp);
		}
}
#line 2042 "alpha_syntaxer.cpp"
    break;

  case 53: /* lvalue: member  */
#line 544 "yyalpha.yacc"
                  {(yyval.expression)=(yyvsp[0].expression);}
#line 2048 "alpha_syntaxer.cpp"
    break;

  case 54: /* member: lvalue DOT IDENT  */
#line 547 "yyalpha.yacc"
                         {(yyval.expression) = member_item((yyvsp[-2].expression) , (yyvsp[0].stringVal));}
#line 2054 "alpha_syntaxer.cpp"
    break;

  case 55: /* member: lvalue LEFT_BRACKET expr RIGHT_BRACKET  */
#line 548 "yyalpha.yacc"
                                                  { 
						(yyvsp[-3].expression) = emit_iftableitem((yyvsp[-3].expression)); 
						(yyval.expression) = newexpr(tableitem_e); 
						(yyval.expression)->sym = (yyvsp[-3].expression)->sym; 
						(yyval.expression)->index = (yyvsp[-1].expression); 
					}
#line 2065 "alpha_syntaxer.cpp"
    break;

  case 56: /* member: call DOT IDENT  */
#line 554 "yyalpha.yacc"
                         {
			(yyval.expression)=(yyvsp[-2].expression) ;
			(yyval.expression)->type=tableitem_e;

}
#line 2075 "alpha_syntaxer.cpp"
    break;

  case 58: /* call: call LEFT_PAREN elist RIGHT_PAREN  */
#line 563 "yyalpha.yacc"
                                         {(yyval.expression) = make_call((yyvsp[-3].expression), (yyvsp[-1].expression));

			if((yyvsp[-1].expression) != NULL && (yyvsp[-1].expression)->inLogical){
				expr* temp = newexpr(assignexpr_e);
				temp->sym = new_temp();
				emit(assign , temp , newexpr_constbool(true) , NULL ,  0 , yylineno);
				emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
				emit(assign , temp  , newexpr_constbool(false) , NULL , 0 , yylineno);
			}

	}
#line 2091 "alpha_syntaxer.cpp"
    break;

  case 59: /* call: lvalue callsuffix  */
#line 574 "yyalpha.yacc"
                            {
			(yyvsp[-1].expression) = emit_iftableitem((yyvsp[-1].expression));
			if ((yyvsp[0].callVal)->method) {
			    expr *t = (yyvsp[-1].expression);
			    (yyvsp[-1].expression) = emit_iftableitem(member_item(t, (yyvsp[0].callVal)->name));
			    (yyvsp[0].callVal)->elist->next = t;
			}
			(yyval.expression) = make_call((yyvsp[-1].expression), (yyvsp[0].callVal)->elist);
   }
#line 2105 "alpha_syntaxer.cpp"
    break;

  case 60: /* call: LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN  */
#line 583 "yyalpha.yacc"
                                                                      {
						expr* func = newexpr(programfunc_e);
						func->sym = (yyvsp[-4].expression)->sym;
						(yyval.expression) = make_call(func, (yyvsp[-1].expression));
						}
#line 2115 "alpha_syntaxer.cpp"
    break;

  case 61: /* callsuffix: normcall  */
#line 590 "yyalpha.yacc"
                     {(yyval.callVal) = (yyvsp[0].callVal);}
#line 2121 "alpha_syntaxer.cpp"
    break;

  case 62: /* callsuffix: methodcall  */
#line 591 "yyalpha.yacc"
                     {(yyval.callVal) = (yyvsp[0].callVal);}
#line 2127 "alpha_syntaxer.cpp"
    break;

  case 63: /* $@2: %empty  */
#line 594 "yyalpha.yacc"
                     {}
#line 2133 "alpha_syntaxer.cpp"
    break;

  case 64: /* normcall: LEFT_PAREN $@2 elist RIGHT_PAREN  */
#line 594 "yyalpha.yacc"
                                          {
					
			
			(yyval.callVal) = new callstruct();
			(yyval.callVal)->elist = (yyvsp[-1].expression);
			(yyval.callVal)->method = 0;
			(yyval.callVal)->name = NULL;
			
		}
#line 2147 "alpha_syntaxer.cpp"
    break;

  case 65: /* $@3: %empty  */
#line 605 "yyalpha.yacc"
                                     {}
#line 2153 "alpha_syntaxer.cpp"
    break;

  case 66: /* methodcall: DOT_DOT IDENT LEFT_PAREN $@3 elist RIGHT_PAREN  */
#line 605 "yyalpha.yacc"
                                                           {
							//$$ = newexpr(tableitem_e);

				(yyval.callVal)->elist = (yyvsp[-1].expression);
				(yyval.callVal)->name = (yyvsp[-4].stringVal);
				(yyval.callVal)->method = 1;
	}
#line 2165 "alpha_syntaxer.cpp"
    break;

  case 67: /* elist: expr  */
#line 614 "yyalpha.yacc"
           {
	if((yyvsp[0].expression)!=NULL && (yyvsp[0].expression)->inLogical){
				backpatch((yyvsp[0].expression)->falselist , nextquad()+2);
				backpatch((yyvsp[0].expression)->truelist , nextquad());
				expr* temp = newexpr(assignexpr_e);
				//printf("hshshshshhs");
				temp->sym = new_temp();
				emit(assign , temp , newexpr_constbool(true) , NULL ,  0 , yylineno);
				emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
				emit(assign , temp  , newexpr_constbool(false) , NULL , 0 , yylineno);
				(yyvsp[0].expression) = temp;	
			}
	(yyval.expression) = (yyvsp[0].expression);
}
#line 2184 "alpha_syntaxer.cpp"
    break;

  case 68: /* elist: elist COMMA expr  */
#line 627 "yyalpha.yacc"
                   {
	expr* tmp = (yyvsp[-2].expression);
	while(tmp->next!=NULL) tmp = tmp->next;
	tmp->next = (yyvsp[0].expression);
	(yyval.expression) = (yyvsp[-2].expression);
}
#line 2195 "alpha_syntaxer.cpp"
    break;

  case 69: /* elist: %empty  */
#line 632 "yyalpha.yacc"
   {(yyval.expression) = NULL;}
#line 2201 "alpha_syntaxer.cpp"
    break;

  case 70: /* objectdef: LEFT_BRACKET indexed RIGHT_BRACKET  */
#line 635 "yyalpha.yacc"
                                               {

		expr *temp = newexpr(newtable_e);
		temp->sym = new_temp();
		emit(tablecreate, temp, NULL, NULL, 0, yylineno);
		for (int i = 0; (yyvsp[-1].pairVal); (yyvsp[-1].pairVal) = (yyvsp[-1].pairVal)->next) {
		    emit(tablesetelem, temp, (yyvsp[-1].pairVal)->index, (yyvsp[-1].pairVal)->element, 0, yylineno);
		}
		(yyval.expression) = temp;
	 }
#line 2216 "alpha_syntaxer.cpp"
    break;

  case 71: /* objectdef: LEFT_BRACKET elist RIGHT_BRACKET  */
#line 645 "yyalpha.yacc"
                                              {

        expr* temp = newexpr(newtable_e);
        temp->sym = new_temp();
        emit(tablecreate, temp, NULL, NULL , 0 , yylineno);
        for (int i = 0; (yyvsp[-1].expression); (yyvsp[-1].expression) = (yyvsp[-1].expression)->next){
            emit(tablesetelem,  temp, newexpr_constnum(i++), (yyvsp[-1].expression) , 0 , yylineno);
        }
        (yyval.expression) = temp;
	}
#line 2231 "alpha_syntaxer.cpp"
    break;

  case 72: /* indexed: indexedelem  */
#line 657 "yyalpha.yacc"
                    { (yyval.pairVal)=(yyvsp[0].pairVal);}
#line 2237 "alpha_syntaxer.cpp"
    break;

  case 73: /* indexed: indexed COMMA indexedelem  */
#line 658 "yyalpha.yacc"
                                {
		indexedstruct *temp = (yyvsp[-2].pairVal);
		while (temp->next)
		    temp = temp->next;
		temp->next = (yyvsp[0].pairVal);
		(yyval.pairVal) = (yyvsp[-2].pairVal);
	}
#line 2249 "alpha_syntaxer.cpp"
    break;

  case 74: /* indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE  */
#line 666 "yyalpha.yacc"
                                                    {
	   (yyval.pairVal) = new indexedstruct();	
	   (yyval.pairVal)->index = (yyvsp[-3].expression);
	   (yyval.pairVal)->element= (yyvsp[-1].expression);
	   (yyval.pairVal)->next= NULL;

	   }
#line 2261 "alpha_syntaxer.cpp"
    break;

  case 75: /* $@4: %empty  */
#line 675 "yyalpha.yacc"
                   {
     		curr_scope++;
		push_Scope(prev_block);
		prev_block=BLOCK;
		}
#line 2271 "alpha_syntaxer.cpp"
    break;

  case 76: /* block: LEFT_BRACE $@4 stmts RIGHT_BRACE  */
#line 679 "yyalpha.yacc"
                                    {  hide(curr_scope);  pop_Scope();   curr_scope--;}
#line 2277 "alpha_syntaxer.cpp"
    break;

  case 77: /* func_name: IDENT  */
#line 681 "yyalpha.yacc"
                 {(yyval.stringVal)=(yyvsp[0].stringVal);}
#line 2283 "alpha_syntaxer.cpp"
    break;

  case 78: /* func_name: %empty  */
#line 682 "yyalpha.yacc"
                      {(yyval.stringVal)= get_anon_func_name().c_str();}
#line 2289 "alpha_syntaxer.cpp"
    break;

  case 79: /* func_prefix: FUNCTION func_name  */
#line 685 "yyalpha.yacc"
                                { 
		SymbolTableEntry *temp;
		std::string func_name = std::string((yyvsp[0].stringVal));
		functionretstack.push(std::vector<unsigned int>());
		if ((temp = lookUpLIB(func_name)) != NULL) {
		    yyerror("ERROR:: Shadowing a LIB function ");
		} else if ((temp = lookUpScope(func_name, curr_scope)) != NULL) {
		    if (temp->get_type() == var_LOCAL || temp->get_type() == var_FORMAL ||
			temp->get_type() == var_GLOBAL) {
			yyerror("ERROR:: Already assigned a variable with this name ");
		    } else if (temp->get_type() == func_USER) {
			yyerror("ERROR:: Already assigned a function with this name ");
		    }
		} else {
		    insert(func_name, curr_scope, yylineno, func_USER, true, currscopeoffset(),
			   currscopespace());
		    inccurrscopeoffset();
		    temp = lookUpScope(func_name, curr_scope);
		}
		if (temp == NULL) {
		    (yyval.expression) = NULL;
		} else {
		    (yyval.expression) = Symbol_to_Expr(temp);
		    /* $$->sym->taddress = nextquad(); */
		}
		emit(jump, NULL, NULL, NULL, 0, yylineno);
		functionjumpstack.push(nextquad());
		emit(funcstart, (yyval.expression), NULL, NULL, 0, yylineno);
		scopeoffsetstack.push(currscopeoffset());
		enterscopespace();
		reset_formalargoffset();
	}
#line 2326 "alpha_syntaxer.cpp"
    break;

  case 80: /* $@5: %empty  */
#line 717 "yyalpha.yacc"
                       {
	curr_scope++;
	push_Scope(BLOCK);
	}
#line 2335 "alpha_syntaxer.cpp"
    break;

  case 81: /* func_args: LEFT_PAREN $@5 idlist RIGHT_PAREN  */
#line 720 "yyalpha.yacc"
                             {
		curr_scope--;
		enterscopespace();
		pop_Scope();
		++inFunction;
		prev_block=FUNC;
		reset_functionlocaloffset();
			}
#line 2348 "alpha_syntaxer.cpp"
    break;

  case 82: /* func_body: block  */
#line 728 "yyalpha.yacc"
                {
		--inFunction;
		(yyval.intVal)= currscopeoffset();
		exitscopespace();
		}
#line 2358 "alpha_syntaxer.cpp"
    break;

  case 83: /* funcdef: func_prefix func_args func_body  */
#line 735 "yyalpha.yacc"
                                        {

		exitscopespace();
		(yyvsp[-2].expression)->sym->totalLocals = (yyvsp[0].intVal);
		int offset = scopeoffsetstack.top();
		scopeoffsetstack.pop();
 		restorecurrscopeoffset(offset); 
		(yyval.expression) = (yyvsp[-2].expression);
		emit(funcend, (yyval.expression), NULL, NULL , 0 ,yylineno);
		patchlabel(functionjumpstack.top()-1 , nextquad());
		backpatch(functionretstack.top() , nextquad()-1);
		functionjumpstack.pop();
		functionretstack.pop();
       }
#line 2377 "alpha_syntaxer.cpp"
    break;

  case 84: /* const: INTCONST  */
#line 750 "yyalpha.yacc"
                 { (yyval.expression) = newexpr_constnum((yyvsp[0].intVal)); }
#line 2383 "alpha_syntaxer.cpp"
    break;

  case 85: /* const: REALCONST  */
#line 751 "yyalpha.yacc"
                    { (yyval.expression) = newexpr_constnum((yyvsp[0].doubleVal)); }
#line 2389 "alpha_syntaxer.cpp"
    break;

  case 86: /* const: STRINGCONST  */
#line 752 "yyalpha.yacc"
                      { (yyval.expression) = newexpr_conststring((yyvsp[0].stringVal)); }
#line 2395 "alpha_syntaxer.cpp"
    break;

  case 87: /* const: NIL  */
#line 753 "yyalpha.yacc"
              {  (yyval.expression) = newexpr(nil_e);  }
#line 2401 "alpha_syntaxer.cpp"
    break;

  case 88: /* const: TRUE  */
#line 754 "yyalpha.yacc"
               {  (yyval.expression) = newexpr_constbool(true);  }
#line 2407 "alpha_syntaxer.cpp"
    break;

  case 89: /* const: FALSE  */
#line 755 "yyalpha.yacc"
                { (yyval.expression) = newexpr_constbool(false);  }
#line 2413 "alpha_syntaxer.cpp"
    break;

  case 90: /* $@6: %empty  */
#line 758 "yyalpha.yacc"
               { 

		SymbolTableEntry *temp;
		std::string var_name = yylval.stringVal;
		if ((temp = lookUpLIB(var_name)) != NULL) {
		    yyerror("ERROR:: Shadowing libfunc ");
		} else if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		    if (temp->get_type() == var_FORMAL) {
			yyerror("ERROR:: Formal argument already assigned ");
		    }
		} else {
		    insert(var_name, curr_scope, yylineno, var_FORMAL, true, currscopeoffset(),
			   currscopespace());
		    inccurrscopeoffset();
		}

	 	}
#line 2435 "alpha_syntaxer.cpp"
    break;

  case 93: /* $@7: %empty  */
#line 778 "yyalpha.yacc"
                     {

				SymbolTableEntry *temp;
				std::string var_name = yylval.stringVal;
				if ((temp = lookUpLIB(var_name)) != NULL) {
				    yyerror("ERROR:: Shadowing libfunc ");
				} else if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
				    if (temp->get_type() == var_FORMAL) {
					yyerror("ERROR:: Formal argument already assigned ");
				    }
				} else {
				    insert(var_name, curr_scope, yylineno, var_FORMAL, true, currscopeoffset(),
					   currscopespace());
				    inccurrscopeoffset();
				}

		}
#line 2457 "alpha_syntaxer.cpp"
    break;

  case 96: /* ifprefix: IF LEFT_PAREN expr RIGHT_PAREN  */
#line 798 "yyalpha.yacc"
                                         {

			backpatch((yyvsp[-1].expression)->falselist , nextquad()+2);
			backpatch((yyvsp[-1].expression)->truelist , nextquad());

if ((yyvsp[-1].expression)!=NULL && (yyvsp[-1].expression)->inLogical){
			(yyvsp[-1].expression) = newexpr(assignexpr_e);
			(yyvsp[-1].expression)->sym = new_temp();
			emit(assign , (yyvsp[-1].expression) , newexpr_constbool(true) , NULL ,  0 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , (yyvsp[-1].expression)  , newexpr_constbool(false) , NULL , 0 , yylineno);
}
			emit(if_eq, NULL, (yyvsp[-1].expression), newexpr_constbool(true),  nextquad()+2, yylineno);
			(yyval.intVal) = nextquad();
			emit(jump,NULL, NULL, NULL, 0, yylineno);
			/* isBackpatch = true; */
	}
#line 2479 "alpha_syntaxer.cpp"
    break;

  case 97: /* elseprefix: ELSE  */
#line 817 "yyalpha.yacc"
                {
				(yyval.intVal) = nextquad();
				emit(jump,NULL,NULL,NULL, 0, yylineno);
				}
#line 2488 "alpha_syntaxer.cpp"
    break;

  case 98: /* ifstmt: ifprefix stmt  */
#line 823 "yyalpha.yacc"
                      {
			patchlabel((yyvsp[-1].intVal), nextquad());
			}
#line 2496 "alpha_syntaxer.cpp"
    break;

  case 99: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 826 "yyalpha.yacc"
                                      {
					patchlabel((yyvsp[-3].intVal) , (yyvsp[-1].intVal) + 1);
					patchlabel((yyvsp[-1].intVal) , nextquad());
								}
#line 2505 "alpha_syntaxer.cpp"
    break;

  case 100: /* whilestart: WHILE  */
#line 832 "yyalpha.yacc"
                   {
					(yyval.intVal) = nextquad();
					loop_enter();
					}
#line 2514 "alpha_syntaxer.cpp"
    break;

  case 101: /* whilecond: LEFT_PAREN expr RIGHT_PAREN  */
#line 838 "yyalpha.yacc"
                                         {
				backpatch((yyvsp[-1].expression)->falselist, nextquad() + 2);
				backpatch((yyvsp[-1].expression)->truelist, nextquad());

if ((yyvsp[-1].expression)!=NULL && (yyvsp[-1].expression)->inLogical){
				(yyvsp[-1].expression) = newexpr(assignexpr_e);
				(yyvsp[-1].expression)->sym = new_temp();
				emit(assign, (yyvsp[-1].expression), newexpr_constbool(true), NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, nextquad() + 2, yylineno);
				emit(assign, (yyvsp[-1].expression), newexpr_constbool(false), NULL, 0, yylineno);
				}

				emit(if_eq,NULL, (yyvsp[-1].expression), newexpr_constbool(true),  nextquad() + 2, yylineno);
				(yyval.intVal) = nextquad();
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				prev_block = FLOW;
				/* isBackpatch = true; */
			}
#line 2537 "alpha_syntaxer.cpp"
    break;

  case 102: /* whilestmt: whilestart whilecond stmt  */
#line 859 "yyalpha.yacc"
        {
		emit(jump, NULL, NULL, NULL, (yyvsp[-2].intVal), yylineno);
		patchlabel((yyvsp[-1].intVal), nextquad());
		patch_break(nextquad());
		patch_cont((yyvsp[-2].intVal));
		loop_exit();
		//edw exi kanti me pathlist  dialeksi 11 telefteo slide
	}
#line 2550 "alpha_syntaxer.cpp"
    break;

  case 103: /* N: %empty  */
#line 868 "yyalpha.yacc"
   {(yyval.intVal) = nextquad(); emit(jump ,NULL , NULL , NULL , 0 , yylineno);

					prev_block=FLOW;
}
#line 2559 "alpha_syntaxer.cpp"
    break;

  case 104: /* M: %empty  */
#line 874 "yyalpha.yacc"
   {(yyval.intVal) = nextquad();}
#line 2565 "alpha_syntaxer.cpp"
    break;

  case 105: /* $@8: %empty  */
#line 877 "yyalpha.yacc"
               { loop_enter(); }
#line 2571 "alpha_syntaxer.cpp"
    break;

  case 106: /* forprefix: FOR $@8 LEFT_PAREN elist SEMICOLON M expr SEMICOLON  */
#line 877 "yyalpha.yacc"
                                                                                {
		if ((yyvsp[-1].expression)->inLogical && isBackpatch == 0) {
			backpatch((yyvsp[-1].expression)->falselist, nextquad() + 2);
			backpatch((yyvsp[-1].expression)->truelist, nextquad());
			(yyvsp[-1].expression)->sym = istempexpr((yyvsp[-1].expression)) ? (yyvsp[-1].expression)->sym : new_temp();
			emit(assign , (yyvsp[-1].expression) , newexpr_constbool(true) , NULL ,  0 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , (yyvsp[-1].expression)  , newexpr_constbool(false) , NULL , 0 , yylineno);
		}
				(yyval.forVal) = new forstruct();
				(yyval.forVal)->test = (yyvsp[-2].intVal);
				(yyval.forVal)->enter = nextquad();
		emit(if_eq,NULL , (yyvsp[-1].expression), newexpr_constbool(true),  0 , yylineno);
		isBackpatch = 0;
			}
#line 2591 "alpha_syntaxer.cpp"
    break;

  case 107: /* forstmt: forprefix N elist RIGHT_PAREN N stmt N  */
#line 893 "yyalpha.yacc"
                                                 {
		patchlabel((yyvsp[-6].forVal)->enter , (yyvsp[-2].intVal)+1); // true jumb
		patchlabel((yyvsp[-5].intVal) , nextquad());          //false jumb
		patchlabel((yyvsp[-2].intVal) , (yyvsp[-6].forVal)->test);    //loop jumb
		patchlabel((yyvsp[0].intVal) , (yyvsp[-5].intVal)+1);               //closure jumb
		patch_break(nextquad());
		patch_cont((yyvsp[-5].intVal)+1);
		loop_exit();
		// edw kati allo kani exra me patchlist dialeksi 11 telefteo slide
		}
#line 2606 "alpha_syntaxer.cpp"
    break;

  case 108: /* $@9: %empty  */
#line 905 "yyalpha.yacc"
                  { 
			if (inFunction == 0) {
			    yyerror("ERROR:: Return outside of function ");
			}
			isReturn = true;
		}
#line 2617 "alpha_syntaxer.cpp"
    break;

  case 109: /* returnstmt: RETURN $@9 expr SEMICOLON  */
#line 910 "yyalpha.yacc"
                                 {
			isReturn=false;  
			emit(ret , (yyvsp[-1].expression) , NULL ,NULL , 0 , yylineno); 
			emit(jump, NULL ,NULL ,NULL ,0 ,yylineno);
			functionretstack.top().push_back(nextquad()-1);
			}
#line 2628 "alpha_syntaxer.cpp"
    break;

  case 110: /* $@10: %empty  */
#line 916 "yyalpha.yacc"
                 { if(inFunction==0){ yyerror("ERROR:: Return outside of function "); } 
			}
#line 2635 "alpha_syntaxer.cpp"
    break;

  case 111: /* returnstmt: RETURN $@10 SEMICOLON  */
#line 917 "yyalpha.yacc"
                                    {
				emit(ret , NULL , NULL ,NULL , 0 , yylineno);
				emit(jump, NULL ,NULL ,NULL ,0 ,yylineno);
				functionretstack.top().push_back(nextquad()-1);
			}
#line 2645 "alpha_syntaxer.cpp"
    break;


#line 2649 "alpha_syntaxer.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 924 "yyalpha.yacc"

