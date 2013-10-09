/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "emitter.h"
#include "../../jit/compiler.h"

namespace {

class compiler final : public machinery::jit::compiler {
  using emitter = machinery::arch::arm_emitter<buffer>;

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

  virtual compiler& enter() override {
    // TODO
    return *this;
  }

  virtual compiler& jmp(...) override {
    // TODO
    return *this;
  }

  virtual compiler& leave() override {
    // TODO
    return *this;
  }

  virtual compiler& ret() override {
    // TODO
    return *this;
  }

  virtual compiler& abs(...) override {
    // TODO
    return *this;
  }

  virtual compiler& add(...) override {
    // TODO
    return *this;
  }

  virtual compiler& and_(...) override {
    // TODO
    return *this;
  }

  virtual compiler& clz(...) override {
    // TODO
    return *this;
  }

  virtual compiler& cmp(...) override {
    // TODO
    return *this;
  }

  virtual compiler& dec(...) override {
    // TODO
    return *this;
  }

  virtual compiler& div(...) override {
    // TODO
    return *this;
  }

  virtual compiler& inc(...) override {
    // TODO
    return *this;
  }

  virtual compiler& mov(...) override {
    // TODO
    return *this;
  }

  virtual compiler& mul(...) override {
    // TODO
    return *this;
  }

  virtual compiler& nand(...) override {
    // TODO
    return *this;
  }

  virtual compiler& neg(...) override {
    // TODO
    return *this;
  }

  virtual compiler& nop() override {
    _emitter.nop();
    return *this;
  }

  virtual compiler& nor(...) override {
    // TODO
    return *this;
  }

  virtual compiler& not_(...) override {
    // TODO
    return *this;
  }

  virtual compiler& or_(...) override {
    // TODO
    return *this;
  }

  virtual compiler& pow(...) override {
    // TODO
    return *this;
  }

  virtual compiler& rem(...) override {
    // TODO
    return *this;
  }

  virtual compiler& shl(...) override {
    // TODO
    return *this;
  }

  virtual compiler& shr(...) override {
    // TODO
    return *this;
  }

  virtual compiler& sub(...) override {
    // TODO
    return *this;
  }

  virtual compiler& xor_(...) override {
    // TODO
    return *this;
  }
};

} /* namespace */

std::unique_ptr<machinery::jit::compiler>
machinery::jit::compiler_for_armv8_aarch64() {
  return std::unique_ptr<machinery::jit::compiler>(new ::compiler());
}
