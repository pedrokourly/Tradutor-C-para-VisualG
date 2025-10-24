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
#line 1 "src/parser.y"

    #include "symbol.h" // Inclua o arquivo de cabeçalho para a tabela de símbolos
    #include <stdio.h>  // Adicionado para FILE*
    #include <stdlib.h> // Adicionado para malloc/exit
    #include <string.h> // Adicionado para strdup/strcmp

    // Definição da estrutura para a tabela de símbolos
    Simbolo * symbol_table = NULL; // Ponteiro para a tabela de símbolos

    int current_scope = 0; // 0 = global, 1 = local
    
    void yyerror(const char *s); // Declaração da função de erro do Bison
    extern int yylex(void); // Declaração da função do scanner, gerada pelo Flex
    extern FILE *yyin;      // Para definir o arquivo de entrada
    extern char *yytext;    // Para acessar o texto do token atual
    extern int yylineno;    // Para rastrear o número da linha
    
    // Funções que são usadas antes de serem definidas no final do arquivo
    Simbolo* create_param(char *name, int type);
    void insert_function(char *name, int return_type, Simbolo *params);
    void insert_symbol(char *name, int type);
    Simbolo *find_symbol(char *name);
    Simbolo *find_symbol_in_scope(char *name, int scope);
    const char* type_to_string(int type);
    void print_symbol_table();

#line 98 "bin/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_FLOAT_LITERAL = 5,              /* FLOAT_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 6,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_INTEIRO = 8,                    /* INTEIRO  */
  YYSYMBOL_REAL = 9,                       /* REAL  */
  YYSYMBOL_CARACTER = 10,                  /* CARACTER  */
  YYSYMBOL_LITERAL = 11,                   /* LITERAL  */
  YYSYMBOL_LOGICO = 12,                    /* LOGICO  */
  YYSYMBOL_VERDADEIRO = 13,                /* VERDADEIRO  */
  YYSYMBOL_FALSO = 14,                     /* FALSO  */
  YYSYMBOL_SE = 15,                        /* SE  */
  YYSYMBOL_ENTAO = 16,                     /* ENTAO  */
  YYSYMBOL_SENAO = 17,                     /* SENAO  */
  YYSYMBOL_FIMSE = 18,                     /* FIMSE  */
  YYSYMBOL_ENQUANTO = 19,                  /* ENQUANTO  */
  YYSYMBOL_FACA = 20,                      /* FACA  */
  YYSYMBOL_FIMENQUANTO = 21,               /* FIMENQUANTO  */
  YYSYMBOL_REPITA = 22,                    /* REPITA  */
  YYSYMBOL_ATE = 23,                       /* ATE  */
  YYSYMBOL_PARA = 24,                      /* PARA  */
  YYSYMBOL_DE = 25,                        /* DE  */
  YYSYMBOL_PASSO = 26,                     /* PASSO  */
  YYSYMBOL_FIMPARA = 27,                   /* FIMPARA  */
  YYSYMBOL_ESCOLHA = 28,                   /* ESCOLHA  */
  YYSYMBOL_CASO = 29,                      /* CASO  */
  YYSYMBOL_OUTROCASO = 30,                 /* OUTROCASO  */
  YYSYMBOL_FIMESCOLHA = 31,                /* FIMESCOLHA  */
  YYSYMBOL_INTERROMPA = 32,                /* INTERROMPA  */
  YYSYMBOL_RETORNE = 33,                   /* RETORNE  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_TIMES = 36,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 37,                    /* DIVIDE  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_EQUAL = 39,                     /* EQUAL  */
  YYSYMBOL_NEQ = 40,                       /* NEQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LTE = 43,                       /* LTE  */
  YYSYMBOL_GTE = 44,                       /* GTE  */
  YYSYMBOL_INT_DIVIDE = 45,                /* INT_DIVIDE  */
  YYSYMBOL_POWER = 46,                     /* POWER  */
  YYSYMBOL_E = 47,                         /* E  */
  YYSYMBOL_OU = 48,                        /* OU  */
  YYSYMBOL_NAO = 49,                       /* NAO  */
  YYSYMBOL_XOU = 50,                       /* XOU  */
  YYSYMBOL_LPAREN = 51,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 52,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 53,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 54,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 55,                     /* COMMA  */
  YYSYMBOL_COLON = 56,                     /* COLON  */
  YYSYMBOL_ALGORITMO = 57,                 /* ALGORITMO  */
  YYSYMBOL_FIMALGORITMO = 58,              /* FIMALGORITMO  */
  YYSYMBOL_VAR = 59,                       /* VAR  */
  YYSYMBOL_INICIO = 60,                    /* INICIO  */
  YYSYMBOL_FUNCAO = 61,                    /* FUNCAO  */
  YYSYMBOL_FIMFUNCAO = 62,                 /* FIMFUNCAO  */
  YYSYMBOL_PROCEDIMENTO = 63,              /* PROCEDIMENTO  */
  YYSYMBOL_FIMPROCEDIMENTO = 64,           /* FIMPROCEDIMENTO  */
  YYSYMBOL_LEIA = 65,                      /* LEIA  */
  YYSYMBOL_ESCREVA = 66,                   /* ESCREVA  */
  YYSYMBOL_ESCREVAL = 67,                  /* ESCREVAL  */
  YYSYMBOL_ALEATORIO = 68,                 /* ALEATORIO  */
  YYSYMBOL_ABS = 69,                       /* ABS  */
  YYSYMBOL_ARCCOS = 70,                    /* ARCCOS  */
  YYSYMBOL_ARCSEN = 71,                    /* ARCSEN  */
  YYSYMBOL_ARCTAN = 72,                    /* ARCTAN  */
  YYSYMBOL_ARQUIVO = 73,                   /* ARQUIVO  */
  YYSYMBOL_ASC = 74,                       /* ASC  */
  YYSYMBOL_COMPR = 75,                     /* COMPR  */
  YYSYMBOL_COPIA = 76,                     /* COPIA  */
  YYSYMBOL_COS = 77,                       /* COS  */
  YYSYMBOL_COTAN = 78,                     /* COTAN  */
  YYSYMBOL_CRONOMETRO = 79,                /* CRONOMETRO  */
  YYSYMBOL_DEBUG = 80,                     /* DEBUG  */
  YYSYMBOL_ECO = 81,                       /* ECO  */
  YYSYMBOL_EXP = 82,                       /* EXP  */
  YYSYMBOL_GRAUPRAD = 83,                  /* GRAUPRAD  */
  YYSYMBOL_INT_FUNC = 84,                  /* INT_FUNC  */
  YYSYMBOL_LOG = 85,                       /* LOG  */
  YYSYMBOL_LOGN = 86,                      /* LOGN  */
  YYSYMBOL_MAIUSC = 87,                    /* MAIUSC  */
  YYSYMBOL_MINUSC = 88,                    /* MINUSC  */
  YYSYMBOL_NUMPCARAC = 89,                 /* NUMPCARAC  */
  YYSYMBOL_PAUSA = 90,                     /* PAUSA  */
  YYSYMBOL_PI = 91,                        /* PI  */
  YYSYMBOL_POS = 92,                       /* POS  */
  YYSYMBOL_QUAD = 93,                      /* QUAD  */
  YYSYMBOL_RADPGRAU = 94,                  /* RADPGRAU  */
  YYSYMBOL_RAIZQ = 95,                     /* RAIZQ  */
  YYSYMBOL_RAND = 96,                      /* RAND  */
  YYSYMBOL_RANDI = 97,                     /* RANDI  */
  YYSYMBOL_SEN = 98,                       /* SEN  */
  YYSYMBOL_TIMER = 99,                     /* TIMER  */
  YYSYMBOL_TAN = 100,                      /* TAN  */
  YYSYMBOL_UMINUS = 101,                   /* UMINUS  */
  YYSYMBOL_YYACCEPT = 102,                 /* $accept  */
  YYSYMBOL_program = 103,                  /* program  */
  YYSYMBOL_declaracao_variaveis = 104,     /* declaracao_variaveis  */
  YYSYMBOL_variable_declaration_list = 105, /* variable_declaration_list  */
  YYSYMBOL_variable_declaration = 106,     /* variable_declaration  */
  YYSYMBOL_identifier_list = 107,          /* identifier_list  */
  YYSYMBOL_declaracao_subrotinas = 108,    /* declaracao_subrotinas  */
  YYSYMBOL_type_specifier = 109,           /* type_specifier  */
  YYSYMBOL_parameter_list = 110,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 111,    /* parameter_declaration  */
  YYSYMBOL_function_declaration = 112,     /* function_declaration  */
  YYSYMBOL_113_1 = 113,                    /* $@1  */
  YYSYMBOL_procedure_declaration = 114,    /* procedure_declaration  */
  YYSYMBOL_115_2 = 115,                    /* $@2  */
  YYSYMBOL_statement_list = 116,           /* statement_list  */
  YYSYMBOL_statement = 117,                /* statement  */
  YYSYMBOL_io_statement = 118,             /* io_statement  */
  YYSYMBOL_write_list = 119,               /* write_list  */
  YYSYMBOL_write_parameter = 120,          /* write_parameter  */
  YYSYMBOL_expression_list = 121,          /* expression_list  */
  YYSYMBOL_if_statement = 122,             /* if_statement  */
  YYSYMBOL_while_statement = 123,          /* while_statement  */
  YYSYMBOL_repita_statement = 124,         /* repita_statement  */
  YYSYMBOL_para_statement = 125,           /* para_statement  */
  YYSYMBOL_escolha_statement = 126,        /* escolha_statement  */
  YYSYMBOL_caso_list = 127,                /* caso_list  */
  YYSYMBOL_outrocaso_block = 128,          /* outrocaso_block  */
  YYSYMBOL_expression = 129,               /* expression  */
  YYSYMBOL_assignment_statement = 130,     /* assignment_statement  */
  YYSYMBOL_logical_or_expression = 131,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 132,   /* logical_and_expression  */
  YYSYMBOL_relational_expression = 133,    /* relational_expression  */
  YYSYMBOL_additive_expression = 134,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 135, /* multiplicative_expression  */
  YYSYMBOL_power_expression = 136,         /* power_expression  */
  YYSYMBOL_unary_expression = 137,         /* unary_expression  */
  YYSYMBOL_primary_expression = 138        /* primary_expression  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   590

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   356


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   113,   115,   119,   120,   125,   142,   146,
     158,   160,   161,   166,   167,   168,   169,   170,   175,   176,
     177,   188,   199,   198,   226,   225,   251,   253,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   270,   271,   272,
     273,   274,   275,   283,   284,   288,   289,   290,   297,   298,
     303,   306,   315,   322,   329,   332,   339,   345,   347,   351,
     353,   360,   361,   365,   380,   381,   382,   386,   387,   391,
     392,   393,   394,   395,   396,   397,   401,   402,   403,   407,
     408,   409,   410,   414,   415,   419,   420,   421,   425,   426,
     427,   428,   429,   430,   431,   439,   440,   441
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "NUMBER",
  "FLOAT_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "INTEIRO", "REAL",
  "CARACTER", "LITERAL", "LOGICO", "VERDADEIRO", "FALSO", "SE", "ENTAO",
  "SENAO", "FIMSE", "ENQUANTO", "FACA", "FIMENQUANTO", "REPITA", "ATE",
  "PARA", "DE", "PASSO", "FIMPARA", "ESCOLHA", "CASO", "OUTROCASO",
  "FIMESCOLHA", "INTERROMPA", "RETORNE", "PLUS", "MINUS", "TIMES",
  "DIVIDE", "ASSIGN", "EQUAL", "NEQ", "LT", "GT", "LTE", "GTE",
  "INT_DIVIDE", "POWER", "E", "OU", "NAO", "XOU", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "COMMA", "COLON", "ALGORITMO", "FIMALGORITMO",
  "VAR", "INICIO", "FUNCAO", "FIMFUNCAO", "PROCEDIMENTO",
  "FIMPROCEDIMENTO", "LEIA", "ESCREVA", "ESCREVAL", "ALEATORIO", "ABS",
  "ARCCOS", "ARCSEN", "ARCTAN", "ARQUIVO", "ASC", "COMPR", "COPIA", "COS",
  "COTAN", "CRONOMETRO", "DEBUG", "ECO", "EXP", "GRAUPRAD", "INT_FUNC",
  "LOG", "LOGN", "MAIUSC", "MINUSC", "NUMPCARAC", "PAUSA", "PI", "POS",
  "QUAD", "RADPGRAU", "RAIZQ", "RAND", "RANDI", "SEN", "TIMER", "TAN",
  "UMINUS", "$accept", "program", "declaracao_variaveis",
  "variable_declaration_list", "variable_declaration", "identifier_list",
  "declaracao_subrotinas", "type_specifier", "parameter_list",
  "parameter_declaration", "function_declaration", "$@1",
  "procedure_declaration", "$@2", "statement_list", "statement",
  "io_statement", "write_list", "write_parameter", "expression_list",
  "if_statement", "while_statement", "repita_statement", "para_statement",
  "escolha_statement", "caso_list", "outrocaso_block", "expression",
  "assignment_statement", "logical_or_expression",
  "logical_and_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "power_expression", "unary_expression",
  "primary_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-131)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -49,    10,    53,   -32,  -131,    55,  -131,  -131,    55,  -131,
      67,    41,  -131,    60,   214,  -131,    74,    88,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,   146,    21,    56,
     -35,  -131,  -131,  -131,  -131,  -131,  -131,   440,   440,  -131,
      96,   440,  -131,   440,   440,   440,   440,  -131,    68,   107,
     111,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
      87,    65,    90,   105,    20,  -131,    95,  -131,   160,   160,
     539,    15,   113,   -12,     4,   186,   141,    87,    87,  -131,
    -131,    48,    55,    76,   346,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     115,   -29,  -131,    32,  -131,  -131,    54,    87,  -131,  -131,
     440,   440,   114,  -131,    61,  -131,    62,  -131,    47,  -131,
      66,    65,    65,    90,   105,   105,   105,   105,   105,   105,
      20,    20,  -131,  -131,  -131,  -131,   214,   116,   160,  -131,
    -131,   440,    27,   226,    87,    38,   440,  -131,   136,  -131,
    -131,   440,   165,  -131,  -131,   214,  -131,   -32,    87,  -131,
    -131,  -131,   440,    87,   506,  -131,  -131,   117,  -131,   120,
     266,   -11,   506,   171,   -32,  -131,  -131,  -131,   440,  -131,
     128,   306,   361,    23,  -131,  -131,  -131,  -131,   401,   466,
    -131,  -131
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     3,     1,     0,    10,     8,     4,     5,
       0,     0,     6,     0,     0,    26,     0,     0,    11,    12,
       9,    13,    14,    15,    16,    17,     7,     0,     0,     0,
      94,    88,    89,    90,    91,    92,    93,     0,     0,    26,
       0,     0,    36,     0,     0,     0,     0,     2,     0,     0,
      42,    27,    34,    29,    30,    31,    32,    33,    28,    61,
      62,    64,    67,    69,    76,    79,    83,    85,    18,    18,
       0,     0,    94,     0,     0,     0,     0,    57,    35,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,    63,    96,     0,    48,    26,    26,
       0,     0,    59,    97,     0,    40,     0,    43,    45,    41,
       0,    65,    66,    68,    70,    71,    72,    73,    74,    75,
      77,    78,    80,    81,    82,    84,     0,     0,     0,    24,
      95,     0,     0,     0,    53,     0,     0,    26,     0,    37,
      38,     0,     0,    39,    21,     0,    20,     3,    49,    26,
      50,    52,     0,    26,    60,    56,    44,    46,    22,     0,
       0,     0,    58,     0,     3,    26,    51,    26,     0,    47,
       0,     0,     0,     0,    26,    25,    54,    26,     0,     0,
      23,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,   -89,  -131,   168,   121,  -131,  -130,   108,    58,
    -131,  -131,  -131,  -131,   -39,  -131,  -131,   110,    51,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,   137,  -131,   -36,
      69,   119,    94,    52,   -85,   112,  -131
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     6,     8,     9,    10,    11,    26,   101,   102,
      18,   174,    19,   157,    27,    51,    52,   116,   117,   106,
      53,    54,    55,    56,    57,   112,   148,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      75,    73,    74,    70,   108,    77,   154,    78,     1,   177,
      81,   132,   133,   134,   135,   178,    71,     3,    72,    31,
      32,    33,    34,   137,   109,   168,   138,     5,    35,    36,
      30,    31,    32,    33,    34,   107,    85,    85,    86,    86,
      35,    36,    37,   187,   159,   160,    38,   118,   118,    39,
      44,    40,    85,     4,    86,    41,    96,    97,     7,    42,
      43,   162,    44,    20,    45,    98,    46,   105,   169,   142,
     143,    85,    68,    86,   144,   145,    45,    28,    46,    72,
      31,    32,    33,    34,   139,   180,    85,   138,    86,    35,
      36,    29,    48,    49,    50,    85,    85,    86,    86,    76,
     113,    15,    16,   152,    17,   158,   140,    69,   164,   141,
     163,    44,    87,   149,   150,   118,    13,   151,   153,    82,
     170,   151,    13,    14,   172,    45,   171,    46,   115,    88,
      89,    90,    91,    92,    93,    85,   181,    86,   182,    94,
      95,    99,   183,   146,   147,   188,   130,   131,   189,    30,
      31,    32,    33,    34,   121,   122,    79,    80,    83,    35,
      36,    37,    84,   100,    71,    38,   111,   165,    39,   167,
      40,   136,   155,   173,    41,   179,    12,   103,    42,    43,
     175,    44,   124,   125,   126,   127,   128,   129,   184,    30,
      31,    32,    33,    34,   120,    45,   156,    46,     0,    35,
      36,    37,   166,   114,    47,    38,   123,   104,    39,   110,
      40,    48,    49,    50,    41,     0,     0,     0,    42,    43,
       0,    44,    21,    22,    23,    24,    25,     0,     0,    30,
      31,    32,    33,    34,     0,    45,     0,    46,     0,    35,
      36,    37,     0,     0,     0,    38,     0,   161,    39,     0,
      40,    48,    49,    50,    41,     0,     0,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,     0,    45,     0,    46,     0,    35,
      36,    37,     0,     0,   176,    38,     0,     0,    39,     0,
      40,    48,    49,    50,    41,     0,     0,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,     0,    45,     0,    46,     0,    35,
      36,    37,     0,     0,     0,    38,     0,     0,    39,     0,
      40,    48,    49,    50,    41,     0,     0,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,    72,
      31,    32,    33,    34,     0,    45,     0,    46,     0,    35,
      36,     0,     0,     0,    30,    31,    32,    33,    34,     0,
     185,    48,    49,    50,    35,    36,    37,     0,     0,     0,
      38,    44,     0,    39,     0,    40,     0,     0,   186,    41,
       0,     0,     0,    42,    43,    45,    44,    46,   119,     0,
       0,     0,     0,     0,    30,    31,    32,    33,    34,     0,
      45,     0,    46,     0,    35,    36,    37,     0,     0,     0,
      38,     0,     0,    39,     0,    40,    48,    49,    50,    41,
       0,     0,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,    72,    31,    32,    33,    34,     0,     0,
      45,     0,    46,    35,    36,     0,     0,     0,     0,     0,
       0,     0,     0,   190,     0,     0,    48,    49,    50,    30,
      31,    32,    33,    34,     0,    44,     0,     0,     0,    35,
      36,    37,     0,     0,     0,    38,     0,     0,    39,    45,
      40,    46,     0,   191,    41,     0,     0,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,     0,    45,     0,    46,     0,    35,
      36,    37,     0,     0,     0,    38,     0,     0,    39,     0,
      40,    48,    49,    50,    41,     0,     0,     0,    42,    43,
       0,    44,    30,    31,    32,    33,    34,     0,     0,     0,
       0,     0,    35,    36,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46
};

static const yytype_int16 yycheck[] =
{
      39,    37,    38,    38,    16,    41,   136,    43,    57,    20,
      46,    96,    97,    98,    99,    26,    51,     7,     3,     4,
       5,     6,     7,    52,    20,   155,    55,    59,    13,    14,
       3,     4,     5,     6,     7,    71,    48,    48,    50,    50,
      13,    14,    15,    20,    17,    18,    19,    83,    84,    22,
      35,    24,    48,     0,    50,    28,    36,    37,     3,    32,
      33,    23,    35,     3,    49,    45,    51,    52,   157,   108,
     109,    48,    51,    50,   110,   111,    49,     3,    51,     3,
       4,     5,     6,     7,    52,   174,    48,    55,    50,    13,
      14,     3,    65,    66,    67,    48,    48,    50,    50,     3,
      52,    60,    61,    56,    63,   141,    52,    51,   147,    55,
     146,    35,    47,    52,    52,   151,    55,    55,    52,    51,
     159,    55,    55,    56,   163,    49,   162,    51,    52,    39,
      40,    41,    42,    43,    44,    48,   175,    50,   177,    34,
      35,    46,   178,    29,    30,   184,    94,    95,   187,     3,
       4,     5,     6,     7,    85,    86,    44,    45,    51,    13,
      14,    15,    51,     3,    51,    19,    25,    31,    22,     4,
      24,    56,    56,    56,    28,     4,     8,    69,    32,    33,
      60,    35,    88,    89,    90,    91,    92,    93,    60,     3,
       4,     5,     6,     7,    84,    49,   138,    51,    -1,    13,
      14,    15,   151,    82,    58,    19,    87,    70,    22,    23,
      24,    65,    66,    67,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,     8,     9,    10,    11,    12,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    49,    -1,    51,    -1,    13,
      14,    15,    -1,    -1,    -1,    19,    -1,    21,    22,    -1,
      24,    65,    66,    67,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    49,    -1,    51,    -1,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    -1,
      24,    65,    66,    67,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    49,    -1,    51,    -1,    13,
      14,    15,    -1,    -1,    -1,    19,    -1,    -1,    22,    -1,
      24,    65,    66,    67,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    49,    -1,    51,    -1,    13,
      14,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      64,    65,    66,    67,    13,    14,    15,    -1,    -1,    -1,
      19,    35,    -1,    22,    -1,    24,    -1,    -1,    27,    28,
      -1,    -1,    -1,    32,    33,    49,    35,    51,    52,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      49,    -1,    51,    -1,    13,    14,    15,    -1,    -1,    -1,
      19,    -1,    -1,    22,    -1,    24,    65,    66,    67,    28,
      -1,    -1,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      49,    -1,    51,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,     3,
       4,     5,     6,     7,    -1,    35,    -1,    -1,    -1,    13,
      14,    15,    -1,    -1,    -1,    19,    -1,    -1,    22,    49,
      24,    51,    -1,    27,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    49,    -1,    51,    -1,    13,
      14,    15,    -1,    -1,    -1,    19,    -1,    -1,    22,    -1,
      24,    65,    66,    67,    28,    -1,    -1,    -1,    32,    33,
      -1,    35,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,   103,     7,     0,    59,   104,     3,   105,   106,
     107,   108,   106,    55,    56,    60,    61,    63,   112,   114,
       3,     8,     9,    10,    11,    12,   109,   116,     3,     3,
       3,     4,     5,     6,     7,    13,    14,    15,    19,    22,
      24,    28,    32,    33,    35,    49,    51,    58,    65,    66,
      67,   117,   118,   122,   123,   124,   125,   126,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,    51,    51,
      38,    51,     3,   131,   131,   116,     3,   131,   131,   137,
     137,   131,    51,    51,    51,    48,    50,    47,    39,    40,
      41,    42,    43,    44,    34,    35,    36,    37,    45,    46,
       3,   110,   111,   110,   129,    52,   121,   131,    16,    20,
      23,    25,   127,    52,   107,    52,   119,   120,   131,    52,
     119,   132,   132,   133,   134,   134,   134,   134,   134,   134,
     135,   135,   136,   136,   136,   136,    56,    52,    55,    52,
      52,    55,   116,   116,   131,   131,    29,    30,   128,    52,
      52,    55,    56,    52,   109,    56,   111,   115,   131,    17,
      18,    21,    23,   131,   116,    31,   120,     4,   109,   104,
     116,   131,   116,    56,   113,    60,    18,    20,    26,     4,
     104,   116,   116,   131,    60,    64,    27,    20,   116,   116,
      62,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   109,   109,   109,   110,   110,
     110,   111,   113,   112,   115,   114,   116,   116,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   118,   118,   119,   119,   120,   120,   120,   121,   121,
     122,   122,   123,   124,   125,   125,   126,   127,   127,   128,
     128,   129,   129,   130,   131,   131,   131,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   134,   135,
     135,   135,   135,   136,   136,   137,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     2,     1,     2,     3,     1,     3,
       0,     2,     2,     1,     1,     1,     1,     1,     0,     1,
       3,     3,     0,    12,     0,    10,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     4,     4,     4,
       3,     3,     1,     1,     3,     1,     3,     5,     1,     3,
       5,     7,     5,     4,     9,    11,     5,     0,     4,     0,
       2,     1,     1,     3,     1,     3,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     3,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     3
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
  case 7: /* variable_declaration: identifier_list COLON type_specifier  */
#line 125 "src/parser.y"
                                         {
        // Itera a lista de identificadores ($1) e insere cada um
        // com o tipo especificado ($3)
        Simbolo* current = (yyvsp[-2].symlist);
        while(current) {
            insert_symbol(current->name, (yyvsp[0].ival)); 
            
            Simbolo* temp = current;
            current = current->next;
            if (temp->name) free(temp->name); // Libera o nome duplicado
            if (temp) free(temp);       // Libera o nó da lista
        }
    }
#line 1464 "bin/parser.tab.c"
    break;

  case 8: /* identifier_list: IDENTIFIER  */
#line 142 "src/parser.y"
               { 
        (yyval.symlist) = create_param((yyvsp[0].sval), 0); // Reutiliza create_param para criar um nó
        free((yyvsp[0].sval)); 
    }
#line 1473 "bin/parser.tab.c"
    break;

  case 9: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 146 "src/parser.y"
                                       {
        Simbolo* newNode = create_param((yyvsp[0].sval), 0);
        free((yyvsp[0].sval));
        
        Simbolo* list = (yyvsp[-2].symlist);
        while(list->next) list = list->next; // Vai até o fim da lista
        list->next = newNode;
        (yyval.symlist) = (yyvsp[-2].symlist); // Retorna o início da lista
    }
#line 1487 "bin/parser.tab.c"
    break;

  case 13: /* type_specifier: INTEIRO  */
#line 166 "src/parser.y"
                { (yyval.ival) = INTEIRO; }
#line 1493 "bin/parser.tab.c"
    break;

  case 14: /* type_specifier: REAL  */
#line 167 "src/parser.y"
                  { (yyval.ival) = REAL; }
#line 1499 "bin/parser.tab.c"
    break;

  case 15: /* type_specifier: CARACTER  */
#line 168 "src/parser.y"
                  { (yyval.ival) = CARACTER; }
#line 1505 "bin/parser.tab.c"
    break;

  case 16: /* type_specifier: LITERAL  */
#line 169 "src/parser.y"
                  { (yyval.ival) = LITERAL; }
#line 1511 "bin/parser.tab.c"
    break;

  case 17: /* type_specifier: LOGICO  */
#line 170 "src/parser.y"
                  { (yyval.ival) = LOGICO; }
#line 1517 "bin/parser.tab.c"
    break;

  case 18: /* parameter_list: %empty  */
#line 175 "src/parser.y"
                { (yyval.symlist) = NULL; }
#line 1523 "bin/parser.tab.c"
    break;

  case 19: /* parameter_list: parameter_declaration  */
#line 176 "src/parser.y"
                            { (yyval.symlist) = (yyvsp[0].sym); }
#line 1529 "bin/parser.tab.c"
    break;

  case 20: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 177 "src/parser.y"
                                                 {
        // Adiciona $3 ao final da lista $1
        Simbolo* list = (yyvsp[-2].symlist);
        while(list->next) list = list->next;
        list->next = (yyvsp[0].sym);
        (yyval.symlist) = (yyvsp[-2].symlist);
    }
#line 1541 "bin/parser.tab.c"
    break;

  case 21: /* parameter_declaration: IDENTIFIER COLON type_specifier  */
#line 188 "src/parser.y"
                                    {
        (yyval.sym) = create_param((yyvsp[-2].sval), (yyvsp[0].ival)); // Cria o símbolo do parâmetro
        free((yyvsp[-2].sval));
        // NÃO insere na tabela de símbolos aqui.
        // A função/procedimento fará isso ao entrar no escopo.
    }
#line 1552 "bin/parser.tab.c"
    break;

  case 22: /* $@1: %empty  */
#line 199 "src/parser.y"
    {
        // Ação 1: Inserir a função na tabela (escopo global)
        // e mudar para o escopo local
        insert_function((yyvsp[-5].sval), (yyvsp[0].ival), (yyvsp[-3].symlist)); // $2=nome, $7=tipo, $4=params
        current_scope = 1; // Entra no escopo local
        
        // Ação 2: Inserir os parâmetros no escopo local
        Simbolo *p = (yyvsp[-3].symlist);
        while (p) {
            insert_symbol(p->name, p->type);
            p = p->next;
        }
        free((yyvsp[-5].sval));
    }
#line 1571 "bin/parser.tab.c"
    break;

  case 23: /* function_declaration: FUNCAO IDENTIFIER LPAREN parameter_list RPAREN COLON type_specifier $@1 declaracao_variaveis INICIO statement_list FIMFUNCAO  */
#line 217 "src/parser.y"
    {
        current_scope = 0; // Volta para escopo global
        // TODO: Limpar tabela de símbolos do escopo local
    }
#line 1580 "bin/parser.tab.c"
    break;

  case 24: /* $@2: %empty  */
#line 226 "src/parser.y"
    {
        // Ação 1: Inserir procedimento e mudar escopo
        insert_function((yyvsp[-3].sval), 0, (yyvsp[-1].symlist)); // Usa tipo 0 (void) para procedimento
        current_scope = 1; // Entra no escopo local
        
        // Ação 2: Inserir parâmetros no escopo local
        Simbolo *p = (yyvsp[-1].symlist);
        while (p) {
            insert_symbol(p->name, p->type);
            p = p->next;
        }
        free((yyvsp[-3].sval));
    }
#line 1598 "bin/parser.tab.c"
    break;

  case 25: /* procedure_declaration: PROCEDIMENTO IDENTIFIER LPAREN parameter_list RPAREN $@2 declaracao_variaveis INICIO statement_list FIMPROCEDIMENTO  */
#line 243 "src/parser.y"
    {
        current_scope = 0; // Volta para escopo global
        // TODO: Limpar tabela de símbolos do escopo local
    }
#line 1607 "bin/parser.tab.c"
    break;

  case 63: /* assignment_statement: IDENTIFIER ASSIGN expression  */
#line 366 "src/parser.y"
    {
        Simbolo *s = find_symbol((yyvsp[-2].sval));
        if (s == NULL) {
            char error_msg[100];
            sprintf(error_msg, "Variável '%s' não declarada.", (yyvsp[-2].sval));
            yyerror(error_msg);
            YYABORT;
        }
        // TODO: Verificação de tipo
        free((yyvsp[-2].sval));
    }
#line 1623 "bin/parser.tab.c"
    break;

  case 94: /* primary_expression: IDENTIFIER  */
#line 431 "src/parser.y"
                 {
        // Ação Semântica: Verifica se o identificador já foi declarado.
        Simbolo *sym = find_symbol((yyvsp[0].sval));
        if (sym == NULL) {
            // Permitir funções built-in como LIMPATELA, MUDACOR, etc.
        }
        free((yyvsp[0].sval));
    }
#line 1636 "bin/parser.tab.c"
    break;


#line 1640 "bin/parser.tab.c"

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

#line 445 "src/parser.y"


// Funções C de suporte para o parser
int main(int argc, char **argv) {

    #ifdef COMPILER_DEBUG 
    if(COMPILER_DEBUG) printf("[DEBUG] parametros = %d\n", argc);
    #endif
    
    FILE *file = NULL;
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            perror("Não foi possível abrir o arquivo");
            return 1;
        }
        yyin = file;
    }
    
    printf("Iniciando a análise...\n");
    printf("Analisando o arquivo: %s\n", argc > 1 ? argv[1] : "entrada padrão");

    // Inicia o processo de parsing
    if (yyparse() == 0) {
        printf("Análise sintática bem-sucedida!\n");
    } else {
        printf("Análise sintática falhou.\n");
    }

    // Imprime a tabela de símbolos ao final da análise
    printf("\n\nAnálise concluída. Tabela de Símbolos:\n");
    print_symbol_table();

    if (file) {
        fclose(file);
    }

    return 0;
}

// Função de erro para o Bison.
void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s. Próximo a: '%s'\n", yylineno, s, yytext);
}

// Funções para manipulação da Tabela de Símbolos

void insert_symbol(char *name, int type) {
    // Implementação simples de lista encadeada.
    // Verifica se o símbolo já existe no escopo atual
    Simbolo * existing = find_symbol_in_scope(name, current_scope);
    if (existing != NULL) {
        fprintf(stderr, "Erro semântico: Identificador '%s' já declarado neste escopo (linha %d).\n", name, yylineno);
        exit(1);
    }
    
    Simbolo * new_symbol = (Simbolo *) malloc(sizeof(Simbolo));

    if (! new_symbol) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    new_symbol->name = strdup(name);
    if (! new_symbol->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    new_symbol->type = type;
    new_symbol->scope = current_scope; // variavel global/local
    new_symbol->is_function = 0;       // por padrão, é uma variável
    new_symbol->params = NULL;         // não é uma função, então sem parâmetros
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
}

Simbolo *find_symbol(char *name) {
    // Procura primeiro no escopo local, depois no global
    Simbolo *s = find_symbol_in_scope(name, 1); // Local
    if (s) return s;
    s = find_symbol_in_scope(name, 0); // Global
    return s;
}

Simbolo * find_symbol_in_scope(char *name, int scope) {
    Simbolo * current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->scope == scope) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

const char* type_to_string(int type) {
    switch (type) {
        case INTEIRO:   return "INTEIRO";
        case REAL:      return "REAL";
        case CARACTER:  return "CARACTER";
        case LITERAL:   return "LITERAL";
        case LOGICO:    return "LOGICO";
        case 0:         return "PROCEDIMENTO"; // Nosso "void"
        default:        return "desconhecido";
    }
}

void print_symbol_table() {
    Simbolo *current = symbol_table;
    printf("\n\nTabela de Símbolos:\n");
    printf("%-15s\t%-15s\t%s\t%s\t%s\n", "Nome", "Tipo", "Escopo", "Categoria", "Parâmetros");
    printf("--------------------------------------------------------------------------\n");
    while (current != NULL) {
        if (current->is_function) {
            printf("%-15s\t%-15s\t%s\tfunção\t\t", current->name, type_to_string(current->type), current->scope == 0 ? "global" : "local");
            Simbolo *p = current->params;
            while (p) {
                printf("%s:%s ", p->name, type_to_string(p->type));
                p = p->next;
            }
            printf("\n");
        } else {
            printf("%-15s\t%-15s\t%d\tvariavel\n", current->name, type_to_string(current->type), current->scope);
        }
        current = current->next;
    }
}

void insert_function(char *name, int return_type, Simbolo *params) {
    if (find_symbol_in_scope(name, 0)) { // Funções só podem ser globais
        fprintf(stderr, "Erro: função/procedimento '%s' já declarado.\n", name);
        exit(1);
    }
    
    Simbolo *func = malloc(sizeof(Simbolo));
    
    if (! func) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    func->name = strdup(name);
    if (! func->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    func->type = return_type;
    func->scope = current_scope; // Deve ser 0 (global)
    func->is_function = 1;
    func->params = params;
    func->next = symbol_table;
    symbol_table = func;
}

Simbolo* create_param(char *name, int type) {
    Simbolo *param = malloc(sizeof(Simbolo));
    if (! param) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    param->name = strdup(name);
    if (! param->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    param->type = type;
    param->scope = 1; // Parâmetros são sempre escopo local
    param->is_function = 0;
    param->params = NULL;
    param->next = NULL;
    return param;
}
