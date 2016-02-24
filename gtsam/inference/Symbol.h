/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file Symbol.h
 * @date Jan 12, 2010
 * @author: Frank Dellaert
 * @author: Richard Roberts
 */

#pragma once

#include <gtsam/inference/Key.h>
#include <gtsam/base/Testable.h>
#include <boost/serialization/nvp.hpp>
#include <cstdint>

namespace gtsam {

/**
 * Character and index key used in VectorValues, GaussianFactorGraph,
 * GaussianFactor, etc.  These keys are generated at runtime from TypedSymbol
 * keys when linearizing a nonlinear factor graph.  This key is not type
 * safe, so cannot be used with any Nonlinear* classes.
 */
class GTSAM_EXPORT Symbol {
protected:
  const unsigned char c_;
  const std::uint64_t j_;

public:

  /** Default constructor */
  Symbol() :
    c_(0), j_(0) {
  }

  /** Copy constructor */
  Symbol(const Symbol& key) :
    c_(key.c_), j_(key.j_) {
  }

  /** Constructor */
  Symbol(unsigned char c, std::uint64_t j) :
    c_(c), j_(j) {
  }

  /** Constructor that decodes an integer Key */
  Symbol(Key key);

  /** return Key (integer) representation */
  Key key() const;

  /** Cast to integer */
  operator Key() const { return key(); }

  /// Print
  void print(const std::string& s = "") const;

  /// Check equality
  bool equals(const Symbol& expected, double tol = 0.0) const;

  /** Retrieve key character */
  unsigned char chr() const {
    return c_;
  }

  /** Retrieve key index */
  std::uint64_t index() const {
    return j_;
  }

  /** Create a string from the key */
  operator std::string() const;

  /** Comparison for use in maps */
  bool operator<(const Symbol& comp) const {
    return c_ < comp.c_ || (comp.c_ == c_ && j_ < comp.j_);
  }

  /** Comparison for use in maps */
  bool operator==(const Symbol& comp) const {
    return comp.c_ == c_ && comp.j_ == j_;
  }

  /** Comparison for use in maps */
  bool operator==(Key comp) const {
    return comp == (Key)(*this);
  }

  /** Comparison for use in maps */
  bool operator!=(const Symbol& comp) const {
    return comp.c_ != c_ || comp.j_ != j_;
  }

  /** Comparison for use in maps */
  bool operator!=(Key comp) const {
    return comp != (Key)(*this);
  }

  /** Return a filter function that returns true when evaluated on a Key whose
   * character (when converted to a Symbol) matches \c c.  Use this with the
   * Values::filter() function to retrieve all key-value pairs with the
   * requested character.
   */
  static boost::function<bool(Key)> ChrTest(unsigned char c);

private:

  /** Serialization function */
  friend class boost::serialization::access;
  template<class ARCHIVE>
  void serialize(ARCHIVE & ar, const unsigned int /*version*/) {
    ar & BOOST_SERIALIZATION_NVP(c_);
    ar & BOOST_SERIALIZATION_NVP(j_);
  }
};

/** Create a symbol key from a character and index, i.e. x5. */
inline Key symbol(unsigned char c, std::uint64_t j) { return (Key)Symbol(c,j); }

/** Return the character portion of a symbol key. */
inline unsigned char symbolChr(Key key) { return Symbol(key).chr(); }

/** Return the index portion of a symbol key. */
inline std::uint64_t symbolIndex(Key key) { return Symbol(key).index(); }

namespace symbol_shorthand {
inline Key A(std::uint64_t j) { return Symbol('a', j); }
inline Key B(std::uint64_t j) { return Symbol('b', j); }
inline Key C(std::uint64_t j) { return Symbol('c', j); }
inline Key D(std::uint64_t j) { return Symbol('d', j); }
inline Key E(std::uint64_t j) { return Symbol('e', j); }
inline Key F(std::uint64_t j) { return Symbol('f', j); }
inline Key G(std::uint64_t j) { return Symbol('g', j); }
inline Key H(std::uint64_t j) { return Symbol('h', j); }
inline Key I(std::uint64_t j) { return Symbol('i', j); }
inline Key J(std::uint64_t j) { return Symbol('j', j); }
inline Key K(std::uint64_t j) { return Symbol('k', j); }
inline Key L(std::uint64_t j) { return Symbol('l', j); }
inline Key M(std::uint64_t j) { return Symbol('m', j); }
inline Key N(std::uint64_t j) { return Symbol('n', j); }
inline Key O(std::uint64_t j) { return Symbol('o', j); }
inline Key P(std::uint64_t j) { return Symbol('p', j); }
inline Key Q(std::uint64_t j) { return Symbol('q', j); }
inline Key R(std::uint64_t j) { return Symbol('r', j); }
inline Key S(std::uint64_t j) { return Symbol('s', j); }
inline Key T(std::uint64_t j) { return Symbol('t', j); }
inline Key U(std::uint64_t j) { return Symbol('u', j); }
inline Key V(std::uint64_t j) { return Symbol('v', j); }
inline Key W(std::uint64_t j) { return Symbol('w', j); }
inline Key X(std::uint64_t j) { return Symbol('x', j); }
inline Key Y(std::uint64_t j) { return Symbol('y', j); }
inline Key Z(std::uint64_t j) { return Symbol('z', j); }
}

/// traits
template<> struct traits<Symbol> : public Testable<Symbol> {};

} // \ namespace gtsam

