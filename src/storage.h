#ifndef SIMIT_STORAGE_H
#define SIMIT_STORAGE_H

#include <map>
#include <memory>
#include <string>

#include "intrusive_ptr.h"
#include "stencils.h"

namespace simit {
namespace pe {
class PathExpression;
}
namespace ir {
class Func;
class Var;
class Stmt;
class Expr;
class TensorIndex;

// TODO: Should we remove the whole system concept? This gives us Dense indices,
//       PathExpression (reduced or unreduced) indices, Diagonal indices,
//       Matrix-Free indices, ... .

/// The storage arrangement of a tensor (e.g. dense or stored on a set).
class TensorStorage {
public:
  enum class Kind {
    /// Undefined storage.
    Undefined,

    /// The dense tensor stored row major.
    /// TODO: Add a tensor layout object that describes the layout (row, z, ...)
    Dense,

    /// A sparse matrix, whose non-empty (non-zero) components are accessible
    /// through a tensor index.
    Indexed,

    /// A diagonal matrix.
    Diagonal,

    /// A stencil matrix, whose non-zeros lie on a fixed number of diagonals.
    /// The set of diagonals is based on the access pattern of the assembly
    /// kernel.
    Stencil,

    /// A system tensor whose contributions are stored on the target set that it
    /// was assembled from. That is, the tensor is stored prior to the map
    /// reduction, and any expression that uses the tensor must reduce it.
    // Unreduced,

    /// A system tensor that is never stored. Any index expressions that use
    /// this tensor must be fused with the tensor assembly.
    MatrixFree
  };

  /// Create an undefined tensor storage
  TensorStorage();

  /// Create a tensor storage descriptor.
  TensorStorage(Kind kind);

  /// Create a system diagonal storage descriptor.
  TensorStorage(const Expr &targetSet);

  /// Create a system tensor reduced storage descriptor. The 'targetSet'
  /// argument is the the set that the system tensor was created by mapping
  /// over. The 'storageSet' is the set the tensor is stored on.
  TensorStorage(const Expr &targetSet, const Expr &storageSet);

  /// Create a stencil based storage descriptor. `assemblyFunc' is the stencil
  /// assembly kernel whose access pattern determines the sparsity. `targetVar'
  /// is the output variable within the assembly func whose sparsity is being
  /// determined here.
  TensorStorage(string assemblyFunc, string targetVar,
                const Expr &targetSet, const Expr &throughSet);

  /// Retrieve the tensor storage type.
  Kind getKind() const;

  /// True if the tensor is dense, which means all values are stored without an
  /// index.
  bool isDense() const;

  /// True if the tensor is stored on a system, false otherwise.
  bool isSystem() const;

  bool hasPathExpression() const;
  const pe::PathExpression& getPathExpression() const;
  void setPathExpression(const pe::PathExpression& pathExpression);

  /// Retrieve properties of the stencil storage
  std::string getStencilFunc() const;
  std::string getStencilVar() const;
  /// Stencil structure (built during assembly map lowering)
  bool hasStencil() const;
  const Stencil& getStencil() const;
  void setStencil(const Stencil& stencil);

  // TODO DEPRECATED: These live in the environment now
  bool hasTensorIndex(unsigned sourceDim, unsigned sinkDim) const;
  const TensorIndex& getTensorIndex(unsigned sourceDim, unsigned sinkDim) const;
  void addTensorIndex(Var tensor, unsigned sourceDim, unsigned sinkDim);

  // TODO DEPRECATED: These should not be needed with the new TensorIndex system
  const Expr &getSystemTargetSet() const;
  const Expr &getSystemStorageSet() const;

private:
  struct Content;
  std::shared_ptr<Content> content;
};
std::ostream &operator<<(std::ostream&, const TensorStorage&);

/// The storage of a set of tensors.
class Storage {
public:
  Storage();

  /// Add storage for a tensor variable.
  void add(const Var &tensor, TensorStorage tensorStorage);

  /// Add the variables from the `other` storage to this storage.
  void add(const Storage &other);

  /// True if the tensor has a storage descriptor, false otherwise.
  bool hasStorage(const Var &tensor) const;

  /// Retrieve the storage of a tensor variable to modify it.
  TensorStorage &getStorage(const Var &tensor);

  /// Retrieve the storage of a tensor variable to inspect it.
  const TensorStorage &getStorage(const Var &tensor) const;

  /// Iterator over storage Vars in this Storage descriptor.
  class Iterator {
  public:
    struct Content;
    Iterator(Content *content);
    ~Iterator();
    const Var &operator*();
    const Var *operator->();
    Iterator& operator++();
    friend bool operator!=(const Iterator&, const Iterator&);
  private:
    Content *content;
  };

  /// Get an iterator pointing to the first Var in this Storage.
  Iterator begin() const;

  /// Get an iterator pointing to the last Var in this Storage.
  Iterator end() const;

private:
  struct Content;
  std::shared_ptr<Content> content;
};
std::ostream &operator<<(std::ostream&, const Storage&);


/// Retrieve a storage descriptor for each tensor used in `func`.
Storage getStorage(const Func &func);

/// Retrieve a storage descriptor for each tensor used in `stmt`.
Storage getStorage(const Stmt &stmt);

/// Adds storage descriptors for each tensor in `func` not already described.
void updateStorage(const Func &func, Storage *storage);

/// Adds storage descriptors for each tensor in `stmt` not already described.
void updateStorage(const Stmt &stmt, Storage *storage);

}}

#endif
