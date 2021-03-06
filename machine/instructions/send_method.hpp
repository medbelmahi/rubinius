#include "interpreter/instructions.hpp"

#include "class/call_site.hpp"

namespace rubinius {
  namespace instructions {
    inline bool send_method(STATE, CallFrame* call_frame, intptr_t literal) {
      Object* recv = stack_top();
      CallSite* call_site = reinterpret_cast<CallSite*>(literal);

      Arguments args(call_site->name(), recv, cNil, 0, 0);
      Object* ret = call_site->execute(state, args);

      (void)stack_pop();

      state->vm()->checkpoint(state);

      CHECK_AND_PUSH(ret);
    }
  }
}
