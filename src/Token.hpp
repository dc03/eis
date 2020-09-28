#pragma once

#ifndef TOKEN_HPP
#  define TOKEN_HPP

#include <string>

#include "TokenTypes.hpp"

struct Token {
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t start;
    std::size_t end;

    Token(TokenType type, std::string lexeme, std::size_t line, std::size_t start, std::size_t end):
        type{type}, lexeme{std::move(lexeme)}, line{line}, start{start}, end{end} {}
};

#endif
