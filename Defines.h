#pragma once

#include <iostream>
#include <map>
#include <cmath>

enum Tag {
	NONE = 0,
	UADD, USUB, ADD, SUB, DIV, MUL, FRAC, POW,
	LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
	SET, COMMA, BREAK, INDEX, AMP,
	WHILE, IF, ELSE, WHEN, OTHERWISE, ALT,
	BEGIN, END,
	BEGINB, ENDB, BEGINC, ENDC, BEGINM, ENDM,
	LT, GT, LEQ, GEQ, NEQ, EQ,
	OR, AND, NOT,
	NUMBER, IDENT, KEYWORD, FUNC,
	ERROR, SPACE,
	PLACEHOLDER, TEXT, LIST, ROOT,
	GRAPHIC, RANGE, TRANSP,
};

typedef struct Tag_info {
	std::string name = "NONE";
	int priority = 0;
	Tag close_tag = NONE;
	Tag alternative_tag = NONE;
	bool is_operator = false;
	bool is_binary = false;
	bool is_inverted = false;
	Tag_info(std::string n = "NONE", int p = 0, Tag ct = NONE, Tag at = NONE, bool op = false, bool bin = false, bool inv = false) :
		name(n), priority(p), close_tag(ct), alternative_tag(at), is_operator(op), is_binary(bin), is_inverted(inv) {}
} Tag_info;

std::map<Tag, Tag_info> t_info = {
	//простые элементы
	{ NUMBER,   Tag_info("NUMBER", 0, NONE, NONE) },
	{ IDENT,    Tag_info("IDENT", 0, NONE, NONE) },
	{ KEYWORD,  Tag_info("KEYWORD", 0, NONE, NONE) },
	{ TEXT,    Tag_info("TEXT", 0, NONE, NONE) },
	{ FUNC,  Tag_info("FUNC", 0, NONE, NONE) },

	//разделители
	{ COMMA, Tag_info("COMMA", 0, NONE, NONE) },
	{ AMP, Tag_info("AMP", 0, NONE, NONE) },
	{ INDEX,    Tag_info("INDEX", 228, NONE, NONE) },

	//скобки
	{ BEGIN, Tag_info("BEGIN", 0, END, NONE) },
	{ END,   Tag_info("END", 0, NONE, NONE) },
	{ BEGINB,Tag_info("BEGINB", 0, ENDB, NONE) },
	{ ENDB,  Tag_info("ENDB", 0, NONE, NONE) },
	{ BEGINC,Tag_info("BEGINC", 0, ENDC, NONE) },
	{ ENDC,  Tag_info("ENDC", 0, NONE, NONE) },
	{ BEGINM,Tag_info("BEGINM", 0, ENDM, NONE) },
	{ ENDM,  Tag_info("ENDM", 0, NONE, NONE) },
	{ LPAREN,  Tag_info("LPAREN", 0, RPAREN, NONE) },
	{ RPAREN,  Tag_info("RPAREN", 0, NONE, NONE) },
	{ LBRACE,Tag_info("LBRACE", 0, RBRACE, NONE) },
	{ RBRACE,Tag_info("RBRACE", 0, NONE, NONE) },
	{ LBRACKET,Tag_info("LBRACKET", 0, RBRACKET, NONE) },
	{ RBRACKET,Tag_info("RBRACKET", 0, NONE, NONE) },

	//операторы
	{ ADD,   Tag_info("ADD", 110, NONE, UADD, true, true, false) },
	{ SUB,   Tag_info("SUB", 110, NONE, USUB, true, true, false) },
	{ MUL,   Tag_info("MUL", 120, NONE, NONE, true, true, false) },
	{ DIV,   Tag_info("DIV", 120, NONE, NONE, true, true, false) },
	{ UADD,  Tag_info("UADD", 130, NONE, ADD, true, false, false) },
	{ USUB,  Tag_info("USUB", 130, NONE, SUB, true, false, false) },
	{ NOT,  Tag_info("NOT", 130, NONE, NONE, true, false, false) },
	{ FRAC,  Tag_info("FRAC", 140, NONE, NONE, true, false, false) },
	{ POW,   Tag_info("POW", 150, NONE, NONE, true, false, false) },

	//операторы сравнения
	{ EQ,    Tag_info("EQ", 90, NONE, NONE, true, true, false) },
	{ NEQ,   Tag_info("NEQ", 90, NONE, NONE, true, true, false) },
	{ LEQ,   Tag_info("LEQ", 100, NONE, NONE, true, true, false) },
	{ GEQ,   Tag_info("GEQ", 100, NONE, NONE, true, true, false) },
	{ LT,    Tag_info("LT", 100, NONE, NONE, true, true, false) },
	{ GT,    Tag_info("GT", 100, NONE, NONE, true, true, false) },

	//логические операторы
	{ OR,    Tag_info("OR", 70, NONE, NONE, true, true, false) },
	{ AND,   Tag_info("AND", 80, NONE, NONE, true, true, false) },
	{ NOT,   Tag_info("NOT", 130, NONE, NONE, true, true, false) },

	{ SET,   Tag_info("SET", 60, NONE, NONE, true, true, false) },

	{ IF,    Tag_info("IF", 0, NONE, NONE) },
	{ WHILE, Tag_info("WHILE", 0, NONE, NONE) },
	{ ELSE,  Tag_info("ELSE", 0, NONE, NONE) },
	{ WHEN,  Tag_info("WHEN", 0, NONE, NONE) },
	{ OTHERWISE, Tag_info("OTHERWISE", 0, NONE, NONE) },
	{ ALT,   Tag_info("ALT", 0, NONE, NONE) },
	{ BREAK, Tag_info("BREAK", 0, NONE, NONE) },

	{ PLACEHOLDER, Tag_info("PLACEHOLDER", 0, NONE, NONE) },
	{ LIST, Tag_info("LIST", 0, NONE, NONE) },
	{ ROOT, Tag_info("ROOT", 0, NONE, NONE) },
	{ ERROR, Tag_info("ERROR", 0, NONE, ERROR) },
	{ SPACE, Tag_info("SPACE", 0, NONE, NONE) },
	{ GRAPHIC, Tag_info("GRAPHIC", 0, NONE, NONE) },
	{ RANGE, Tag_info("RANGE", 0, NONE, NONE) },
	{ TRANSP, Tag_info("TRANSP", 0, NONE, NONE) },
};


std::map<std::string, enum Tag> raw_tag = {
	{ "\\\\", Tag::BREAK },
	{ "\\begin", Tag::BEGIN },
	{ "\\end", Tag::END },
	{ "\\placeholder", Tag::PLACEHOLDER },
	{ "\\text", Tag::TEXT },
	{ "\\cdot", Tag::MUL },
	{ "\\times", Tag::MUL },
	{ "\\frac", Tag::FRAC },
	{ "\\eq", Tag::EQ },
	{ "\\neq", Tag::NEQ },
	{ "\\leq", Tag::LEQ },
	{ "\\geq", Tag::GEQ },
	{ "\\neg", Tag::NOT },
	{ "\\lor", Tag::OR },
	{ "\\vee", Tag::OR },
	{ "\\land", Tag::AND },
	{ "\\wedge", Tag::AND },
	{ "\\ifexpr", Tag::IF },
	{ "\\while", Tag::WHILE },
	{ "\\when", Tag::WHEN },
	{ "\\otherwise", Tag::OTHERWISE },
	{ "\\graphic", Tag::GRAPHIC },
	{ "\\range", Tag::RANGE },
	{ "\\transp", Tag::TRANSP },
};

std::map<std::string, int> arg_count = {
	{ "\\cos", 1 },
	{ "\\sin", 1 },
	{ "\\tan", 1 },
	{ "\\cot", 1 },
	//        { "\\exp", 1 },
	//        { "\\log", 1 },
	//        { "\\sqrt", 1 },
	//        {"\\pow", 2},

	{ "\\arcsin", 1 },
	{ "\\arccos", 1 },
	{ "\\arctan", 1 },
	//  { "\\arccot", 1 },
	{ "\\cosh", 1 },
	{ "\\sinh", 1 },
	{ "\\tanh", 1 },
	//  { "\\coth", 1 },
	//  { "\\sec", 1 },
	//  { "\\csc", 1 },
};

std::map<std::string, double> constants = {
	{ "\\true", 1 },
	{ "\\false", 0 },
	{ "\\pi", 3.14159265358979323846 },
};

std::map<std::string, double(*)(double)> funcs1 = {
	{ "\\cos", cos },
	{ "\\sin", sin },
	{ "\\tan", tan },
	{ "\\cot", [](double x) {return 1 / tan(x); } },
	//   { "\\exp", exp },
	//   { "\\log", log },
	//   { "\\sqrt", sqrt },
	{ "\\arcsin", asin },
	{ "\\arccos", acos },
	{ "\\arctan", atan },
	//  { "\\arccot", 1 },
	{ "\\cosh", cosh },
	{ "\\sinh", sinh },
	{ "\\tanh", tanh },
	//  { "\\coth", 1 },
	//  { "\\sec", 1 },
	//  { "\\csc", 1 },*/
};

std::map<std::string, double(*)(double, double)> funcs2 = {
	//   {"\\pow", pow},
};
