/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "emitter.h"
#include "../../jit/compiler.h"

namespace {

class compiler final : public machinery::jit::compiler {
  using emitter = machinery::arch::x86_emitter<buffer>;

  emitter _emitter;

public:
  /**
   * Default constructor.
   */
  compiler()
    : _emitter(_buffer) {}

  /**
   * Destructor.
   */
  virtual ~compiler() noexcept override {}

  virtual compiler& nop() override {
    _emitter.nop();
    return *this;
  }
};

} /* namespace */

std::unique_ptr<machinery::jit::compiler>
machinery::jit::compiler_for_x86_64() {
  return std::unique_ptr<machinery::jit::compiler>(new ::compiler());
}
