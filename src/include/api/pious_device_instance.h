/*
 * Created by The Pious Authors on 25/03/2017.
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

#ifndef PIOUS_PIOUS_DEVICE_INSTANCE_H
#define PIOUS_PIOUS_DEVICE_INSTANCE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Pious_DeviceInstance;

struct Pious_DeviceInstance * PiousDevInst_Create(struct Pious_Spec * spec);
struct Pious_PortInstance * PiousDevInst_FindPort(struct Pious_DeviceInstance * p, const char * id);
struct Pious_PortInstance * PiousDevInst_PortAt(struct Pious_DeviceInstance * p, size_t index);
size_t PiousDevInst_GetPortCount(const struct Pious_DeviceInstance * p);

#ifdef __cplusplus
}
#endif

#endif /* PIOUS_PIOUS_DEVICE_INSTANCE_H */
