//
// Created by keldo on 13/12/2016.
//

#include <api/pious_device.h>
#include <api/pious_spec.h>
#include <emcee/util.hpp>
#include <algorithm>

void CreateImpulseDevice(Pious_Db *db);
void CreateHarmonicsDevice(Pious_Db *db);
void CreateChain(Pious_Db *db);

struct DspImpulse {
  Pious_Handle out;
};

static float GetImpulse(float *sig, size_t size) {
  bool has_zeroes = true;
  for(size_t i = 1; i < size; ++i) {
    if(!emcee::NearEq(0, sig[i], 0.001f))
      has_zeroes = false;
  }
  if(has_zeroes)
    return sig[0];
  return 0;
}

static void* ImpulseInit(Pious_Scope *scope) {
  DspImpulse *self = new DspImpulse;
  self->out = scope->GetHandle(scope, "out");
  return self;
}
static void ImpulseRender(Pious_Scope *scope, void *data, uint32_t) {
  DspImpulse *self = reinterpret_cast<DspImpulse*>(data);
  float buf[64];
  buf[0] = 1.f;
  for(int i = 1; i < 64; ++i)
    buf[i] = 0;
  scope->WriteSignal(scope, self->out, buf, 64);
}

struct DspInterleave {
  Pious_Handle in;
  Pious_Handle out;
};

static void* InterleaveInit(Pious_Scope *scope) {
  DspInterleave *self = new DspInterleave;
  self->in = scope->GetHandle(scope, "in");
  self->out = scope->GetHandle(scope, "out");
  return self;
}

static void InterleaveRender(Pious_Scope *scope, void *data, uint32_t ) {
  DspInterleave *self = reinterpret_cast<DspInterleave*>(data);
  float in[64];
  scope->ReadSignal(scope, self->in, in, 64);
  bool is_impulse = true;
  for(int i = 0; i < 64; ++i) {
    if(i == 0 && !emcee::NearEq(1.f, in[i], 0.001f))
      is_impulse = false;
    if(i > 0 && !emcee::NearEq(0, in[i], 0.001f))
      is_impulse = false;
  }
  float out[64];
  for(int i = 0; i < 64; ++i) {
    float mult = is_impulse ? 1 : 0;
    if(i%2 == 0)
      out[i] = 1 * mult;
    else
      out[i] = 0 * mult;
  }
  scope->WriteSignal(scope, self->out, out, 64);
}

struct DspInterAccum {
  Pious_Handle in;
  Pious_Handle out;
};
void* DspInterAccumInit (Pious_Scope *scope) {
  DspInterAccum *self = new DspInterAccum;
  self->in = scope->GetHandle(scope, "in");
  self->out = scope->GetHandle(scope, "out");
  return self;
}

void DspInterAccumRender(Pious_Scope *scope, void *data, uint32_t) {
  auto self = reinterpret_cast<DspInterAccum*>(data);
  float in[64];
  scope->ReadSignal(scope, self->in, in, 64);
  float out[64];
  for(int i = 0; i < 64; i += 2) {
    out[i] = in[i];
    out[i+1] = in[i] * i/2;
  }
  scope->WriteSignal(scope, self->out, out, 64);
}

struct DspHarmonics {
  Pious_Handle in;
  Pious_Handle out;
};

void* DspHarmonicsInit(Pious_Scope *scope) {
  auto self = new DspHarmonics;
  self->in = scope->GetHandle(scope, "in");
  self->out = scope->GetHandle(scope, "out");
  return self;
}

void MarkPrimes(float *arr, size_t size) {
  for(size_t i = 2; i < size; ++i) {
    arr[i] = 1;
    for(size_t j = 2; j < size; ++j) {
      if(i%j == 0)
        arr[i] = 0;
    }
  }
}

void DspHarmonicsRender(Pious_Scope *scope, void *data, uint32_t) {
  auto self = reinterpret_cast<DspHarmonics*>(data);
  float in[64];
  scope->ReadSignal(scope, self->in, in, 64);
  float out[64];
  std::fill(&out[0],&out[64],0);
  MarkPrimes(out, 64);
  float amp = GetImpulse(in, 64);
  for(size_t i = 0; i < 64; ++i) {
    out[i] *= amp;
  }
  scope->WriteSignal(scope, self->out, out, 64);
}

int main() {
  Pious_Db *db = PiousDb_Create();

  CreateImpulseDevice(db);
  CreateHarmonicsDevice(db);
  CreateChain(db);
  return 0;
}
void CreateChain(Pious_Db *db) {
  Pious_DeviceSpec *chain = PiousDb_CreateDevice(db, "s/com.avasopht.chain/i/1014");
  PiousSpec_AddDevicePort(chain, Pious_IoTypeSignalOut, "s/out");
  PiousSpec_AddDevice(chain, "s/com.avasopht.impulse", "s/impulse");
  PiousSpec_AddDevice(chain, "i/1001", "s/harmonics");
  PiousSpec_AddConnection(chain, "impulse", "out", "harmonics", "in");
  PiousSpec_AddConnection(chain, "harmonics", "out", "self", "out");
}
void CreateHarmonicsDevice(Pious_Db *db) {
  Pious_DeviceSpec *harmonics = PiousDb_CreateDevice(db, "s/com.avasopht.harmonics/i/1001");
  PiousSpec_AddDevicePort(harmonics, Pious_IoTypeSignalIn, "in");
  PiousSpec_AddDevicePort(harmonics, Pious_IoTypeSignalOut, "out");
  Pious_UnitPlugin harmonics_dsp { DspHarmonicsInit, DspHarmonicsRender };
  PiousSpec_LoadDsp(harmonics, &harmonics_dsp);
}
void CreateImpulseDevice(Pious_Db *db) {
  Pious_DeviceSpec *impulse = PiousDb_CreateDevice(db, "s/com.avasopht.impulse/i/1000");
  PiousSpec_AddDevicePort(impulse, Pious_IoTypeSignalOut,"out");
  Pious_UnitPlugin impulse_dsp = { ImpulseInit, ImpulseRender };
  PiousSpec_LoadDsp(impulse, &impulse_dsp);
}