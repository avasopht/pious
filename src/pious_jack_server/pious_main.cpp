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
#include <pious/port.hpp>
#include <cmath>
#include <emcee/emcee.hpp>

#include <emcee/object.hpp>
#include <emcee/platform.hpp>
#include <emcee/pow2.hpp>

class SineDsp : public pious::Dsp {
 public:
  void Render(pious::Scope * scope) override {
    pious::Port * in_port = scope->GetPort("freq");
    float freq = in_port->GetHoldSignalAt(0);
    (void) freq;

    pious::Port * out_port = scope->GetPort("out");

    float buffer[64];
    for (int N = 0; N < 64; ++N)
      buffer[N] = (float) sin(2 * M_PI * N / 64 / 2);

    out_port->WriteSignal(buffer, 64);
  }
};

int main() {
  auto platform = emcee::DefaultPlatform();
  (void)emcee::Object(platform);
  (void)Log2(1);
  (void)IsPow2(1);
  (void)ToPow2(1);
  return 0;
}