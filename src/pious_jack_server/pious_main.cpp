//
// Created by keldo on 13/12/2016.
//

#include <api/pious_device.h>
#include <api/pious_spec.h>
#include <emcee/map.hpp>
#include <api/pious_sys.h>
#include <api/db.h>
#include <emcee/util.hpp>
#include <algorithm>
#include <pious/dsp.hpp>
#include <pious/scope.hpp>
#include <emcee/vector.hpp>
#include <pious/port_instance.hpp>
#include <cmath>
#include <emcee/emcee.hpp>

class SineDsp : public pious::Dsp {
 public:
  void Render(pious::Scope * scope) override {
    Pious_Handle in_signal_handle = scope->GetHandle("freq");
    pious::PortInstance * in_port = scope->GetPort(&in_signal_handle);
    float freq = in_port->GetHoldSignalAt(0);
    (void) freq;

    Pious_Handle out_signal_handle = scope->GetHandle("out");
    pious::PortInstance * out_port = scope->GetPort(&out_signal_handle);

    float buffer[64];
    for(int N = 0; N < 64; ++N)
      buffer[N] = sin(2 * M_PI * N / 64 / 2);

    out_port->WriteSignal(buffer, 64);
  }
};

int main() {
  return 0;
}