#ifndef SIMIT_TYPES_H
#define SIMIT_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

#include "interfaces.h"
#include "tensor_components.h"

namespace simit {
namespace ir {

/// An index set is a set of labels into a set.  There are three types of index
/// set distringuished by the type of set they index into: a range (Range), a 
/// set name (Set) or the set of all integers (Dynamic).
class IndexSet {
public:
  /// The types of index sets that are supported.
  enum Kind {Range, Set, Dynamic};

  /// Create an index set consisting of the items in the given range.
  IndexSet(int rangeSize) : kind(Range), rangeSize(rangeSize) {}

  /// Create an index set over the given set.
  IndexSet(const std::string &setName): kind(Set), setName(setName) {}

  /// Create a variable-size index set.
  IndexSet() : kind(Dynamic) {}

  /// Get the Kind of the index set (Range, Set or Dynamic)
  Kind getKind() const { return kind; }

  /// Returns the size of the index set if kind is Range, otherwise undefined
  int getSize() const {
    assert(kind == Range && "Only Range index sets have a statically known size");
    return rangeSize;
  }

  /// Returns the name of the indexset set if kind is Set, otherwise undefined
  const std::string &getSetName() const {
    assert(kind==Set);
    return setName;
  }

  friend bool operator==(const IndexSet &l, const IndexSet &r);
  friend std::ostream &operator<<(std::ostream &os, const IndexSet &is);

private:
  Kind kind;

  int rangeSize;
  std::string setName;
};

bool operator!=(const IndexSet &l, const IndexSet &r);


/// An index domain is a set product of zero or more index sets.
class IndexDomain {
public:
  explicit IndexDomain() {}
  explicit IndexDomain(const IndexSet &is) { indexSets.push_back(is); }
  explicit IndexDomain(const std::vector<IndexSet> &iss) : indexSets(iss) {};

  /// Get the index sets that are multiplied to get the index set product.
  const std::vector<IndexSet> &getFactors() const {return indexSets; }

  /// Get the number of elements in the product of the index sets if all the
  /// index sets are Range sets, otherwise undefined.
  size_t getSize() const;

private:
  std::vector<IndexSet> indexSets;
};

bool operator==(const IndexDomain &l, const IndexDomain &r);
bool operator!=(const IndexDomain &l, const IndexDomain &r);
IndexDomain operator*(const IndexDomain &l, const IndexDomain &r);
std::ostream &operator<<(std::ostream &os, const IndexDomain &isp);


/// A Simit type, which is either a Set or a Tensor.
class Type : public simit::interfaces::Printable, simit::interfaces::Uncopyable{
public:
  enum Kind { Tensor, Element, Set, Tuple };
  Type(Kind kind) : kind(kind) {}

  virtual ~Type() {}

  Kind getKind() const { return kind; }
  bool isTensor() const { return kind == Type::Tensor; }
  bool isElement() const { return kind == Type::Element; }
  bool isSet() const { return kind == Type::Set; }
  bool isTuple() const { return kind == Type::Tuple; }

private:
  Kind kind;
};

bool operator==(const Type& l, const Type& r);
bool operator!=(const Type& l, const Type& r);


/// The type of a tensor (the type of its components and its shape). Note that
/// a scalar in Simit is a o-order tensor.
class TensorType : public Type {
public:
  TensorType(ComponentType componentType)
      : Type(Type::Tensor), componentType(componentType) {}

  TensorType(ComponentType componentType,
             const std::vector<IndexDomain> &dimensions)
      : Type(Type::Tensor), componentType(componentType),
        dimensions(dimensions) {}

  /// Get the order of the tensor (the number of dimensions).
  size_t getOrder() const { return dimensions.size(); }

  /// Get the type of the components in the vector.
  ComponentType getComponentType() const { return componentType; }

  /// Get the index sets that form the dimensions of the tensor.
  const std::vector<IndexDomain> &getDimensions() const {return dimensions;}

  /// Get the number of components in the tensor if all its dimensions are
  /// composed of Range index sets, otherwise undefined.
  size_t getSize() const;

private:
  ComponentType componentType;
  std::vector<IndexDomain> dimensions;

  void print(std::ostream &os) const;
};

bool operator==(const TensorType& l, const TensorType& r);
bool operator!=(const TensorType& l, const TensorType& r);


/// A Simit Element type, which consist of zero or more tensor fields.
class ElementType : public Type {
public:
  typedef std::map<std::string, std::shared_ptr<TensorType>> FieldsMapType;

  ElementType(const std::string &name, const FieldsMapType &fields)
      : Type(Type::Element), name(name), fields(fields) {}

  const std::string &getName() const { return name; }
  const FieldsMapType &getFields() const { return fields; }

private:
  std::string name;
  FieldsMapType fields;

  void print(std::ostream &os) const;
};

bool operator==(const ElementType &l, const ElementType &r);
bool operator!=(const ElementType &l, const ElementType &r);


/// A Simit tuple type, which is defined by the types of its elements.
class TupleType : public Type {
public:
  TupleType(std::vector<std::shared_ptr<ElementType>> elementTypes)
      : Type(Type::Tuple), elementTypes(elementTypes) {}

  const std::vector<std::shared_ptr<ElementType>> &getElementType() const {
    return elementTypes;
  }

private:
  std::vector<std::shared_ptr<ElementType>> elementTypes;

  void print(std::ostream &os) const;
};


/// A Simit set type, which is defined by the type of its elements and it's
/// connectivity information.
class SetType : public Type {
public:
  SetType(std::shared_ptr<ElementType> elementType)
      : Type(Type::Set), elementType(elementType) {}

  const std::shared_ptr<ElementType> &getElementType() const {
    return elementType;
  }

private:
  std::shared_ptr<ElementType> elementType;

  void print(std::ostream &os) const;
};

bool operator==(const SetType& l, const SetType& r);
bool operator!=(const SetType& l, const SetType& r);


// Conversion functions
inline TensorType *tensorTypePtr(Type *type) {
  assert(type->isTensor());
  return static_cast<TensorType*>(type);
}

inline TensorType *tensorTypePtr(const std::shared_ptr<Type> &type) {
  return tensorTypePtr(type.get());
}

inline SetType *setTypePtr(Type *type) {
  assert(type->isSet());
  return static_cast<SetType*>(type);
}

inline const SetType *setTypePtr(const Type *type) {
  assert(type->isSet());
  return static_cast<const SetType*>(type);
}

inline SetType *setTypePtr(const std::shared_ptr<Type> &type) {
  return setTypePtr(type.get());
}

}} // namespace simit::internal

#endif
