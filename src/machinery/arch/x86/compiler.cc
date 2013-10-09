/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "emitter.h"
#include "../../jit/compiler.h"

namespace {

class compiler final : public machinery::jit::compiler {
  using emitter = machinery::arch::x86_emitter<buffer>;
  using reg64   = machinery::arch::x86_reg64;

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
    _emitter.push(reg64::rbp);
    _emitter.mov(reg64::rbp, reg64::rsp);
    return *this;
  }

  virtual compiler& jmp(...) override {
    // TODO
    return *this;
  }

  virtual compiler& leave() override {
    _emitter.pop(reg64::rbp);
    return *this;
  }

  virtual compiler& ret() override {
    _emitter.ret();
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
machinery::jit::compiler_for_x86_64() {
  return std::unique_ptr<machinery::jit::compiler>(new ::compiler());
}
