/*
 * Created by The Pious Authors on 16/12/2016.
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PIOUS_PIOUS_SPEC_H
#define PIOUS_PIOUS_SPEC_H

#include "pious_device.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PIOUS_MAX_DEVICE_CHILD_COUNT 256
#define PIOUS_MAX_DEVICE_CONNECTION_COUNT 2048
#define PIOUS_MAX_DEVICE_PORT_COUNT 2048

struct Pious_Db;
struct Pious_DeviceSpec;
struct Pious_ReferenceSpec;
struct Pious_Mem;
struct Pious_DeviceConnectionIds {
  char source_device_id [256];
  char source_device_port[256];
  char dest_device_id [256];
  char dest_device_port[256];
};

void PiousSpec_LoadDsp(struct Pious_DeviceSpec *spec, Pious_UnitPlugin *dsp);
void PiousSpec_SetName(struct Pious_DeviceSpec *spec, const char *name);
void PiousSpec_AddDevicePort(struct Pious_DeviceSpec *spec, enum Pious_IoType io_type, const char *port_id);
size_t PiousSpec_PortCount(const struct Pious_DeviceSpec *spec);
size_t PiousSpec_GetPortNameLengthAt(const struct Pious_DeviceSpec *spec, size_t index);
size_t PiousSpec_GetPortNameAt(const struct Pious_DeviceSpec *spec, size_t index, char * out);
bool PiousSpec_HasPort(const struct Pious_DeviceSpec *spec, const char *port_id);
enum Pious_IoType PiousSpec_GetPortType(const struct Pious_DeviceSpec *spec, const char *port_id);
struct Pious_ReferenceSpec* PiousSpec_AddDevice(struct Pious_DeviceSpec *spec, const char *db_id, const char *spec_id);
struct Pious_ReferenceSpec* PiousSpec_FindDevice(struct Pious_DeviceSpec *spec, const char *spec_id);
struct Pious_ReferenceSpec* PiousSpec_DeviceAt(struct Pious_DeviceSpec *spec, size_t idx);
size_t PiousSpec_DeviceCount(const struct Pious_DeviceSpec *spec);
bool PiousSpec_IsPolyphonic(const struct Pious_DeviceSpec *spec, const char *ref_id);
void PiousSpec_SetPolyphonic(struct Pious_DeviceSpec *spec, const char *ref_id, bool b);
void PiousSpec_AddConnection(struct Pious_DeviceSpec *spec,
                         const char *first_device, const char *first_port,
                         const char *second_device, const char *second_port);
size_t PiousSpec_ConnectionCount(const struct Pious_DeviceSpec *spec);
struct Pious_DeviceConnectionIds PiousSpec_GetConnectionAt(const struct Pious_DeviceSpec *spec, size_t idx);


#ifdef __cplusplus
}
#endif

#endif /* PIOUS_PIOUS_SPEC_H */
