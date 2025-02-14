#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  /*
  return Corpus();
  */

  //elems' type of `it_space` should be set into const_iterator
  //as template of `find_all` deduced the `source.begin()` to `const_iterator`
  std::vector<std::string::const_iterator>it_space = find_all(source.begin(), source.end(),isspace);

  auto create_token = [&source](const auto& begin, const auto& end){
    return Token(source, begin, end);
  } ;

  std::set<Token> tokens;
  std::transform(it_space.begin(), it_space.end()-1, it_space.begin()+1, 
                  std::inserter(tokens, tokens.end()), create_token);

  std::erase_if(tokens, [](const Token& t){
    return t.content.empty();
  });
  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  /*
  return std::set<Mispelling>();
  */

  namespace rv = std::ranges::views;

/**
 * lambda func: predicate whether a token is misspelled
 * @param t A `Token`
 * @return  boolean: true or fasle
 */
  auto isMispell = [&dictionary](const Token& t){
    if(!dictionary.contains(t.content)){
      return true;
    }
    return false;
  };

  /**
   * lambda func: get a misspelling Token `t` 's suggestions
   * @param t const Token& t, a misspelling Token
   * @return a struct Mispelling{t, suggestions}
   */
  auto get_Misspelling = [&dictionary](const Token& t){
      auto distance1 = dictionary | 
            rv::filter([&t](const std::string& dic_token){
              if(levenshtein(t.content, dic_token) == 1)  return true;
              return false; 
            });//one view of tokens in dictionary whose distance is 1 with `t`.

      std::set<std::string> suggestions(distance1.begin(), distance1.end());

      return Mispelling{t, suggestions};
  };

/**
 * get a view of Mispelling{t,suggestions}
 */
  auto view = source | rv::filter(isMispell) | rv::transform(get_Misspelling);
  
  /**
   * remove the suggestion-less misspelling tokens
   * and get the view of Misspelled Tokens with suggestions
   */
  auto view_sugg = view | rv::filter([](const Mispelling& m){
      if(m.suggestions.empty())   return false;
      return true;
  });
  return std::set<Mispelling>(view_sugg.begin(), view_sugg.end());
};

/* Helper methods */

#include "utils.cpp"