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

#ifndef PIOUS_PIOUS_PORT_INSTANCE_H
#define PIOUS_PIOUS_PORT_INSTANCE_H

#ifndef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct Pious_PortInstance;

struct Pious_ConnectionInstance * Pious_PortInstanceConnect (
    struct Pious_PortInstance * p, struct Pious_PortInstance * dest);
void Pious_PortInstanceRemoveConnection(struct Pious_PortInstance * p, struct Pious_PortInstance * dest);
/*! Returns true if an id is successfully written to id_out. id_buffer_size is
 * the size of the buffer including null terminator.
 */
int Pious_PortInstanceReadId(const struct Pious_PortInstance * p, char * id_out, size_t id_buffer_size);
struct Pious_DeviceInstance * Pious_PortInstanceGetDevice( struct Pious_PortInstance * p);

#ifndef __cplusplus
}
#endif

#endif /* PIOUS_PIOUS_PORT_INSTANCE_H */