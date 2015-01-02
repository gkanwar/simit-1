// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.h"

// User implementation prologue.


// Unqualified %code blocks.


  #include <stdlib.h>
  #include <iostream>
  #include <map>
  #include <set>
  #include <algorithm>

  #include "program_context.h"
  #include "scanner.h"

  using namespace std;
  using namespace simit::internal;
  using namespace simit::ir;

  std::string typeString(const Type &type) {
    std::stringstream ss;
    ss << type;
    std::string str = ss.str();
    if (type.isTensor() && type.toTensor()->isColumnVector) {
      str += "'";
    }
    return str;
  }

  #define REPORT_ERROR(msg, loc)  \
    do {                          \
      error((loc), (msg));        \
      YYERROR;                    \
    } while (0)

  #define REPORT_TYPE_MISSMATCH(t1, t2, loc)                          \
    do {                                                              \
      std::stringstream errorStr;                                     \
      errorStr << "type missmatch (" <<                               \
                  typeString(t1) << " and " << typeString(t2) << ")"; \
      REPORT_ERROR(errorStr.str(), loc);                              \
    } while (0)

  #define REPORT_INDEX_VARIABLE_MISSMATCH(numIndexVars, order, loc) \
    do {                                                            \
      REPORT_ERROR("wrong number of index variables (" +            \
                    to_string(numIndexVars) +                       \
                    " index variables, but tensor order is " +      \
                    to_string(order), loc);                         \
      } while (0)

  void Parser::error(const Parser::location_type &loc,
                           const std::string &msg) {
    errors->push_back(ParseError(loc.begin.line, loc.begin.column,
                            loc.end.line, loc.end.column, msg));
  }

  #undef yylex
  #define yylex scanner->lex

  inline std::string convertAndFree(const char *str) {
    std::string result = std::string(str);
    free((void*)str);
    return result;
  }

  template <typename T>
  inline T convertAndDelete(T *obj) {
    auto result = T(*obj);
    delete obj;
    return result;
  }

  void transposeVector(Expr vec) {
    iassert(vec.type().isTensor());
    const TensorType *ttype = vec.type().toTensor();
    iassert(ttype->order() == 1);

    Type transposedVector = TensorType::make(ttype->componentType,
                                             ttype->dimensions,
                                             !ttype->isColumnVector);

    const_cast<ExprNodeBase*>(to<ExprNodeBase>(vec))->type = transposedVector;
  }

  bool compare(const Type &l, const Type &r, ProgramContext *ctx) {
    if (l.kind() != r.kind()) {
      return false;
    }

//    if (l.isTensor()) {
//      if (l.toTensor()->isColumnVector != r.toTensor()->isColumnVector) {
//        return false;
//      }
//    }

    if (l != r) {
      return false;
    }
    return true;
  }

  #define CHECK_IS_TENSOR(expr, loc)                    \
    do {                                                \
      if (!expr.type().isTensor()) {                \
        std::stringstream errorStr;                     \
        errorStr << "expected tensor";                  \
        REPORT_ERROR(errorStr.str(), loc);              \
      }                                                 \
    } while (0)

  #define CHECK_TYPE_EQUALITY(t1, t2, loc)              \
    do {                                                \
      if (!compare(t1, t2, ctx)) {                      \
        REPORT_TYPE_MISSMATCH(t1, t2, loc);             \
      }                                                 \
    } while (0)


  #define BINARY_ELWISE_TYPE_CHECK(lt, rt, loc)   \
    do {                                          \
      iassert(lt.isTensor() && rt.isTensor());    \
      const TensorType *ltt = lt.toTensor();      \
      const TensorType *rtt = rt.toTensor();      \
      if (ltt->order() > 0 && rtt->order() > 0) { \
        CHECK_TYPE_EQUALITY(lt, rt, loc);         \
      }                                           \
    }                                             \
    while (0)




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace  simit { namespace internal  {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   Parser :: Parser  (Scanner *scanner_yyarg, ProgramContext *ctx_yyarg, std::vector<ParseError> *errors_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      ctx (ctx_yyarg),
      errors (errors_yyarg)
  {}

   Parser ::~ Parser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
   Parser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
   Parser ::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
   Parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
   Parser ::by_type::by_type ()
     : type (empty)
  {}

  inline
   Parser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   Parser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   Parser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
   Parser ::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
   Parser ::by_state::by_state ()
    : state (empty)
  {}

  inline
   Parser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
   Parser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   Parser ::symbol_number_type
   Parser ::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
   Parser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   Parser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 4: // "int literal"


        {}

        break;

      case 5: // "float literal"


        {}

        break;

      case 6: // "string literal"


        { free((void*)((yysym.value.string))); }

        break;

      case 7: // "identifier"


        { free((void*)((yysym.value.string))); }

        break;

      case 69: // extern


        { delete (yysym.value.var); }

        break;

      case 70: // element_type_decl


        { delete (yysym.value.type); }

        break;

      case 71: // field_decl_list


        { delete (yysym.value.fields); }

        break;

      case 72: // field_decl


        { delete (yysym.value.field); }

        break;

      case 73: // procedure


        { delete (yysym.value.function); }

        break;

      case 76: // procedure_header


        { delete (yysym.value.function); }

        break;

      case 77: // function


        { delete (yysym.value.function); }

        break;

      case 80: // function_header


        { delete (yysym.value.function); }

        break;

      case 81: // arguments


        { delete (yysym.value.vars); }

        break;

      case 82: // argument_list


        { delete (yysym.value.vars); }

        break;

      case 83: // argument_decl


        { delete (yysym.value.var); }

        break;

      case 84: // results


        { delete (yysym.value.vars); }

        break;

      case 85: // result_list


        { delete (yysym.value.vars); }

        break;

      case 86: // result_decl


        { delete (yysym.value.var); }

        break;

      case 87: // stmt_block


        { delete (yysym.value.stmt); }

        break;

      case 92: // partial_expr_list


        { delete (yysym.value.exprs); }

        break;

      case 93: // idents


        { delete (yysym.value.strings); }

        break;

      case 94: // with


        { delete (yysym.value.expr); }

        break;

      case 95: // reduce


        {}

        break;

      case 96: // reduce_op


        {}

        break;

      case 100: // while_stmt_header


        { delete (yysym.value.expr); }

        break;

      case 101: // while_body


        { delete (yysym.value.stmt); }

        break;

      case 103: // if_stmt


        { delete (yysym.value.stmt); }

        break;

      case 104: // if_body


        { delete (yysym.value.stmt); }

        break;

      case 105: // else_clauses


        { delete (yysym.value.stmt); }

        break;

      case 107: // for_stmt_header


        { delete (yysym.value.var); }

        break;

      case 110: // expr_stmt


        { delete (yysym.value.stmt); }

        break;

      case 112: // expr


        { delete (yysym.value.expr); }

        break;

      case 113: // ident_expr


        { delete (yysym.value.expr); }

        break;

      case 114: // paren_expr


        { delete (yysym.value.expr); }

        break;

      case 115: // linear_algebra_expr


        { delete (yysym.value.expr); }

        break;

      case 116: // elwise_binary_op


        {}

        break;

      case 117: // boolean_expr


        { delete (yysym.value.expr); }

        break;

      case 118: // field_read_expr


        { delete (yysym.value.expr); }

        break;

      case 119: // set_read_expr


        { delete (yysym.value.expr); }

        break;

      case 120: // call_or_paren_read_expr


        { delete (yysym.value.expr); }

        break;

      case 121: // expr_list_or_empty


        { delete (yysym.value.exprs); }

        break;

      case 122: // expr_list


        { delete (yysym.value.exprs); }

        break;

      case 123: // type


        { delete (yysym.value.type); }

        break;

      case 124: // element_type


        { delete (yysym.value.type); }

        break;

      case 125: // set_type


        { delete (yysym.value.type); }

        break;

      case 126: // endpoints


        { delete (yysym.value.exprs); }

        break;

      case 127: // tuple_type


        { delete (yysym.value.type); }

        break;

      case 128: // tensor_type


        { delete (yysym.value.type); }

        break;

      case 129: // index_sets


        { delete (yysym.value.indexSets); }

        break;

      case 130: // index_set


        { delete (yysym.value.indexSet); }

        break;

      case 131: // component_type


        { delete (yysym.value.scalarType); }

        break;

      case 132: // literal_expr


        { delete (yysym.value.expr); }

        break;

      case 133: // tensor_literal


        { delete (yysym.value.expr); }

        break;

      case 134: // dense_tensor_literal


        { delete (yysym.value.expr); }

        break;

      case 135: // float_dense_tensor_literal


        { delete (yysym.value.TensorDoubleValues); }

        break;

      case 136: // float_dense_ndtensor_literal


        { delete (yysym.value.TensorDoubleValues); }

        break;

      case 137: // float_dense_matrix_literal


        { delete (yysym.value.TensorDoubleValues); }

        break;

      case 138: // float_dense_vector_literal


        { delete (yysym.value.TensorDoubleValues); }

        break;

      case 139: // int_dense_tensor_literal


        { delete (yysym.value.TensorIntValues); }

        break;

      case 140: // int_dense_ndtensor_literal


        { delete (yysym.value.TensorIntValues); }

        break;

      case 141: // int_dense_matrix_literal


        { delete (yysym.value.TensorIntValues); }

        break;

      case 142: // int_dense_vector_literal


        { delete (yysym.value.TensorIntValues); }

        break;

      case 143: // scalar_literal


        { delete (yysym.value.expr); }

        break;

      case 144: // signed_int_literal


        {}

        break;

      case 145: // signed_float_literal


        {}

        break;

      case 147: // system_generator


        { delete (yysym.value.system); }

        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   Parser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   Parser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   Parser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 5:

    {
    Func func = convertAndDelete((yystack_[0].value.function));
    std::string name = func.getName();
    if (ctx->containsFunction(name)) {
      REPORT_ERROR("procedure redefinition (" + name + ")", yystack_[0].location);
    }
    ctx->addFunction(func);
  }

    break;

  case 6:

    {
    Func func = convertAndDelete((yystack_[0].value.function));
    std::string name = func.getName();
    if (ctx->containsFunction(name)) {
      REPORT_ERROR("function redefinition (" + name + ")", yystack_[0].location);
    }
    ctx->addFunction(func);
  }

    break;

  case 10:

    {
    Var externVar = convertAndDelete((yystack_[1].value.var));
    ctx->addExtern(externVar);
    ctx->addSymbol(externVar);
  }

    break;

  case 11:

    {
    string name = convertAndFree((yystack_[2].value.string));
    unique_ptr<vector<Field>> fields((yystack_[1].value.fields));

    if (ctx->containsElementType(name)) {
      REPORT_ERROR("struct redefinition (" + name + ")", yylhs.location);
    }

    ctx->addElementType(ElementType::make(name, *fields));
  }

    break;

  case 12:

    {
    (yylhs.value.fields) = new vector<Field>;
  }

    break;

  case 13:

    {
    (yylhs.value.fields) = (yystack_[1].value.fields);
    (yylhs.value.fields)->push_back(*(yystack_[0].value.field));
    delete (yystack_[0].value.field);
  }

    break;

  case 14:

    {
    std::string name = convertAndFree((yystack_[3].value.string));
    auto tensorType = convertAndDelete((yystack_[1].value.type));
    (yylhs.value.field) = new Field(name, tensorType);
  }

    break;

  case 15:

    {ctx->scope();}

    break;

  case 16:

    {ctx->unscope();}

    break;

  case 17:

    {
    Func func = convertAndDelete((yystack_[3].value.function));
    Stmt body = convertAndDelete((yystack_[2].value.stmt));
    (yylhs.value.function) = new Func(func.getName(), func.getArguments(), func.getResults(), body);
  }

    break;

  case 18:

    {
    std::string name = convertAndFree((yystack_[0].value.string));
    auto arguments = vector<Var>();
    auto results = vector<Var>();

    for (auto &extPair : ctx->getExterns()) {
      Var ext = ctx->getExtern(extPair.first);

      // TODO: Make extResult a mutable parameter
      arguments.push_back(ext);
    }

    (yylhs.value.function) = new Func(name, arguments, results, Stmt());
  }

    break;

  case 19:

    {ctx->scope();}

    break;

  case 20:

    {ctx->unscope();}

    break;

  case 21:

    {
    Func func = convertAndDelete((yystack_[3].value.function));
    Stmt body = convertAndDelete((yystack_[2].value.stmt));
    (yylhs.value.function) = new Func(func.getName(), func.getArguments(), func.getResults(), body);
  }

    break;

  case 22:

    {
    std::string name = convertAndFree((yystack_[4].value.string));
    auto arguments = unique_ptr<vector<Var>>((yystack_[2].value.vars));
    auto results = unique_ptr<vector<Var>>((yystack_[0].value.vars));
    auto newArguments = unique_ptr<vector<Var>>(new vector<Var>());
    
    std::set<std::string> argNames;
    for (Var &arg : *arguments) {
      auto found = arg.getName().find("___inout___");
      if (found != string::npos) {
        // this is an inout param
        string newName = arg.getName().substr(0,found);
        auto newArg = Var(newName, arg.getType());
        ctx->addSymbol(newName, newArg, Symbol::ReadWrite);
        argNames.insert(newArg.getName());
        newArguments->push_back(newArg);
      } else {
        ctx->addSymbol(arg.getName(), arg, Symbol::Read);
        argNames.insert(arg.getName());
        newArguments->push_back(arg);
      }
    }

    (yylhs.value.function) = new Func(name, *newArguments, *results, Stmt());

    for (Var &res : *results) {
      Symbol::Access access = (argNames.find(res.getName()) != argNames.end())
                              ? Symbol::ReadWrite : Symbol::ReadWrite;
      ctx->addSymbol(res.getName(), res, access);
    }
  }

    break;

  case 23:

    {
    (yylhs.value.vars) = new vector<Var>;
  }

    break;

  case 24:

    {
    (yylhs.value.vars) = (yystack_[0].value.vars);
 }

    break;

  case 25:

    {
    auto argument = convertAndDelete((yystack_[0].value.var));
    (yylhs.value.vars) = new vector<Var>;
    (yylhs.value.vars)->push_back(argument);
  }

    break;

  case 26:

    {
    auto argument = convertAndDelete((yystack_[0].value.var));
    (yylhs.value.vars) = (yystack_[2].value.vars);
    (yylhs.value.vars)->push_back(argument);
  }

    break;

  case 27:

    {
    // this is by no means the best way to do this, but it works.
    std::string name = convertAndFree((yystack_[2].value.string)).append("___inout___");

    auto type = convertAndDelete((yystack_[0].value.type));
    (yylhs.value.var) = new Var(name, type);
  }

    break;

  case 28:

    {
    std::string name = convertAndFree((yystack_[2].value.string));

    auto type = convertAndDelete((yystack_[0].value.type));
    (yylhs.value.var) = new Var(name, type);
  }

    break;

  case 29:

    {
    (yylhs.value.vars) = new vector<Var>;
  }

    break;

  case 30:

    {
    (yylhs.value.vars) = (yystack_[1].value.vars);
  }

    break;

  case 31:

    {
    auto result = convertAndDelete((yystack_[0].value.var));
    (yylhs.value.vars) = new vector<Var>;
    (yylhs.value.vars)->push_back(result);
  }

    break;

  case 32:

    {
    auto result = convertAndDelete((yystack_[0].value.var));
    (yylhs.value.vars) = (yystack_[2].value.vars);
    (yylhs.value.vars)->push_back(result);
  }

    break;

  case 33:

    {
    std::string name = convertAndFree((yystack_[2].value.string));
    auto type = convertAndDelete((yystack_[0].value.type));
    (yylhs.value.var) = new Var(name, type);
  }

    break;

  case 34:

    {
    (yylhs.value.stmt) = new Stmt(Pass::make());
  }

    break;

  case 35:

    {
    vector<Stmt> stmts = *ctx->getStatements();
    if (stmts.size() == 0) {(yylhs.value.stmt) = new Stmt(Pass::make()); break;} // TODO: remove
    (yylhs.value.stmt) = new Stmt((stmts.size() == 1) ? stmts[0] : Block::make(stmts));
  }

    break;

  case 48:

    {
    if ((yystack_[1].value.expr) == nullptr) {break;} // TODO: Remove check

    auto varNames = convertAndDelete((yystack_[3].value.strings));
    Expr value = convertAndDelete((yystack_[1].value.expr));

    if (varNames.size() > 1) {
      REPORT_ERROR("can only assign to one value in a non-map statement",
                   yystack_[3].location);
    }
    string varName = varNames[0];

    Var var;
    if (ctx->hasSymbol(varName)) {
      Symbol symbol = ctx->getSymbol(varName);

      if (!symbol.isWritable()) {
        REPORT_ERROR(varName + " is not writable", yystack_[3].location);
      }

      CHECK_TYPE_EQUALITY(symbol.getVar().getType(), value.type(), yystack_[1].location);

      var = symbol.getVar();
    }
    else {
      var = Var(varName, value.type());
      ctx->addSymbol(varName, var, Symbol::ReadWrite);
    }

    // TODO: This should be dealt with inside the ident_expr rule
    if (isa<VarExpr>(value) && value.type().isTensor()) {
      // The statement assign a tensor to a tensor, so we change it to an
      // assignment index expr
      value = ctx->getBuilder()->unaryElwiseExpr(IRBuilder::None, value);
    }

    ctx->addStatement(AssignStmt::make(var, value));
  }

    break;

  case 49:

    {
    auto varNames = unique_ptr<vector<string>>((yystack_[8].value.strings));

    auto partialExprList = unique_ptr<vector<Expr>>((yystack_[4].value.exprs));
    
    string funcName = convertAndFree((yystack_[5].value.string));
    string targetsName = convertAndFree((yystack_[2].value.string));

    Expr neighbor = convertAndDelete((yystack_[1].value.expr));
    ReductionOperator reduction((yystack_[0].value.reductionop));

    if (!ctx->containsFunction(funcName)) {
      REPORT_ERROR("undefined function '" + funcName + "'", yystack_[5].location);
    }
    Func func = ctx->getFunction(funcName);

    if (varNames->size() != func.getResults().size()) {
      REPORT_ERROR("the number of variables (" + to_string(varNames->size()) +
                   ") does not match the number of results returned by " +
                   func.getName() + " (" + to_string(func.getResults().size()) +
                   ")", yystack_[8].location);
    }

    if (!ctx->hasSymbol(targetsName)) {
      REPORT_ERROR("undefined set '" + targetsName + "'", yystack_[2].location);
    }
    Expr targets = ctx->getSymbol(targetsName).getExpr();

    auto &results = func.getResults();
    vector<Var> vars;
    for (size_t i=0; i < results.size(); ++i) {
      string varName = (*varNames)[i];
      Var var;
      if (ctx->hasSymbol(varName)) {
        Symbol symbol = ctx->getSymbol(varName);

        if (!symbol.isWritable()) {
          REPORT_ERROR(varName + " is not writable", yystack_[8].location);
        }

        var = symbol.getVar();
      }
      else {
        var = Var(varName, results[i].getType());
        ctx->addSymbol(varName, var, Symbol::ReadWrite);
      }
      vars.push_back(var);
    }

    ctx->addStatement(Map::make(vars, func, *partialExprList, targets, neighbor,
      reduction));
  }

    break;

  case 50:

    {
    (yylhs.value.exprs) = new vector<Expr>();
  }

    break;

  case 51:

    {
    (yylhs.value.exprs) = (yystack_[1].value.exprs);
  }

    break;

  case 52:

    {
    (yylhs.value.strings) = new vector<string>;
    (yylhs.value.strings)->push_back(convertAndFree((yystack_[0].value.string)));
  }

    break;

  case 53:

    {
    (yylhs.value.strings) = (yystack_[2].value.strings);
    (yylhs.value.strings)->push_back(convertAndFree((yystack_[0].value.string)));
  }

    break;

  case 54:

    {
    (yylhs.value.expr) = new Expr();
  }

    break;

  case 55:

    {
    std::string neighborsName = convertAndFree((yystack_[0].value.string));

    if (!ctx->hasSymbol(neighborsName)) {
      REPORT_ERROR("undefined set '" + neighborsName + "'", yystack_[0].location);
    }
    Expr neighbors = ctx->getSymbol(neighborsName).getExpr();

    (yylhs.value.expr) = new Expr(neighbors);
  }

    break;

  case 56:

    {
    (yylhs.value.reductionop) =  ReductionOperator::Undefined;
  }

    break;

  case 57:

    {
    (yylhs.value.reductionop) =  (yystack_[0].value.reductionop);
  }

    break;

  case 58:

    {
    (yylhs.value.reductionop) = ReductionOperator::Sum;
  }

    break;

  case 59:

    {
    string setName = convertAndFree((yystack_[5].value.string));
    string fieldName = convertAndFree((yystack_[3].value.string));
    if ((yystack_[1].value.expr) == nullptr) break;  // TODO: remove check
    Expr value = convertAndDelete((yystack_[1].value.expr));

    if (!ctx->hasSymbol(setName)) {
      REPORT_ERROR(setName + " is not defined in scope", yystack_[5].location);
    }

    const Symbol &setSymbol = ctx->getSymbol(setName);
    if (!setSymbol.isWritable()) {
      REPORT_ERROR(setName + " is not writable", yystack_[5].location);
    }

    Expr setExpr = setSymbol.getExpr();
    ctx->addStatement(FieldWrite::make(setExpr, fieldName, value));
  }

    break;

  case 60:

    {
    std::string tensorName = convertAndFree((yystack_[6].value.string));
    auto indices = unique_ptr<vector<Expr>>((yystack_[4].value.exprs));
    if ((yystack_[1].value.expr) == nullptr) break;  // TODO: remove check
    Expr value = convertAndDelete((yystack_[1].value.expr));

    if(!ctx->hasSymbol(tensorName)) break;  // TODO: Remove check

    if (!ctx->hasSymbol(tensorName)) {
      REPORT_ERROR(tensorName + " is not defined in scope", yystack_[6].location);
    }

    const Symbol &tensorSymbol = ctx->getSymbol(tensorName);
    if (!tensorSymbol.isWritable()) {
      REPORT_ERROR(tensorName + " is not writable", yystack_[6].location);
    }

    Expr tensorExpr = tensorSymbol.getExpr();
    ctx->addStatement(TensorWrite::make(tensorExpr, *indices, value));
  }

    break;

  case 61:

    {
    //TODO: This rule really should be:
    // field_read_expr "(" expr_list ")" "=" expr ";"
    // but this requires reworking a lot of the parser.
 
    string setName = convertAndFree((yystack_[8].value.string));
    string fieldName = convertAndFree((yystack_[6].value.string));
    auto indices = unique_ptr<vector<Expr>>((yystack_[4].value.exprs));
    if ((yystack_[1].value.expr) == nullptr) break;  // TODO: remove check
    Expr value = convertAndDelete((yystack_[1].value.expr));

    if (!ctx->hasSymbol(setName)) {
      REPORT_ERROR(setName + " is not defined in scope", yystack_[8].location);
    }

    const Symbol &setSymbol = ctx->getSymbol(setName);
    if (!setSymbol.isWritable()) {
      REPORT_ERROR(setName + " is not writable", yystack_[8].location);
    }

    Expr setExpr = setSymbol.getExpr();

    Expr tensorExpr = FieldRead::make(setExpr, fieldName);
    ctx->addStatement(TensorWrite::make(tensorExpr, *indices, value));
  }

    break;

  case 62:

    {
    Expr cond = convertAndDelete((yystack_[2].value.expr));
    Stmt body = convertAndDelete((yystack_[1].value.stmt));
    
    ctx->addStatement(While::make(cond, body));

  }

    break;

  case 63:

    {
    ctx->scope();
    (yylhs.value.expr) = new Expr(convertAndDelete((yystack_[0].value.expr)));
  }

    break;

  case 64:

    {

    (yylhs.value.stmt) = new Stmt(convertAndDelete((yystack_[0].value.stmt)));
  }

    break;

  case 65:

    {
    ctx->unscope();
  }

    break;

  case 66:

    {
    Expr cond = convertAndDelete((yystack_[3].value.expr));
    ctx->scope();
    Stmt trueStmt = convertAndDelete((yystack_[2].value.stmt));
    ctx->unscope();
    Stmt elseStmt = convertAndDelete((yystack_[1].value.stmt));
    Stmt *result = new Stmt(IfThenElse::make(cond, trueStmt, elseStmt));
    ctx->addStatement(*result);
    (yylhs.value.stmt) = result;
  }

    break;

  case 67:

    {
    (yylhs.value.stmt) = new Stmt(convertAndDelete((yystack_[0].value.stmt)));
  }

    break;

  case 68:

    {
    (yylhs.value.stmt) = new Stmt(Pass::make());
  }

    break;

  case 69:

    {
    ctx->scope();
    (yylhs.value.stmt) = new Stmt(convertAndDelete((yystack_[0].value.stmt)));
    ctx->unscope();
  }

    break;

  case 70:

    {
    Expr cond = convertAndDelete((yystack_[2].value.expr));
    ctx->scope();
    Stmt trueStmt = convertAndDelete((yystack_[1].value.stmt));
    ctx->unscope();
    Stmt elseStmt = convertAndDelete((yystack_[0].value.stmt));
    Stmt *result = new Stmt(IfThenElse::make(cond, trueStmt, elseStmt));
    ctx->addStatement(*result);
    (yylhs.value.stmt) = result;
  }

    break;

  case 71:

    {    
    if((yystack_[2].value.indexSet)->getKind()==IndexSet::Set){
      ctx->addStatement(For::make(*(yystack_[3].value.var),ForDomain(*(yystack_[2].value.indexSet)), *(yystack_[1].value.stmt)));
    }
    delete (yystack_[3].value.var);
    delete (yystack_[2].value.indexSet);
    delete (yystack_[1].value.stmt);
  }

    break;

  case 72:

    {    
    ctx->addStatement(ForRange::make(*(yystack_[5].value.var), *(yystack_[4].value.expr), *(yystack_[2].value.expr), *(yystack_[1].value.stmt)));
    delete (yystack_[5].value.var);
    delete (yystack_[4].value.expr);
    delete (yystack_[2].value.expr);
    delete (yystack_[1].value.stmt);
  }

    break;

  case 73:

    {
 string varName = convertAndFree((yystack_[1].value.string));
 Var * var = new Var(varName, Int);     
 ctx->scope();
 // If we need to write to loop variables, then that should be added as a
 // separate loop structure (that can't be vectorized easily)
 ctx->addSymbol(varName, *var, Symbol::Read);

 (yylhs.value.var)=var;
 }

    break;

  case 74:

    {
    ctx->unscope();
  }

    break;

  case 75:

    {
    std::string name = convertAndFree((yystack_[5].value.string));
    auto type = convertAndDelete((yystack_[3].value.type));
    const TensorType *tensorType = type.toTensor();

    Expr literalExpr = convertAndDelete((yystack_[1].value.expr));

    iassert(literalExpr.type().isTensor())
        << "Only tensor literals are currently supported";
    auto litType = literalExpr.type();

    // If tensor_type is a 1xn matrix and $tensor_literal is a vector then we
    // cast $tensor_literal to a 1xn matrix.
    const TensorType *litTensorType = litType.toTensor();
    if (tensorType->order() == 2 && litTensorType->order() == 1) {
      const_cast<Literal*>(to<Literal>(literalExpr))->cast(type);
    }

    // Typecheck: value and literal types must be equivalent.
    CHECK_TYPE_EQUALITY(type, literalExpr.type(), yystack_[5].location);

    Var var(name, type);
    ctx->addConstant(var, literalExpr);
    ctx->addSymbol(var);
  }

    break;

  case 76:

    {
    (yylhs.value.stmt) = NULL;
  }

    break;

  case 77:

    {
    (yylhs.value.stmt) = NULL;
  }

    break;

  case 78:

    {
     Expr expr = Expr(convertAndDelete((yystack_[1].value.expr)));
     ctx->addStatement(Stmt(Print::make(expr)));
  }

    break;

  case 86:

    {
    string ident = convertAndFree((yystack_[0].value.string));

    if (!ctx->hasSymbol(ident)) {
      REPORT_ERROR(ident + " is not defined in scope", yystack_[0].location);
    }

    const Symbol &symbol = ctx->getSymbol(ident);
    if (!symbol.isReadable()) {
      REPORT_ERROR(ident + " is not readable", yystack_[0].location);
    }

    Expr expr = symbol.getExpr();
    (yylhs.value.expr) = new Expr(expr);
  }

    break;

  case 87:

    {
    if ((yystack_[1].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    (yylhs.value.expr) = (yystack_[1].value.expr);
  }

    break;

  case 88:

    {
    if ((yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check

    Expr expr = convertAndDelete((yystack_[0].value.expr));
    CHECK_IS_TENSOR(expr, yystack_[0].location);

    (yylhs.value.expr) = new Expr(ctx->getBuilder()->unaryElwiseExpr(IRBuilder::Neg, expr));
  }

    break;

  case 89:

    {  // + - .* ./
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check

    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));

    CHECK_IS_TENSOR(l, yystack_[2].location);
    CHECK_IS_TENSOR(r, yystack_[0].location);

    const TensorType *ltype = l.type().toTensor();
    const TensorType *rtype = r.type().toTensor();

    if (ltype->order()>0&&rtype->order()>0 && !compare(l.type(),r.type(),ctx)) {
        REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
    }

    BINARY_ELWISE_TYPE_CHECK(l.type(), r.type(), yystack_[1].location);
    (yylhs.value.expr) = new Expr(ctx->getBuilder()->binaryElwiseExpr(l, (yystack_[1].value.binop), r));
  }

    break;

  case 90:

    {
    iassert((yystack_[2].value.expr) && (yystack_[0].value.expr));
    IRBuilder *builder = ctx->getBuilder();

    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));

    CHECK_IS_TENSOR(l, yystack_[2].location);
    CHECK_IS_TENSOR(r, yystack_[0].location);

    const TensorType *ltype = l.type().toTensor();
    const TensorType *rtype = r.type().toTensor();

    // Scale
    if (ltype->order()==0 || rtype->order()==0) {
      (yylhs.value.expr) = new Expr(builder->binaryElwiseExpr(l, IRBuilder::Mul, r));
    }
    // Vector-Vector Multiplication (inner and outer product)
    else if (ltype->order() == 1 && rtype->order() == 1) {
      // Inner product
      if (!ltype->isColumnVector) {
        if (!rtype->isColumnVector) {
          REPORT_ERROR("cannot multiply two row vectors", yystack_[1].location);
        }
        if (l.type() != r.type()) {
          REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
        }
        (yylhs.value.expr) = new Expr(builder->innerProduct(l, r));
      }
      // Outer product (l is a column vector)
      else {
        if (rtype->isColumnVector) {
          REPORT_ERROR("cannot multiply two column vectors", yystack_[1].location);
        }
        if (l.type() != r.type()) {
          REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
        }
        (yylhs.value.expr) = new Expr(builder->outerProduct(l, r));
      }
    }
    // Matrix-Vector
    else if (ltype->order() == 2 && rtype->order() == 1) {
      // TODO: Figure out how column vectors should be handled here
      if (ltype->dimensions[1] != rtype->dimensions[0]){
        REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
      }
      (yylhs.value.expr) = new Expr(builder->gemv(l, r));
    }
    // Vector-Matrix
    else if (ltype->order() == 1 && rtype->order() == 2) {
      // TODO: Figure out how column vectors should be handled here
      if (ltype->dimensions[0] != rtype->dimensions[0]) {
        REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
      }
      (yylhs.value.expr) = new Expr(builder->gevm(l,r));
    }
    // Matrix-Matrix
    else if (ltype->order() == 2 && rtype->order() == 2) {
      if (ltype->dimensions[1] != rtype->dimensions[0]){
        REPORT_TYPE_MISSMATCH(l.type(), r.type(), yystack_[1].location);
      }
      (yylhs.value.expr) = new Expr(builder->gemm(l,r));
    }
    else {
      REPORT_ERROR("cannot multiply >2-order tensors using *", yystack_[1].location);
      (yylhs.value.expr) = NULL;
    }
  }

    break;

  case 91:

    {
    iassert((yystack_[2].value.expr) && (yystack_[0].value.expr));
    IRBuilder *builder = ctx->getBuilder();

    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));

    CHECK_IS_TENSOR(l, yystack_[2].location);
    CHECK_IS_TENSOR(r, yystack_[0].location);

    const TensorType *ltype = l.type().toTensor();
    const TensorType *rtype = r.type().toTensor();

    if (ltype->order()==0 || rtype->order()==0) {
      (yylhs.value.expr) = new Expr(builder->binaryElwiseExpr(l, IRBuilder::Div, r));
    }
    else {
      REPORT_ERROR("division not supported for these tensor types" , yystack_[2].location);
    }
  }

    break;

  case 92:

    {
    if ((yystack_[1].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    IRBuilder *builder = ctx->getBuilder();
    Expr expr = convertAndDelete((yystack_[1].value.expr));

    CHECK_IS_TENSOR(expr, yystack_[1].location);

    const TensorType *type = expr.type().toTensor();
    switch (type->order()) {
      case 0:
        // OPT: This might lead to redundant code to be removed in later pass
        (yylhs.value.expr) = new Expr(builder->unaryElwiseExpr(IRBuilder::None, expr));
        break;
      case 1:
        // OPT: This might lead to redundant code to be removed in later pass
        (yylhs.value.expr) = new Expr(builder->unaryElwiseExpr(IRBuilder::None, expr));
        if (!type->isColumnVector) {
          transposeVector(*(yylhs.value.expr));
        }
        break;
      case 2:
        (yylhs.value.expr) = new Expr(builder->transposedMatrix(expr));
        break;
      default:
        REPORT_ERROR("cannot transpose >2-order tensors using '", yystack_[1].location);
        (yylhs.value.expr) = NULL;
    }
  }

    break;

  case 93:

    {
    (yylhs.value.expr) = NULL;
    delete (yystack_[2].value.expr);
    delete (yystack_[0].value.expr);
  }

    break;

  case 94:

    {  // Solve
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    (yylhs.value.expr) = NULL;
    delete (yystack_[2].value.expr);
    delete (yystack_[0].value.expr);
  }

    break;

  case 95:

    { (yylhs.value.binop) = IRBuilder::Add; }

    break;

  case 96:

    { (yylhs.value.binop) = IRBuilder::Sub; }

    break;

  case 97:

    { (yylhs.value.binop) = IRBuilder::Mul; }

    break;

  case 98:

    { (yylhs.value.binop) = IRBuilder::Div; }

    break;

  case 99:

    {
    if ((yystack_[1].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    (yylhs.value.expr) = (yystack_[1].value.expr);
  }

    break;

  case 100:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Eq::make(l, r));
  }

    break;

  case 101:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Ne::make(l, r));
  }

    break;

  case 102:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Gt::make(l, r));
  }

    break;

  case 103:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Lt::make(l, r));
  }

    break;

  case 104:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Ge::make(l, r));
  }

    break;

  case 105:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Le::make(l, r));
  }

    break;

  case 106:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(And::make(l, r));
  }

    break;

  case 107:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Or::make(l, r));
  }

    break;

  case 108:

    {
    if ((yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Not::make(r));
  }

    break;

  case 109:

    {
    if ((yystack_[2].value.expr) == NULL || (yystack_[0].value.expr) == NULL) { (yylhs.value.expr) = NULL; break; } // TODO: Remove check
    Expr l = convertAndDelete((yystack_[2].value.expr));
    Expr r = convertAndDelete((yystack_[0].value.expr));
    (yylhs.value.expr) = new Expr(Xor::make(l, r));
  }

    break;

  case 110:

    {
    bool val = true;
    (yylhs.value.expr) = new Expr(Literal::make(TensorType::make(ScalarType::Boolean), &val));
  }

    break;

  case 111:

    {
    bool val = false;
    (yylhs.value.expr) = new Expr(Literal::make(TensorType::make(ScalarType::Boolean), &val));
  }

    break;

  case 112:

    {
    iassert((yystack_[2].value.expr));
    iassert((yystack_[2].value.expr)->type().defined());

    Expr elemOrSet = convertAndDelete((yystack_[2].value.expr));
    std::string fieldName = convertAndFree((yystack_[0].value.string));

    Type type = elemOrSet.type();
    if (!(type.isElement() || type.isSet())) {
      std::stringstream errorStr;
      errorStr << "only elements and sets have fields";
      REPORT_ERROR(errorStr.str(), yystack_[2].location);
    }

    const ElementType *elemType = nullptr;
    if (elemOrSet.type().isElement()) {
      elemType = elemOrSet.type().toElement();
    }
    else if (elemOrSet.type().isSet()) {
      const SetType *setType = elemOrSet.type().toSet();
      elemType = setType->elementType.toElement();
    }
    iassert(elemType);

    if (!elemType->hasField(fieldName)) {
      REPORT_ERROR("undefined field '" + toString(elemOrSet)+"."+fieldName+ "'",
                   yystack_[0].location);
    }

    (yylhs.value.expr) = new Expr(FieldRead::make(elemOrSet, fieldName));
  }

    break;

  case 116:

    {
    std::string name = convertAndFree((yystack_[3].value.string));
    auto indices = unique_ptr<vector<Expr>>((yystack_[1].value.exprs));

    if (ctx->hasSymbol(name)) {
      const Symbol &symbol = ctx->getSymbol(name);
      if (!symbol.isReadable()) {
        REPORT_ERROR(name + " is not readable", yystack_[3].location);
      }

      // The parenthesis read can read from a tensor or a tuple.
      auto expr = symbol.getExpr();
      if (expr.type().isTensor()) {
        (yylhs.value.expr) = new Expr(TensorRead::make(expr, *indices));
      }
      else if (expr.type().isTuple()) {
        if (indices->size() != 1) {
          REPORT_ERROR("reading a tuple requires exactly one index", yystack_[1].location);
        }
        (yylhs.value.expr) = new Expr(TupleRead::make(expr, (*indices)[0]));
      }
      else {
        REPORT_ERROR("can only access components in tensors and tuples", yystack_[3].location);
      }
    }
    else if (ctx->containsFunction(name)) {
      Func func = ctx->getFunction(name);
      (yylhs.value.expr) = new Expr(Call::make(func, *indices));
    }
    else {
      REPORT_ERROR(name + " is not defined in scope", yystack_[3].location);
    }
  }

    break;

  case 117:

    {
    (yylhs.value.expr) = NULL;
  }

    break;

  case 118:

    {
    (yylhs.value.exprs) = new vector<Expr>();
  }

    break;

  case 119:

    {
    (yylhs.value.exprs) = (yystack_[0].value.exprs);
  }

    break;

  case 120:

    {
    (yylhs.value.exprs) = new std::vector<Expr>();
    if ((yystack_[0].value.expr) == NULL) break;  // TODO: Remove check
    (yylhs.value.exprs)->push_back(*(yystack_[0].value.expr));
    delete (yystack_[0].value.expr);
  }

    break;

  case 121:

    {
    (yylhs.value.exprs) = (yystack_[2].value.exprs);
    if ((yystack_[0].value.expr) == NULL) break;  // TODO: Remove check
    (yylhs.value.exprs)->push_back(*(yystack_[0].value.expr));
    delete (yystack_[0].value.expr);
  }

    break;

  case 126:

    {
    std::string name = convertAndFree((yystack_[0].value.string));

    if (!ctx->containsElementType(name)) {
      REPORT_ERROR("undefined element type '" + name + "'" , yystack_[0].location);
    }

    (yylhs.value.type) = new Type(ctx->getElementType(name));
  }

    break;

  case 127:

    {
    auto elementType = convertAndDelete((yystack_[1].value.type));
    (yylhs.value.type) = new Type(SetType::make(elementType, {}));
  }

    break;

  case 128:

    {
    auto elementType = convertAndDelete((yystack_[4].value.type));
    auto endpoints = convertAndDelete((yystack_[1].value.exprs));

    // TODO: Add endpoint information to set type
    (yylhs.value.type) = new Type(SetType::make(elementType, endpoints));
  }

    break;

  case 129:

    {
    (yylhs.value.exprs) = new vector<Expr>;
    std::string name = convertAndFree((yystack_[0].value.string));

    if (!ctx->hasSymbol(name)) {
      REPORT_ERROR("undefined set type '" + name + "'" , yystack_[0].location);
    }
    (yylhs.value.exprs)->push_back(ctx->getSymbol(name).getExpr());
  }

    break;

  case 130:

    {
    (yylhs.value.exprs) = (yystack_[2].value.exprs);
    std::string name = convertAndFree((yystack_[0].value.string));

    if (!ctx->hasSymbol(name)) {
      REPORT_ERROR("undefined set type '" + name + "'" , yystack_[2].location);
    }
    (yylhs.value.exprs)->push_back(ctx->getSymbol(name).getExpr());
  }

    break;

  case 131:

    {
    auto elementType = convertAndDelete((yystack_[3].value.type));

    if ((yystack_[1].value.num)<1) {
      REPORT_ERROR("Must be 1 or greater", yystack_[2].location);
    }

    (yylhs.value.type) = new Type(TupleType::make(elementType, (yystack_[1].value.num)));
  }

    break;

  case 132:

    {
    auto componentType = convertAndDelete((yystack_[0].value.scalarType));
    (yylhs.value.type) = new Type(TensorType::make(componentType));
  }

    break;

  case 133:

    {
    (yylhs.value.type) = (yystack_[1].value.type);
  }

    break;

  case 134:

    {
    auto blockTypePtr = convertAndDelete((yystack_[1].value.type));
    const TensorType *blockType = blockTypePtr.toTensor();

    auto componentType = blockType->componentType;

    auto outerDimensions = unique_ptr<vector<IndexSet>>((yystack_[4].value.indexSets));
    auto blockDimensions = blockType->dimensions;

    vector<IndexDomain> dimensions;
    if (blockType->order() == 0) {
      for (size_t i=0; i<outerDimensions->size(); ++i) {
        dimensions.push_back(IndexDomain((*outerDimensions)[i]));
      }
    }
    else {
      // TODO: Handle the following cases where there there are more inner than
      //       outer dimensions (e.g. a vector of matrixes) and where there are
      //       more outer than inner dimensions (e.g. a matrix of vectors)
      //       gracefully by padding with '1'-dimensions.
      // TODO: Handle case where there are more block than outer dimensions
      // TODO: Handle case where there are more outer than block dimensions
      // TODO: Remove below error
//      if (blockType->order() != outerDimensions->size()) {
//        REPORT_ERROR("Blocktype order (" + to_string(blockType->order()) +
//                     ") differ from number of dimensions", @index_sets);
//      }

//      iassert(blockDimensions.size() == outerDimensions->size());
      for (size_t i=0; i < outerDimensions->size(); ++i) {
        vector<IndexSet> dimension;
        dimension.push_back((*outerDimensions)[i]);
        dimension.insert(dimension.end(),
                         blockDimensions[i].getIndexSets().begin(),
                         blockDimensions[i].getIndexSets().end());

        dimensions.push_back(IndexDomain(dimension));
      }
    }

    (yylhs.value.type) = new Type(TensorType::make(componentType, dimensions));
  }

    break;

  case 135:

    {
    auto type = convertAndDelete((yystack_[1].value.type));
    const TensorType *tensorType = type.toTensor();
    auto dimensions = tensorType->dimensions;
    auto componentType = tensorType->componentType;
    (yylhs.value.type) = new Type(TensorType::make(componentType, dimensions, true));
  }

    break;

  case 136:

    {
    (yylhs.value.indexSets) = new std::vector<IndexSet>();
    (yylhs.value.indexSets)->push_back(*(yystack_[0].value.indexSet));
    delete (yystack_[0].value.indexSet);
  }

    break;

  case 137:

    {
    (yylhs.value.indexSets) = (yystack_[2].value.indexSets);
    (yylhs.value.indexSets)->push_back(*(yystack_[0].value.indexSet));
    delete (yystack_[0].value.indexSet);
  }

    break;

  case 138:

    {
    (yylhs.value.indexSet) = new IndexSet((yystack_[0].value.num));
  }

    break;

  case 139:

    {
    std::string setName = convertAndFree((yystack_[0].value.string));

    if (!ctx->hasSymbol(setName)) {
      REPORT_ERROR("the set has not been declared", yystack_[0].location);
    }

    Expr set = ctx->getSymbol(setName).getExpr();
    if (!set.type().isSet()) {
      REPORT_ERROR("an index set must be a set, a range or dynamic (*)", yystack_[0].location);
    }

    (yylhs.value.indexSet) = new IndexSet(set);
  }

    break;

  case 140:

    {
    (yylhs.value.indexSet) = new IndexSet();
  }

    break;

  case 141:

    {
    (yylhs.value.scalarType) = new ScalarType(ScalarType::Int);
  }

    break;

  case 142:

    {
    (yylhs.value.scalarType) = new ScalarType(ScalarType::Float);
  }

    break;

  case 145:

    {
    (yylhs.value.expr) = (yystack_[1].value.expr);
    transposeVector(*(yylhs.value.expr));
  }

    break;

  case 147:

    {
    auto values = unique_ptr<TensorValues<double>>((yystack_[1].value.TensorDoubleValues));
    auto idoms = std::vector<IndexDomain>(values->dimSizes.rbegin(),
                                          values->dimSizes.rend());
    Type type = TensorType::make(ScalarType(ScalarType::Float), idoms);
    (yylhs.value.expr) = new Expr(Literal::make(type, values->values.data()));
  }

    break;

  case 148:

    {
    auto values = unique_ptr<TensorValues<int>>((yystack_[1].value.TensorIntValues));
    auto idoms = std::vector<IndexDomain>(values->dimSizes.rbegin(),
                                          values->dimSizes.rend());
    Type type = TensorType::make(ScalarType(ScalarType::Int), idoms);
    (yylhs.value.expr) = new Expr(Literal::make(type, values->values.data()));
  }

    break;

  case 149:

    {
    // If the matrix has only one column then we discard that dimension and
    // treat it as a vector.
    if ((yystack_[0].value.TensorDoubleValues)->dimSizes[(yystack_[0].value.TensorDoubleValues)->dimSizes.size()-1] == 1) {
      (yystack_[0].value.TensorDoubleValues)->dimSizes.pop_back();
    }
  }

    break;

  case 151:

    {
    (yylhs.value.TensorDoubleValues) = (yystack_[1].value.TensorDoubleValues);
    (yylhs.value.TensorDoubleValues)->addDimension();
  }

    break;

  case 152:

    {
    auto  left = unique_ptr<TensorValues<double>>((yystack_[4].value.TensorDoubleValues));
    auto right = unique_ptr<TensorValues<double>>((yystack_[1].value.TensorDoubleValues));

    string errorStr;
    if(!left->dimensionsMatch(*right, &errorStr)) {
      REPORT_ERROR(errorStr, yystack_[3].location);
    }
    left->merge(*right);
    (yylhs.value.TensorDoubleValues) = left.release();
  }

    break;

  case 153:

    {
    (yylhs.value.TensorDoubleValues) = (yystack_[0].value.TensorDoubleValues);
    (yylhs.value.TensorDoubleValues)->addDimension();
  }

    break;

  case 154:

    {
    auto  left = unique_ptr<TensorValues<double>>((yystack_[2].value.TensorDoubleValues));
    auto right = unique_ptr<TensorValues<double>>((yystack_[0].value.TensorDoubleValues));

    string errorStr;
    if(!left->dimensionsMatch(*right, &errorStr)) {
      REPORT_ERROR(errorStr, yystack_[1].location);
    }

    left->merge(*right);
    (yylhs.value.TensorDoubleValues) = left.release();
  }

    break;

  case 155:

    {
    (yylhs.value.TensorDoubleValues) = new TensorValues<double>();
    (yylhs.value.TensorDoubleValues)->addValue((yystack_[0].value.fnum));
  }

    break;

  case 156:

    {
    (yylhs.value.TensorDoubleValues) = (yystack_[2].value.TensorDoubleValues);
    (yylhs.value.TensorDoubleValues)->addValue((yystack_[0].value.fnum));
  }

    break;

  case 157:

    {
    // If the matrix has only one column then we discard that dimension and
    // treat it as a vector.
    if ((yystack_[0].value.TensorIntValues)->dimSizes[(yystack_[0].value.TensorIntValues)->dimSizes.size()-1] == 1) {
      (yystack_[0].value.TensorIntValues)->dimSizes.pop_back();
    }
  }

    break;

  case 159:

    {
    (yylhs.value.TensorIntValues) = (yystack_[1].value.TensorIntValues);
    (yylhs.value.TensorIntValues)->addDimension();
  }

    break;

  case 160:

    {
    auto  left = unique_ptr<TensorValues<int>>((yystack_[4].value.TensorIntValues));
    auto right = unique_ptr<TensorValues<int>>((yystack_[1].value.TensorIntValues));

    string errorStr;
    if(!left->dimensionsMatch(*right, &errorStr)) {
      REPORT_ERROR(errorStr, yystack_[3].location);
    }
    left->merge(*right);
    (yylhs.value.TensorIntValues) = left.release();
  }

    break;

  case 161:

    {
    (yylhs.value.TensorIntValues) = (yystack_[0].value.TensorIntValues);
    (yylhs.value.TensorIntValues)->addDimension();
  }

    break;

  case 162:

    {
    auto  left = unique_ptr<TensorValues<int>>((yystack_[2].value.TensorIntValues));
    auto right = unique_ptr<TensorValues<int>>((yystack_[0].value.TensorIntValues));

    string errorStr;
    if(!left->dimensionsMatch(*right, &errorStr)) {
      REPORT_ERROR(errorStr, yystack_[1].location);
    }

    left->merge(*right);
    (yylhs.value.TensorIntValues) = left.release();
  }

    break;

  case 163:

    {
    (yylhs.value.TensorIntValues) = new TensorValues<int>();
    (yylhs.value.TensorIntValues)->addValue((yystack_[0].value.num));
  }

    break;

  case 164:

    {
    (yylhs.value.TensorIntValues) = (yystack_[2].value.TensorIntValues);
    (yylhs.value.TensorIntValues)->addValue((yystack_[0].value.num));
  }

    break;

  case 165:

    {
    auto scalarTensorType = TensorType::make(ScalarType(ScalarType::Int));
    (yylhs.value.expr) = new Expr(Literal::make(scalarTensorType, &(yystack_[0].value.num)));
  }

    break;

  case 166:

    {
    auto scalarTensorType = TensorType::make(ScalarType(ScalarType::Float));
    (yylhs.value.expr) = new Expr(Literal::make(scalarTensorType, &(yystack_[0].value.fnum)));
  }

    break;

  case 167:

    {
    (yylhs.value.num) = (yystack_[0].value.num);
  }

    break;

  case 168:

    {
    (yylhs.value.num) = -(yystack_[0].value.num);
  }

    break;

  case 169:

    {
    (yylhs.value.fnum) = (yystack_[0].value.fnum);
  }

    break;

  case 170:

    {
    (yylhs.value.fnum) = -(yystack_[0].value.fnum);
  }

    break;

  case 171:

    {
    std::string name = convertAndFree((yystack_[6].value.string));
    auto actuals = unique_ptr<vector<Expr>>((yystack_[4].value.exprs));
    auto expected = convertAndDelete((yystack_[1].value.expr));

    std::vector<Expr> literalArgs;
    literalArgs.reserve(actuals->size());
    for (auto &arg : *actuals) {
      if (!isa<Literal>(arg)) {
        REPORT_ERROR("function calls in tests must have literal arguments", yystack_[7].location);
      }
      literalArgs.push_back(arg);
    }

    std::vector<Expr> expecteds;
    expecteds.push_back(expected);
    ctx->addTest(new FunctionTest(name, literalArgs, expecteds));
  }

    break;

  case 172:

    {
    std::string setName = convertAndFree((yystack_[4].value.string));
    unique_ptr<System> system((yystack_[2].value.system));

    //std::map<std::string, simit::SetBase*> externs;
    //externs[setName] = system->elements;
    //ctx->addTest(new ProcedureTest("test", externs));
  }

    break;

  case 174:

    {
    System *sys = new System;
    //sys->elements = new simit::Set<>;
    //createElements(sys->elements, $numElems);
    (yylhs.value.system) = sys;
  }

    break;



            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int  Parser ::yypact_ninf_ = -221;

  const short int  Parser ::yytable_ninf_ = -140;

  const short int
   Parser ::yypact_[] =
  {
    -221,   197,  -221,  -221,  -221,    85,    67,    72,    29,   427,
     427,   121,   155,   427,   427,    18,  -221,   444,   427,  -221,
    -221,  -221,  -221,  -221,  -221,    25,  -221,   159,  -221,  -221,
    -221,   -20,  -221,  -221,  -221,    28,  -221,  -221,   391,  -221,
    -221,  -221,   475,   137,   140,  -221,  -221,   151,   148,   158,
    -221,  -221,   144,  -221,  -221,  -221,  -221,   427,   189,  -221,
     160,   164,   205,   168,   188,   699,   352,   311,   198,    40,
     502,   531,   190,    36,   100,   195,   185,   191,   192,   200,
     196,   194,   199,  -221,  -221,  -221,  -221,   135,   699,   225,
      28,   230,    28,   235,   414,  -221,    28,  -221,   214,   375,
     130,  -221,   558,    28,   427,   427,   427,   427,  -221,  -221,
    -221,   427,   427,  -221,  -221,   427,  -221,   427,   427,   427,
     427,   427,   427,   427,   427,   239,  -221,   699,   211,    57,
      41,    24,   206,   111,   204,  -221,   427,  -221,   193,  -221,
     427,   134,  -221,  -221,  -221,    11,    44,  -221,  -221,  -221,
     217,    21,    21,  -221,   222,    15,    15,  -221,   221,   231,
     237,  -221,   262,   587,  -221,  -221,  -221,   427,   240,   755,
     755,   120,   120,   135,   135,   135,   726,   777,   777,   120,
     120,   699,   699,   233,   228,  -221,  -221,   232,   427,   427,
     427,   227,  -221,  -221,  -221,  -221,   127,    51,  -221,  -221,
     236,   272,  -221,  -221,  -221,  -221,   226,   111,   427,    28,
     250,   247,  -221,  -221,   242,  -221,  -221,    21,   281,   192,
    -221,    15,   285,   199,  -221,  -221,    29,  -221,   254,  -221,
     249,  -221,  -221,  -221,   427,   699,    88,   614,   206,   206,
      30,    34,  -221,   272,   243,  -221,   311,  -221,  -221,   261,
     286,   105,   106,  -221,   280,   276,  -221,  -221,   427,   300,
     259,   240,   643,   277,  -221,    -5,   -10,  -221,  -221,     8,
    -221,   279,   287,   325,   193,    34,   288,  -221,  -221,  -221,
     295,    29,   294,   327,  -221,  -221,   427,  -221,  -221,   296,
      30,  -221,   299,   304,  -221,   297,   336,   310,  -221,  -221,
    -221,   328,   670,   206,  -221,   341,  -221,  -221,   302,   345,
     346,   330,  -221,    26,  -221,   113,    34,   309,   123,  -221,
    -221,   313,  -221,  -221,  -221,   353,   329,   111,  -221,   345,
    -221,  -221,  -221,    34,  -221,  -221,  -221
  };

  const unsigned char
   Parser ::yydefact_[] =
  {
       2,    15,     1,   167,   169,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    77,     0,     0,   110,
     111,     3,     7,     4,     5,     0,     6,     0,     8,    38,
      39,     0,    40,    41,    43,    34,    42,    44,     0,    45,
      46,    47,     0,    79,    80,    82,    83,    84,     0,    85,
      81,   143,   144,   146,   165,   166,     9,   118,     0,    12,
       0,     0,     0,     0,    86,     0,    83,    83,     0,     0,
       0,     0,    83,     0,     0,     0,   150,   149,   153,     0,
     158,   157,   161,   163,   155,   167,   169,    88,   108,     0,
      34,     0,    34,     0,     0,    64,    35,    36,     0,   167,
      86,   140,     0,    34,     0,     0,     0,     0,    76,    95,
      96,     0,     0,    97,    98,     0,    92,     0,     0,     0,
       0,     0,     0,     0,   118,     0,   145,   120,     0,     0,
       0,     0,     0,     0,     0,    10,   118,    67,    68,    73,
     118,     0,    78,    87,    99,     0,     0,   168,   170,   147,
       0,     0,     0,   148,     0,     0,     0,    18,     0,     0,
       0,    53,     0,     0,    37,    65,    62,     0,     0,   106,
     107,   103,   102,    90,    91,    93,    94,   100,   101,   105,
     104,   109,    89,     0,   119,   112,   116,     0,     0,     0,
       0,     0,    11,    13,   141,   142,     0,     0,   132,   126,
       0,     0,    28,   122,   123,   124,   125,     0,     0,    34,
       0,     0,   174,   173,     0,   151,   159,     0,     0,   154,
     156,     0,     0,   162,   164,    16,    23,    20,    50,    48,
      34,    74,    71,   117,     0,   121,     0,     0,     0,     0,
       0,     0,   135,     0,     0,    27,    83,    69,    66,     0,
       0,     0,     0,    17,     0,    24,    25,    21,   118,     0,
      96,     0,     0,     0,    59,     0,     0,   138,   139,     0,
     136,     0,     0,     0,    68,     0,     0,   172,   152,   160,
      29,     0,     0,     0,    72,    60,     0,    14,   133,     0,
       0,    75,   127,     0,    70,     0,     0,     0,    22,    26,
      51,    54,     0,     0,   137,     0,   131,   171,     0,     0,
       0,    56,    61,     0,   129,     0,     0,     0,     0,    31,
      55,     0,    49,   134,   128,     0,     0,     0,    30,     0,
      58,    57,   130,     0,    33,    32,   175
  };

  const short int
   Parser ::yypgoto_[] =
  {
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -208,  -221,  -221,
      37,   -23,  -221,    20,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,   117,    91,
    -221,  -221,   108,  -221,  -221,  -221,    -9,  -221,  -221,  -221,
    -221,     1,  -221,  -221,  -221,  -110,   -40,  -191,  -156,  -221,
    -221,  -221,  -119,  -221,  -220,  -221,  -221,  -216,  -221,  -221,
    -221,   -66,   216,  -221,  -221,   -67,   215,  -221,   -13,   -12,
    -221,  -221,  -221
  };

  const short int
   Parser ::yydefgoto_[] =
  {
      -1,     1,    21,    22,    23,   131,   193,    24,    25,   253,
      90,    26,    27,   257,    92,   254,   255,    63,   298,   318,
     319,   137,    96,    97,    29,    30,   259,    31,   311,   322,
     331,    32,    33,    34,    35,    98,   166,    36,   138,   210,
      37,    38,   232,    39,    40,    41,    42,    43,    44,    45,
     123,    46,    47,    48,    49,   128,   184,   202,   203,   204,
     315,   205,   206,   269,   103,   198,    50,    51,    52,    75,
      76,    77,    78,    79,    80,    81,    82,    53,    54,    55,
      56,   214,   277
  };

  const short int
   Parser ::yytable_[] =
  {
      65,    65,    83,    84,    70,    71,   146,   145,    87,    88,
      66,    67,    95,   197,   183,    72,   245,   129,   256,     3,
     270,    28,     3,     4,    93,   271,     4,   288,    94,   102,
     211,   191,     3,     4,   267,     5,    61,   268,     3,     4,
       3,     4,   287,    89,     7,   244,   242,   289,   127,    62,
     215,   242,   290,     9,    10,   192,    73,    11,   151,   295,
      83,    84,    13,   323,    14,   222,    15,   158,    74,   160,
     304,   218,    15,   299,    59,    16,   140,   189,    17,    60,
     168,   101,   242,   216,    74,   163,    74,   272,   141,   190,
      18,   155,    19,    20,   187,   169,   170,   171,   172,   241,
     326,   188,   173,   174,   147,   148,   175,   242,   176,   177,
     178,   179,   180,   181,   182,   127,   164,   336,   199,   265,
     266,    57,   194,   195,   196,   263,   200,   127,    68,   -52,
      58,   127,   188,   -52,  -139,  -139,   334,  -139,   212,    84,
     220,   213,    83,   224,   278,   279,  -139,   201,   282,   236,
     324,   251,   151,   155,   252,  -139,  -139,   325,   230,  -139,
     328,  -139,    69,   239,  -139,   240,   136,   329,  -139,   109,
     110,   111,   112,   113,   114,   115,   116,  -139,    91,   235,
     127,   237,  -113,   122,   313,  -114,   247,   124,   113,   114,
     115,   116,  -139,   125,  -139,  -139,   130,     2,   122,    65,
     126,     3,     4,  -115,     5,    84,   132,   261,    83,   246,
     133,     6,   134,     7,     8,   135,   -19,   194,   195,   196,
     208,   209,     9,    10,   136,   262,    11,   144,   139,   150,
      12,    13,   157,    14,   149,    15,   152,   159,   151,   153,
     154,   155,   161,   156,    16,   165,   185,    17,   186,   127,
     207,    87,   225,     3,     4,   217,     5,   104,   105,    18,
     221,    19,    20,    85,    86,     7,    64,   226,   227,   228,
     233,   231,   188,   238,     9,    10,   243,   302,    11,   199,
     234,   248,   242,    13,   249,    14,   148,    15,   250,   147,
     258,   106,   107,   276,   273,    14,    16,    15,   109,   260,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    18,   122,    19,    20,     3,     4,   280,     5,   275,
     281,    18,   283,    19,    20,   286,   291,     7,   292,   293,
     297,   300,   303,   296,   301,   305,     9,    10,   -34,   -34,
      11,   306,   -34,   308,   307,    13,   309,    14,   314,    15,
     316,   310,   317,   320,   321,   327,   -63,   -63,    16,   -63,
     332,    17,   330,   274,   333,   294,   335,   219,   -63,   284,
     223,     0,     0,    18,     0,    19,    20,   -63,   -63,  -138,
    -138,   -63,  -138,   -63,     0,     0,   -63,     0,   -63,     0,
     -63,  -138,     0,     0,     0,    99,     4,     0,   100,   -63,
    -138,  -138,   -63,     0,  -138,     0,  -138,     0,     0,  -138,
       0,  -138,     0,  -138,   -63,     0,   -63,   -63,     3,     4,
       0,    64,  -138,     0,     0,  -138,     0,    14,     0,    15,
       0,     3,     4,     0,    64,   162,     0,  -138,     0,  -138,
    -138,    17,   101,     0,     0,     0,     0,     0,    85,    86,
      14,    64,    15,    18,     0,    19,    20,     0,     0,     0,
       0,     0,     0,    14,    17,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    17,    19,    20,
      14,     0,    15,   104,   105,     0,     0,     0,     0,    18,
       0,    19,    20,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,    19,    20,
     104,   105,     0,     0,     0,     0,     0,   106,   107,     0,
       0,     0,   108,     0,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,   122,   104,
     105,     0,     0,     0,   106,   107,     0,     0,     0,   142,
       0,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,   122,   104,   105,   143,     0,
       0,     0,     0,   106,   107,     0,     0,     0,     0,     0,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,   122,   104,   105,     0,     0,     0,
     106,   107,     0,     0,   167,     0,     0,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
       0,   122,   104,   105,     0,     0,     0,     0,     0,   106,
     107,     0,     0,     0,   229,     0,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
     122,   104,   105,     0,     0,     0,   106,   107,     0,     0,
       0,   264,     0,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,     0,   122,   104,   105,
       0,     0,     0,     0,     0,   106,   107,     0,     0,     0,
     285,     0,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,     0,   122,   104,   105,     0,
       0,     0,   106,   107,     0,     0,     0,   312,     0,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,     0,   122,   104,   105,     0,     0,     0,     0,
       0,   106,   107,     0,     0,     0,     0,     0,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,   122,   104,   105,     0,     0,     0,   106,   107,
       0,     0,     0,     0,     0,   109,   110,   111,   112,   113,
     114,   115,   116,  -140,   118,   119,   120,   121,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   106,   107,     0,
       0,     0,     0,     0,   109,   110,   111,   112,   113,   114,
     115,   116,     0,   118,   119,   120,   121,     0,   122,   106,
     107,     0,     0,     0,     0,     0,   109,   110,   111,   112,
     113,   114,   115,   116,     0,     0,     0,   120,   121,     0,
     122
  };

  const short int
   Parser ::yycheck_[] =
  {
       9,    10,    15,    15,    13,    14,    73,    73,    17,    18,
       9,    10,    35,   132,   124,    14,   207,    57,   226,     4,
     240,     1,     4,     5,    44,   241,     5,    37,    48,    38,
     140,     7,     4,     5,     4,     7,     7,     7,     4,     5,
       4,     5,    47,    18,    16,   201,    56,    39,    57,    20,
      39,    56,    44,    25,    26,    31,    38,    29,    47,   275,
      73,    73,    34,    37,    36,    50,    38,    90,    50,    92,
     290,    50,    38,   281,     7,    47,    36,    36,    50,     7,
     103,    51,    56,    39,    50,    94,    50,   243,    48,    48,
      62,    47,    64,    65,    37,   104,   105,   106,   107,    48,
     316,    44,   111,   112,     4,     5,   115,    56,   117,   118,
     119,   120,   121,   122,   123,   124,    96,   333,     7,   238,
     239,    36,    11,    12,    13,    37,    15,   136,     7,    44,
      45,   140,    44,    48,     4,     5,   327,     7,     4,   151,
     152,     7,   155,   156,    39,    39,    16,    36,   258,   189,
      37,   217,    47,    47,   221,    25,    26,    44,   167,    29,
      37,    31,     7,    36,    34,    38,    36,    44,    38,    49,
      50,    51,    52,    53,    54,    55,    56,    47,    19,   188,
     189,   190,    45,    63,   303,    45,   209,    36,    53,    54,
      55,    56,    62,    45,    64,    65,     7,     0,    63,   208,
      56,     4,     5,    45,     7,   217,    46,   230,   221,   208,
      46,    14,     7,    16,    17,    47,    19,    11,    12,    13,
      27,    28,    25,    26,    36,   234,    29,    37,    30,    44,
      33,    34,     7,    36,    39,    38,    44,     7,    47,    39,
      44,    47,     7,    44,    47,    31,     7,    50,    37,   258,
      46,   260,    31,     4,     5,    38,     7,     8,     9,    62,
      38,    64,    65,     4,     5,    16,     7,    36,    31,     7,
      37,    31,    44,    46,    25,    26,    40,   286,    29,     7,
      48,    31,    56,    34,    37,    36,     5,    38,    46,     4,
      36,    42,    43,     7,    51,    36,    47,    38,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     4,     5,    37,     7,    58,
      44,    62,    22,    64,    65,    48,    47,    16,    41,     4,
      35,    37,    36,    45,     7,    36,    25,    26,    27,    28,
      29,    37,    31,     7,    47,    34,    36,    36,     7,    38,
      48,    23,     7,     7,    24,    46,     4,     5,    47,     7,
       7,    50,    49,   246,    35,   274,   329,   151,    16,   261,
     155,    -1,    -1,    62,    -1,    64,    65,    25,    26,     4,
       5,    29,     7,    31,    -1,    -1,    34,    -1,    36,    -1,
      38,    16,    -1,    -1,    -1,     4,     5,    -1,     7,    47,
      25,    26,    50,    -1,    29,    -1,    31,    -1,    -1,    34,
      -1,    36,    -1,    38,    62,    -1,    64,    65,     4,     5,
      -1,     7,    47,    -1,    -1,    50,    -1,    36,    -1,    38,
      -1,     4,     5,    -1,     7,    21,    -1,    62,    -1,    64,
      65,    50,    51,    -1,    -1,    -1,    -1,    -1,     4,     5,
      36,     7,    38,    62,    -1,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    50,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    50,    64,    65,
      36,    -1,    38,     8,     9,    -1,    -1,    -1,    -1,    62,
      -1,    64,    65,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,
       8,     9,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    63,     8,
       9,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,     8,     9,    37,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    63,     8,     9,    -1,    -1,    -1,
      42,    43,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    63,     8,     9,    -1,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      63,     8,     9,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,     8,     9,
      -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      47,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    63,     8,     9,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,     8,     9,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    63,     8,     9,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    61,    -1,    63,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    60,    61,    -1,
      63
  };

  const unsigned char
   Parser ::yystos_[] =
  {
       0,    67,     0,     4,     5,     7,    14,    16,    17,    25,
      26,    29,    33,    34,    36,    38,    47,    50,    62,    64,
      65,    68,    69,    70,    73,    74,    77,    78,    89,    90,
      91,    93,    97,    98,    99,   100,   103,   106,   107,   109,
     110,   111,   112,   113,   114,   115,   117,   118,   119,   120,
     132,   133,   134,   143,   144,   145,   146,    36,    45,     7,
       7,     7,    20,    83,     7,   112,   117,   117,     7,     7,
     112,   112,   117,    38,    50,   135,   136,   137,   138,   139,
     140,   141,   142,   144,   145,     4,     5,   112,   112,    18,
      76,    19,    80,    44,    48,    87,    88,    89,   101,     4,
       7,    51,   112,   130,     8,     9,    42,    43,    47,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    63,   116,    36,    45,    56,   112,   121,   122,
       7,    71,    46,    46,     7,    47,    36,    87,   104,    30,
      36,    48,    47,    37,    37,   137,   141,     4,     5,    39,
      44,    47,    44,    39,    44,    47,    44,     7,    87,     7,
      87,     7,    21,   112,    89,    31,   102,    46,    87,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   121,   122,     7,    37,    37,    44,    36,
      48,     7,    31,    72,    11,    12,    13,   128,   131,     7,
      15,    36,   123,   124,   125,   127,   128,    46,    27,    28,
     105,   121,     4,     7,   147,    39,    39,    38,    50,   138,
     145,    38,    50,   142,   144,    31,    36,    31,     7,    47,
     112,    31,   108,    37,    48,   112,   122,   112,    46,    36,
      38,    48,    56,    40,   124,   123,   117,    87,    31,    37,
      46,   137,   141,    75,    81,    82,    83,    79,    36,    92,
      50,    87,   112,    37,    47,   128,   128,     4,     7,   129,
     130,   133,   124,    51,   104,    58,     7,   148,    39,    39,
      37,    44,   121,    22,   108,    47,    48,    47,    37,    39,
      44,    47,    41,     4,   105,   133,    45,    35,    84,    83,
      37,     7,   112,    36,   130,    36,    37,    47,     7,    36,
      23,    94,    47,   128,     7,   126,    48,     7,    85,    86,
       7,    24,    95,    37,    37,    44,   133,    46,    37,    44,
      49,    96,     7,    35,   123,    86,   133
  };

  const unsigned char
   Parser ::yyr1_[] =
  {
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      69,    70,    71,    71,    72,    74,    75,    73,    76,    78,
      79,    77,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    87,    87,    88,    88,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    90,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    96,    97,
      98,    98,    99,   100,   101,   102,   103,   104,   105,   105,
     105,   106,   106,   107,   108,   109,   110,   110,   111,   112,
     112,   112,   112,   112,   112,   112,   113,   114,   115,   115,
     115,   115,   115,   115,   115,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   118,   119,   119,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   123,   124,   125,   125,   126,
     126,   127,   128,   128,   128,   128,   129,   129,   130,   130,
     130,   131,   131,   132,   133,   133,   133,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   146,   146,   147,   147,   148
  };

  const unsigned char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       3,     4,     0,     2,     4,     0,     0,     5,     2,     0,
       0,     5,     6,     0,     1,     1,     3,     4,     3,     0,
       4,     1,     3,     3,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     9,
       0,     3,     1,     3,     0,     2,     0,     2,     1,     6,
       7,     9,     3,     2,     1,     1,     5,     1,     0,     2,
       4,     4,     6,     3,     1,     7,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       3,     3,     2,     3,     3,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     3,     1,     1,     1,     4,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     4,     7,     1,
       3,     5,     1,     4,     7,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     3,     1,
       1,     3,     5,     1,     3,     1,     3,     1,     1,     3,
       5,     1,     3,     1,     3,     1,     1,     1,     2,     1,
       2,     8,     6,     1,     1,     7
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "UNKNOWN", "\"int literal\"",
  "\"float literal\"", "\"string literal\"", "\"identifier\"", "\"and\"",
  "\"or\"", "NEG", "\"int\"", "\"float\"", "\"tensor\"", "\"element\"",
  "\"set\"", "\"const\"", "\"extern\"", "\"proc\"", "\"func\"",
  "\"inout\"", "\"map\"", "\"to\"", "\"with\"", "\"reduce\"", "\"while\"",
  "\"if\"", "\"elif\"", "\"else\"", "\"for\"", "\"in\"", "\"end\"",
  "\"return\"", "\"%!\"", "\"print\"", "\"->\"", "\"(\"", "\")\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"<\"", "\">\"", "\",\"", "\".\"", "\":\"",
  "\";\"", "\"=\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\".*\"", "\"./\"",
  "\"^\"", "\"'\"", "\"\\\\\"", "\"==\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"not\"", "\"xor\"", "\"true\"", "\"false\"", "$accept", "program",
  "program_element", "extern", "element_type_decl", "field_decl_list",
  "field_decl", "procedure", "$@1", "$@2", "procedure_header", "function",
  "$@3", "$@4", "function_header", "arguments", "argument_list",
  "argument_decl", "results", "result_list", "result_decl", "stmt_block",
  "stmts", "stmt", "assign_stmt", "map_stmt", "partial_expr_list",
  "idents", "with", "reduce", "reduce_op", "field_write_stmt",
  "tensor_write_stmt", "while_stmt", "while_stmt_header", "while_body",
  "while_end", "if_stmt", "if_body", "else_clauses", "for_stmt",
  "for_stmt_header", "for_stmt_footer", "const_stmt", "expr_stmt",
  "print_stmt", "expr", "ident_expr", "paren_expr", "linear_algebra_expr",
  "elwise_binary_op", "boolean_expr", "field_read_expr", "set_read_expr",
  "call_or_paren_read_expr", "expr_list_or_empty", "expr_list", "type",
  "element_type", "set_type", "endpoints", "tuple_type", "tensor_type",
  "index_sets", "index_set", "component_type", "literal_expr",
  "tensor_literal", "dense_tensor_literal", "float_dense_tensor_literal",
  "float_dense_ndtensor_literal", "float_dense_matrix_literal",
  "float_dense_vector_literal", "int_dense_tensor_literal",
  "int_dense_ndtensor_literal", "int_dense_matrix_literal",
  "int_dense_vector_literal", "scalar_literal", "signed_int_literal",
  "signed_float_literal", "test", "system_generator", "extern_assert", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   Parser ::yyrline_[] =
  {
       0,   279,   279,   281,   284,   285,   293,   301,   302,   303,
     308,   318,   331,   334,   342,   352,   352,   352,   360,   377,
     377,   377,   385,   419,   422,   428,   433,   441,   448,   458,
     461,   467,   472,   480,   490,   493,   500,   501,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   518,   559,
     614,   617,   624,   628,   635,   638,   651,   654,   660,   665,
     685,   705,   732,   742,   749,   755,   761,   774,   780,   783,
     788,   800,   808,   818,   830,   835,   863,   866,   871,   879,
     880,   881,   882,   883,   884,   885,   891,   911,   920,   928,
     947,  1015,  1035,  1063,  1068,  1077,  1078,  1079,  1080,  1086,
    1090,  1096,  1102,  1108,  1114,  1120,  1126,  1132,  1138,  1143,
    1149,  1153,  1161,  1195,  1196,  1197,  1203,  1236,  1258,  1261,
    1267,  1273,  1284,  1285,  1286,  1287,  1291,  1303,  1307,  1317,
    1326,  1338,  1350,  1354,  1357,  1399,  1409,  1414,  1422,  1425,
    1439,  1445,  1448,  1498,  1502,  1503,  1507,  1511,  1518,  1529,
    1536,  1540,  1544,  1558,  1562,  1577,  1581,  1588,  1595,  1599,
    1603,  1617,  1621,  1636,  1640,  1647,  1651,  1658,  1661,  1667,
    1670,  1677,  1696,  1720,  1721,  1729
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
   Parser ::token_number_type
   Parser ::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
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
      65
    };
    const unsigned int user_token_number_max_ = 320;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} } //  simit::internal 



