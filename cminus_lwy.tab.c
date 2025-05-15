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
#line 1 "cminus_lwy.y"

    #include <iostream>
    #include <memory>
    #include <string>
    #include <vector>
    #include <cstring>
    #include "main.hpp"
    
    extern FILE* yyin;
    extern int yylex();
    extern int currentLine;
    
    // 全局变量
    std::shared_ptr<SyntaxTree> syntaxTree;
    bool analysisSuccessful = true;
    
    // 前向声明
    void yyerror(const char* msg);
    
    // 错误处理工具
    class SyntaxErrorHandler {
    private:
        static const int MAX_ERROR_MSG = 256;
        
    public:
        static void reportError(const char* msg, int line) {
            if (strstr(msg, "Missing") != nullptr || strstr(msg, "Unexpected") != nullptr) {
                fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
            } else if (strstr(msg, "syntax error") != nullptr) {
                // 提供更具体的错误消息
                extern char* yytext;
                if (yytext != nullptr) {
                    if (strcmp(yytext, "else") == 0) {
                        fprintf(stderr, "Error type B at Line %d: Missing ';' before 'else'\n", line);
                    } else if (strcmp(yytext, ",") == 0) {
                        fprintf(stderr, "Error type B at Line %d: Unexpected ',' in array indexing\n", line);
                    } else {
                        fprintf(stderr, "Error type B at Line %d: syntax error near '%s'\n", line, yytext);
                    }
                } else {
                    fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
                }
            } else {
                fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
            }
        }
    };
    
    // 节点构建器
    class NodeBuilder {
    public:
        static TreeNode* createNonTerminalNode(const char* name, int line) {
            return TreeNode::createNonTerminalNode(name, line);
        }
        
        static void addChild(TreeNode* parent, TreeNode* child) {
            if (parent && child) {
                parent->addChild(child);
            }
        }
        
        static int updateNodeLine(TreeNode* node) {
            if (!node) return INT_MAX;
            if (node->children.empty()) return node->line;
            
            int minLine = node->line;
            for (auto child : node->children) {
                if (child) {
                    minLine = std::min(minLine, child->line);
                }
            }
            node->line = minLine;
            return minLine;
        }
    };

#line 148 "cminus_lwy.tab.c"

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

#include "cminus_lwy.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_STRUCT = 7,                     /* STRUCT  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_SEMI = 12,                      /* SEMI  */
  YYSYMBOL_COMMA = 13,                     /* COMMA  */
  YYSYMBOL_ASSIGNOP = 14,                  /* ASSIGNOP  */
  YYSYMBOL_RELOP = 15,                     /* RELOP  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_STAR = 18,                      /* STAR  */
  YYSYMBOL_DIV = 19,                       /* DIV  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_DOT = 23,                       /* DOT  */
  YYSYMBOL_LP = 24,                        /* LP  */
  YYSYMBOL_RP = 25,                        /* RP  */
  YYSYMBOL_LB = 26,                        /* LB  */
  YYSYMBOL_RB = 27,                        /* RB  */
  YYSYMBOL_LC = 28,                        /* LC  */
  YYSYMBOL_RC = 29,                        /* RC  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_ErrorSemi = 32,                 /* ErrorSemi  */
  YYSYMBOL_ErrorRP = 33,                   /* ErrorRP  */
  YYSYMBOL_ErrorRB = 34,                   /* ErrorRB  */
  YYSYMBOL_ErrorRC = 35,                   /* ErrorRC  */
  YYSYMBOL_Program = 36,                   /* Program  */
  YYSYMBOL_ExtDefList = 37,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 38,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 39,                /* ExtDecList  */
  YYSYMBOL_Specifier = 40,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 41,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 42,                    /* OptTag  */
  YYSYMBOL_Tag = 43,                       /* Tag  */
  YYSYMBOL_VarDec = 44,                    /* VarDec  */
  YYSYMBOL_FunDec = 45,                    /* FunDec  */
  YYSYMBOL_VarList = 46,                   /* VarList  */
  YYSYMBOL_ParamDec = 47,                  /* ParamDec  */
  YYSYMBOL_CompSt = 48,                    /* CompSt  */
  YYSYMBOL_StmtList = 49,                  /* StmtList  */
  YYSYMBOL_Stmt = 50,                      /* Stmt  */
  YYSYMBOL_DefList = 51,                   /* DefList  */
  YYSYMBOL_Def = 52,                       /* Def  */
  YYSYMBOL_DecList = 53,                   /* DecList  */
  YYSYMBOL_Dec = 54,                       /* Dec  */
  YYSYMBOL_Exp = 55,                       /* Exp  */
  YYSYMBOL_Args = 56                       /* Args  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   253

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   123,   129,   134,   140,   145,   151,   156,
     163,   172,   180,   185,   193,   200,   210,   216,   227,   233,
     241,   251,   260,   267,   272,   281,   287,   298,   307,   317,
     325,   333,   343,   354,   362,   367,   374,   380,   388,   398,
     410,   420,   437,   445,   450,   460,   466,   476,   482,   493,
     501,   509,   517,   525,   533,   541,   549,   557,   565,   572,
     579,   588,   596,   605,   613,   619,   625,   631,   644,   652
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "TYPE", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "NOT",
  "DOT", "LP", "RP", "LB", "RB", "LC", "RC", "LOWER_THAN_ELSE", "$accept",
  "ErrorSemi", "ErrorRP", "ErrorRB", "ErrorRC", "Program", "ExtDefList",
  "ExtDef", "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      45,   -58,    -2,    18,   -58,    45,    42,   -58,    -5,    16,
     -58,   -58,   -58,    46,    38,   -58,   -58,    36,    29,    41,
      45,   -58,    15,   -58,    59,    70,    45,   -58,    59,     9,
      45,    49,   -58,   -58,    59,    11,    73,   -58,   -58,    14,
     150,    -1,    36,    75,    63,   -58,   -58,   -58,   -58,    68,
     -58,    45,    66,   -58,   -58,   -58,   -58,    88,   165,    91,
      94,   165,   165,   165,   -58,     9,   150,   105,   165,   -58,
      59,   -58,   -58,   -58,   159,   105,   165,   165,    90,    23,
     126,   -58,   -58,   165,   165,   165,   165,   165,   165,   165,
     165,   109,   165,   -58,   204,   -58,   -58,   177,    11,   -58,
     126,   126,   -58,   204,   227,    90,    90,    23,    23,    64,
     216,   -58,    84,   165,   -58,   150,   150,   165,   -58,   -58,
      67,   -58,   190,   150,   150,   -58,   -58,   -58
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      12,    18,    23,     0,    10,    12,     0,    19,    24,     0,
      21,     1,    11,     0,    25,     3,    14,     0,    16,     0,
      43,     2,     0,    13,     0,     0,    43,    15,     0,     0,
      43,     0,     5,    28,     0,     0,    30,    25,    17,     0,
      34,    47,     0,    45,     0,     9,    20,    42,     4,    31,
      27,     0,     0,     7,    26,    65,    66,    64,     0,     0,
       0,     0,     0,     0,    36,     0,    34,     0,     0,    44,
       0,     8,    29,     6,     0,     0,     0,     0,    58,    59,
       0,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    48,    46,    61,    69,     0,    37,
       0,     0,    57,    49,    52,    53,    54,    55,    56,    50,
      51,    63,     0,     0,    60,     0,     0,     0,    62,    68,
       0,    40,     0,     0,     0,    67,    41,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,    -8,   -35,    17,    65,   -58,   127,   -58,   110,     2,
     -58,   -58,   -58,   -20,   -58,    82,   -58,   116,    71,   125,
      31,   -58,    69,   -58,   -57,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    16,    33,    54,    46,     3,     4,     5,    17,    28,
       7,     9,    10,    18,    19,    35,    36,    64,    65,    66,
      29,    30,    42,    43,    67,    98
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    75,     6,     8,    78,    79,    80,     6,    41,    23,
      44,    94,    31,    68,    49,    52,    31,    97,    11,   100,
     101,     1,     2,   -22,    34,    25,   103,   104,   105,   106,
     107,   108,   109,   110,    69,   112,    32,    13,    45,    96,
      32,    53,    24,    13,    20,   102,    91,    14,    15,    92,
      41,     1,     2,    34,    15,    25,    97,    40,    21,    93,
     122,    47,    22,   114,    37,   115,   116,    99,   123,    26,
     -38,   -38,   -38,    39,    48,   -38,   -38,   124,   -38,    84,
      85,    86,    87,    88,   -38,    52,    51,    91,    70,   -38,
      92,   -38,    71,    73,    25,   -38,   -38,   117,    83,    84,
      85,    86,    87,    88,    89,    90,    13,    91,    87,    88,
      92,    53,    74,    91,   111,    76,    92,    15,    77,    83,
      84,    85,    86,    87,    88,    89,    90,    31,    91,   118,
      81,    92,    12,    72,    38,    27,     0,    82,   119,    95,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    91,
       0,    32,    92,    55,    56,    57,     0,     0,    58,    59,
      31,    60,    55,    56,    57,     0,     0,    61,    55,    56,
      57,     0,    62,     0,    63,     0,    61,     0,    26,     0,
       0,    62,    61,    63,    32,     0,     0,    62,     0,    63,
     113,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,     0,     0,    92,    83,    84,    85,    86,    87,    88,
      89,    90,     0,    91,     0,     0,    92,   125,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,     0,     0,
      92,    84,    85,    86,    87,    88,    89,     0,     0,    91,
     120,   121,    92,    85,    86,    87,    88,     0,   126,   127,
      91,     0,     0,    92
};

static const yytype_int8 yycheck[] =
{
      35,    58,     0,     5,    61,    62,    63,     5,    28,    17,
       1,    68,     1,    14,    34,     1,     1,    74,     0,    76,
      77,     6,     7,    28,    22,    26,    83,    84,    85,    86,
      87,    88,    89,    90,    42,    92,    25,     1,    29,    74,
      25,    27,    13,     1,    28,    80,    23,     5,    12,    26,
      70,     6,     7,    51,    12,    26,   113,    26,    12,    67,
     117,    30,    24,    98,     5,   100,   101,    75,     1,    28,
       3,     4,     5,     3,    25,     8,     9,    10,    11,    15,
      16,    17,    18,    19,    17,     1,    13,    23,    13,    22,
      26,    24,    29,    27,    26,    28,    29,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     1,    23,    18,    19,
      26,    27,    24,    23,     5,    24,    26,    12,    24,    14,
      15,    16,    17,    18,    19,    20,    21,     1,    23,   112,
      65,    26,     5,    51,    24,    19,    -1,    66,   113,    70,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    23,
      -1,    25,    26,     3,     4,     5,    -1,    -1,     8,     9,
       1,    11,     3,     4,     5,    -1,    -1,    17,     3,     4,
       5,    -1,    22,    -1,    24,    -1,    17,    -1,    28,    -1,
      -1,    22,    17,    24,    25,    -1,    -1,    22,    -1,    24,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    -1,
      23,    -1,    -1,    26,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    -1,    -1,    26,    27,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    23,    -1,    -1,
      26,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
     115,   116,    26,    16,    17,    18,    19,    -1,   123,   124,
      23,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,    36,    37,    38,    40,    41,     5,    42,
      43,     0,    37,     1,     5,    12,    32,    39,    44,    45,
      28,    12,    24,    32,    13,    26,    28,    48,    40,    51,
      52,     1,    25,    33,    40,    46,    47,     5,    39,     3,
      51,    44,    53,    54,     1,    29,    35,    51,    25,    44,
      33,    13,     1,    27,    34,     3,     4,     5,     8,     9,
      11,    17,    22,    24,    48,    49,    50,    55,    14,    32,
      13,    29,    46,    27,    24,    55,    24,    24,    55,    55,
      55,    35,    49,    14,    15,    16,    17,    18,    19,    20,
      21,    23,    26,    32,    55,    53,    33,    55,    56,    32,
      55,    55,    33,    55,    55,    55,    55,    55,    55,    55,
      55,     5,    55,    13,    33,    33,    33,    13,    34,    56,
      50,    50,    55,     1,    10,    27,    50,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    34,    34,    35,    35,
      36,    37,    37,    38,    38,    38,    39,    39,    40,    40,
      41,    41,    42,    42,    43,    44,    44,    45,    45,    46,
      46,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    51,    51,    52,    53,    53,    54,    54,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     2,     1,     2,     1,
       1,     2,     0,     3,     2,     3,     1,     3,     1,     1,
       5,     2,     1,     0,     1,     1,     4,     4,     3,     3,
       1,     2,     4,     2,     0,     2,     1,     3,     5,     7,
       5,     7,     2,     0,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     4,     3,     1,     1,     1,     6,     3,     1
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
  case 2: /* ErrorSemi: error SEMI  */
#line 119 "cminus_lwy.y"
             { 
                SyntaxErrorHandler::reportError("Missing or invalid token before ';'", currentLine);
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1297 "cminus_lwy.tab.c"
    break;

  case 3: /* ErrorSemi: SEMI  */
#line 124 "cminus_lwy.y"
             { 
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1305 "cminus_lwy.tab.c"
    break;

  case 4: /* ErrorRP: error RP  */
#line 130 "cminus_lwy.y"
             { 
                SyntaxErrorHandler::reportError("Missing or invalid expression in parentheses", currentLine);
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1314 "cminus_lwy.tab.c"
    break;

  case 5: /* ErrorRP: RP  */
#line 135 "cminus_lwy.y"
             { 
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1322 "cminus_lwy.tab.c"
    break;

  case 6: /* ErrorRB: error RB  */
#line 141 "cminus_lwy.y"
             { 
                SyntaxErrorHandler::reportError("Missing or invalid expression in square brackets", currentLine);
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1331 "cminus_lwy.tab.c"
    break;

  case 7: /* ErrorRB: RB  */
#line 146 "cminus_lwy.y"
             { 
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1339 "cminus_lwy.tab.c"
    break;

  case 8: /* ErrorRC: error RC  */
#line 152 "cminus_lwy.y"
             { 
                SyntaxErrorHandler::reportError("Missing or invalid declaration in block", currentLine);
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1348 "cminus_lwy.tab.c"
    break;

  case 9: /* ErrorRC: RC  */
#line 157 "cminus_lwy.y"
             { 
                (yyval.node) = (yyvsp[0].node); 
             }
#line 1356 "cminus_lwy.tab.c"
    break;

  case 10: /* Program: ExtDefList  */
#line 164 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Program", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
                syntaxTree->setRoot((yyval.node));
             }
#line 1367 "cminus_lwy.tab.c"
    break;

  case 11: /* ExtDefList: ExtDef ExtDefList  */
#line 173 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDefList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1378 "cminus_lwy.tab.c"
    break;

  case 12: /* ExtDefList: %empty  */
#line 180 "cminus_lwy.y"
             {
                (yyval.node) = nullptr;
             }
#line 1386 "cminus_lwy.tab.c"
    break;

  case 13: /* ExtDef: Specifier ExtDecList ErrorSemi  */
#line 186 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1398 "cminus_lwy.tab.c"
    break;

  case 14: /* ExtDef: Specifier ErrorSemi  */
#line 194 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1409 "cminus_lwy.tab.c"
    break;

  case 15: /* ExtDef: Specifier FunDec CompSt  */
#line 201 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1421 "cminus_lwy.tab.c"
    break;

  case 16: /* ExtDecList: VarDec  */
#line 211 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDecList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1431 "cminus_lwy.tab.c"
    break;

  case 17: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 217 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ExtDecList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1443 "cminus_lwy.tab.c"
    break;

  case 18: /* Specifier: TYPE  */
#line 228 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Specifier", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1453 "cminus_lwy.tab.c"
    break;

  case 19: /* Specifier: StructSpecifier  */
#line 234 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Specifier", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1463 "cminus_lwy.tab.c"
    break;

  case 20: /* StructSpecifier: STRUCT OptTag LC DefList ErrorRC  */
#line 242 "cminus_lwy.y"
                {
                   (yyval.node) = NodeBuilder::createNonTerminalNode("StructSpecifier", currentLine);
                   NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                   NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                   NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                   NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                   NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                   NodeBuilder::updateNodeLine((yyval.node));
                }
#line 1477 "cminus_lwy.tab.c"
    break;

  case 21: /* StructSpecifier: STRUCT Tag  */
#line 252 "cminus_lwy.y"
                {
                   (yyval.node) = NodeBuilder::createNonTerminalNode("StructSpecifier", currentLine);
                   NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                   NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                   NodeBuilder::updateNodeLine((yyval.node));
                }
#line 1488 "cminus_lwy.tab.c"
    break;

  case 22: /* OptTag: ID  */
#line 261 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("OptTag", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1498 "cminus_lwy.tab.c"
    break;

  case 23: /* OptTag: %empty  */
#line 267 "cminus_lwy.y"
             {
                (yyval.node) = nullptr;
             }
#line 1506 "cminus_lwy.tab.c"
    break;

  case 24: /* Tag: ID  */
#line 273 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Tag", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1516 "cminus_lwy.tab.c"
    break;

  case 25: /* VarDec: ID  */
#line 282 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("VarDec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1526 "cminus_lwy.tab.c"
    break;

  case 26: /* VarDec: VarDec LB INT ErrorRB  */
#line 288 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("VarDec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1539 "cminus_lwy.tab.c"
    break;

  case 27: /* FunDec: ID LP VarList ErrorRP  */
#line 299 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("FunDec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1552 "cminus_lwy.tab.c"
    break;

  case 28: /* FunDec: ID LP ErrorRP  */
#line 308 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("FunDec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1564 "cminus_lwy.tab.c"
    break;

  case 29: /* VarList: ParamDec COMMA VarList  */
#line 318 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("VarList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1576 "cminus_lwy.tab.c"
    break;

  case 30: /* VarList: ParamDec  */
#line 326 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("VarList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1586 "cminus_lwy.tab.c"
    break;

  case 31: /* ParamDec: Specifier VarDec  */
#line 334 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("ParamDec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1597 "cminus_lwy.tab.c"
    break;

  case 32: /* CompSt: LC DefList StmtList ErrorRC  */
#line 344 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("CompSt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1610 "cminus_lwy.tab.c"
    break;

  case 33: /* StmtList: Stmt StmtList  */
#line 355 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("StmtList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1621 "cminus_lwy.tab.c"
    break;

  case 34: /* StmtList: %empty  */
#line 362 "cminus_lwy.y"
             {
                (yyval.node) = nullptr;
             }
#line 1629 "cminus_lwy.tab.c"
    break;

  case 35: /* Stmt: Exp ErrorSemi  */
#line 368 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1640 "cminus_lwy.tab.c"
    break;

  case 36: /* Stmt: CompSt  */
#line 375 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1650 "cminus_lwy.tab.c"
    break;

  case 37: /* Stmt: RETURN Exp ErrorSemi  */
#line 381 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1662 "cminus_lwy.tab.c"
    break;

  case 38: /* Stmt: IF LP Exp ErrorRP Stmt  */
#line 389 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1676 "cminus_lwy.tab.c"
    break;

  case 39: /* Stmt: IF LP Exp ErrorRP Stmt ELSE Stmt  */
#line 399 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-6].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-5].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1692 "cminus_lwy.tab.c"
    break;

  case 40: /* Stmt: WHILE LP Exp ErrorRP Stmt  */
#line 411 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1706 "cminus_lwy.tab.c"
    break;

  case 41: /* Stmt: IF LP Exp ErrorRP Stmt error Stmt  */
#line 421 "cminus_lwy.y"
             {
                analysisSuccessful = false;
                SyntaxErrorHandler::reportError("Missing ';' before 'else'", currentLine);
                
                (yyval.node) = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-6].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-5].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1724 "cminus_lwy.tab.c"
    break;

  case 42: /* DefList: Def DefList  */
#line 438 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("DefList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1735 "cminus_lwy.tab.c"
    break;

  case 43: /* DefList: %empty  */
#line 445 "cminus_lwy.y"
             {
                (yyval.node) = nullptr;
             }
#line 1743 "cminus_lwy.tab.c"
    break;

  case 44: /* Def: Specifier DecList ErrorSemi  */
#line 451 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Def", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1755 "cminus_lwy.tab.c"
    break;

  case 45: /* DecList: Dec  */
#line 461 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("DecList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1765 "cminus_lwy.tab.c"
    break;

  case 46: /* DecList: Dec COMMA DecList  */
#line 467 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("DecList", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1777 "cminus_lwy.tab.c"
    break;

  case 47: /* Dec: VarDec  */
#line 477 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Dec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1787 "cminus_lwy.tab.c"
    break;

  case 48: /* Dec: VarDec ASSIGNOP Exp  */
#line 483 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Dec", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1799 "cminus_lwy.tab.c"
    break;

  case 49: /* Exp: Exp ASSIGNOP Exp  */
#line 494 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1811 "cminus_lwy.tab.c"
    break;

  case 50: /* Exp: Exp AND Exp  */
#line 502 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1823 "cminus_lwy.tab.c"
    break;

  case 51: /* Exp: Exp OR Exp  */
#line 510 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1835 "cminus_lwy.tab.c"
    break;

  case 52: /* Exp: Exp RELOP Exp  */
#line 518 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1847 "cminus_lwy.tab.c"
    break;

  case 53: /* Exp: Exp PLUS Exp  */
#line 526 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1859 "cminus_lwy.tab.c"
    break;

  case 54: /* Exp: Exp MINUS Exp  */
#line 534 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1871 "cminus_lwy.tab.c"
    break;

  case 55: /* Exp: Exp STAR Exp  */
#line 542 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1883 "cminus_lwy.tab.c"
    break;

  case 56: /* Exp: Exp DIV Exp  */
#line 550 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1895 "cminus_lwy.tab.c"
    break;

  case 57: /* Exp: LP Exp ErrorRP  */
#line 558 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1907 "cminus_lwy.tab.c"
    break;

  case 58: /* Exp: MINUS Exp  */
#line 566 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1918 "cminus_lwy.tab.c"
    break;

  case 59: /* Exp: NOT Exp  */
#line 573 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1929 "cminus_lwy.tab.c"
    break;

  case 60: /* Exp: ID LP Args ErrorRP  */
#line 580 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1942 "cminus_lwy.tab.c"
    break;

  case 61: /* Exp: ID LP ErrorRP  */
#line 589 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1954 "cminus_lwy.tab.c"
    break;

  case 62: /* Exp: Exp LB Exp ErrorRB  */
#line 597 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1967 "cminus_lwy.tab.c"
    break;

  case 63: /* Exp: Exp DOT ID  */
#line 606 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1979 "cminus_lwy.tab.c"
    break;

  case 64: /* Exp: ID  */
#line 614 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1989 "cminus_lwy.tab.c"
    break;

  case 65: /* Exp: INT  */
#line 620 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 1999 "cminus_lwy.tab.c"
    break;

  case 66: /* Exp: FLOAT  */
#line 626 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 2009 "cminus_lwy.tab.c"
    break;

  case 67: /* Exp: Exp LB Exp COMMA Exp RB  */
#line 632 "cminus_lwy.y"
             {
                analysisSuccessful = false;
                SyntaxErrorHandler::reportError("Unexpected ',' in array indexing, did you mean '][' ?", currentLine);
                
                (yyval.node) = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-5].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-4].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-3].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 2024 "cminus_lwy.tab.c"
    break;

  case 68: /* Args: Exp COMMA Args  */
#line 645 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Args", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[-2].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[-1].node));
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 2036 "cminus_lwy.tab.c"
    break;

  case 69: /* Args: Exp  */
#line 653 "cminus_lwy.y"
             {
                (yyval.node) = NodeBuilder::createNonTerminalNode("Args", currentLine);
                NodeBuilder::addChild((yyval.node), (yyvsp[0].node));
                NodeBuilder::updateNodeLine((yyval.node));
             }
#line 2046 "cminus_lwy.tab.c"
    break;


#line 2050 "cminus_lwy.tab.c"

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

#line 660 "cminus_lwy.y"


void yyerror(const char* msg) {
    // 由SyntaxErrorHandler处理具体错误报告
    analysisSuccessful = false;
    SyntaxErrorHandler::reportError(msg, currentLine);
}
